#include "zar.h"
namespace zar
{
	bool CZAR::Fetch(CKey* key, void* buf, int size)
	{
		bool isOpen = false;
		bool success = false;

		if (m_pFile == NULL)
		{
			return false;
		}
		else
		{
			isOpen = m_pFile->IsOpen();
		}

		CKey* openKey = OpenKey(key);
		if (isOpen && openKey != NULL)
		{
			if (openKey->m_size != 0)
			{
				int offset = key->m_offset;
				int keyFilePos = m_pFile->fseek(offset, SEEK_SET);

				if (offset == keyFilePos && size <= key->m_size)
				{
					offset = m_pFile->fread(buf, size);

					if (m_bSecure && 0 < size)
					{
						if (8 < size)
						{
							do
							{
								// Yes, I know this fucking sucks.
								unsigned char* byte = (unsigned char*)((int)buf + offset);
								offset += 8;
								byte[0] = ~byte[0];
								byte[1] = ~byte[1];
								byte[2] = ~byte[2];
								byte[3] = ~byte[3];
								byte[4] = ~byte[4];
								byte[5] = ~byte[5];
								byte[6] = ~byte[6];
								byte[7] = ~byte[7];
							} while (offset < size - 8);
						}

						for (; offset < size; offset++)
						{
							unsigned char* byte = (unsigned char*)((int)buf + offset);
							byte[offset] = ~byte[offset];
						}
					}
				}
			}

			CloseKey(key);
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, int(*callback)(CZAR*, int, void*), void* buf)
	{
		bool isOpen = false;
		bool success = false;
		CKey* openKey = GetOpenKey();

		if (openKey == NULL)
		{
			success = false;
		}
		else
		{
			openKey = openKey->FindKey(name);
			success = false;

			if (m_pFile == NULL)
			{
				isOpen = false;
			}
			else
			{
				isOpen = m_pFile->IsOpen();
			}

			CKey* bufferOpenKey = OpenKey(openKey);
			if (isOpen && bufferOpenKey != NULL)
			{
				int position = m_pFile->fseek(openKey->m_offset, SEEK_SET);
				if (position != -1)
				{
					hackStr = openKey->m_name;
					int callbackResult = callback(this, openKey->m_size, buf);

					if (0 < callbackResult)
					{
						success = callbackResult <= openKey->m_size;
					}
				}

				CloseKey(openKey);
			}
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, void* buf, int size)
	{
		bool isOpen = false;
		bool success = false;
		CKey* openKey = GetOpenKey();

		if (openKey == NULL)
		{
			success = false;
		}
		else
		{
			openKey = openKey->FindKey(name);
			success = false;

			if (m_pFile == NULL)
			{
				isOpen = false;
			}
			else
			{
				isOpen = m_pFile->IsOpen();
			}

			CKey* bufferOpenKey = OpenKey(openKey);
			if (isOpen && bufferOpenKey != NULL)
			{
				if (openKey->m_size != 0)
				{
					int offset = openKey->m_offset;
					int position = m_pFile->fseek(offset, SEEK_SET);
					if (offset == position && size <= openKey->m_size)
					{
						offset = m_pFile->fread(buf, size);
						success = size == offset;
						Unsecurify(buf, size);
					}
				}

				CloseKey(openKey);
			}
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, char** array)
	{
		bool isOpen = false;
		bool success = false;

		if (m_pFile == NULL)
		{
			isOpen = false;
		}
		else
		{
			isOpen = m_pFile->IsOpen();
		}

		if (!isOpen)
		{
			success = false;
		}
		else
		{
			success = false;
			size_t keySize = GetSize(name);

			if (0 < keySize)
			{
				char* strArray = (char*)calloc(keySize + 1, 1);
				*array = strArray;

				CKey* openKey = GetOpenKey();

				if (openKey == NULL)
				{
					success = false;
				}
				else
				{
					openKey = openKey->FindKey(name);
					// success = Fetch(openKey, strArray, keySize, 0);
				}
			}
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, float* buf)
	{
		bool success = false;

		CKey* openKey = GetOpenKey();

		if (openKey == NULL)
		{
			success = false;
		}
		else
		{
			openKey = openKey->FindKey(name);
			success = Fetch(openKey, buf, 4);
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, unsigned int* buf)
	{
		bool success = false;

		CKey* openKey = GetOpenKey();

		if (openKey == NULL)
		{
			success = false;
		}
		else
		{
			openKey = openKey->FindKey(name);
			success = Fetch(openKey, buf, 4);
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, int* buf)
	{
		bool success = false;

		CKey* openKey = GetOpenKey();

		if (openKey == NULL)
		{
			success = false;
		}
		else
		{
			openKey = openKey->FindKey(name);
			success = Fetch(openKey, buf, 4);
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, bool* buf)
	{
		bool success = false;
		char cBool = 0;

		CKey* openKey = GetOpenKey();

		if (openKey == NULL)
		{
			success = false;
		}
		else
		{
			openKey = openKey->FindKey(name);
			success = Fetch(openKey, &cBool, 4);
		}

		if (success)
		{
			*buf = cBool != 0;
		}

		return success;
	}

	bool CZAR::FetchAll(int(*callback)(CZAR*, char*, void*, int, void*), void* buf)
	{
		int count = 0;
		bool valid = false;
		bool isOpen = false;
		CKey* openKey = GetOpenKey();

		for (auto it = openKey->begin(); it != openKey->end(); it++)
		{
			CKey* curKey = *it;

			if (m_pFile == NULL)
			{
				isOpen = false;
			}
			else
			{
				isOpen = m_pFile->IsOpen();
			}

			CKey* bufferOpenKey = OpenKey(curKey);
			if (isOpen && bufferOpenKey != NULL)
			{
				int position = m_pFile->fseek(curKey->m_offset, SEEK_CUR);

				if (position != -1)
				{
					void* lipBuf = NULL;
					FetchLIP(curKey, &lipBuf);
					int result = callback(this, curKey->m_name, lipBuf, curKey->m_size, buf);

					if (0 < result)
					{
						valid = result <= curKey->m_size;
					}
				}

				CloseKey(curKey);
			}

			if (valid)
			{
				count++;
			}
		}

		return count != 0;
	}

	bool CZAR::FetchLIP(CKey* key, void** buf)
	{
		bool success = false;
		bool isOpen = false;
		CBufferIO* bufferIO = dynamic_cast<CBufferIO*>(m_pFile);

		if (m_pFile == NULL)
		{
			isOpen = false;
		}
		else
		{
			isOpen = m_pFile->IsOpen();
		}

		CKey* openKey = OpenKey(key);
		if (isOpen && openKey != NULL)
		{
			if (key->m_size != 0)
			{
				int offset = key->m_offset;
				int position = m_pFile->fseek(offset, SEEK_CUR);

				if (offset == position)
				{
					size_t size = bufferIO->fread(key->m_size, buf);
					success = size != 0;
				}
			}

			CloseKey(key);
		}

		return success;
	}
}
