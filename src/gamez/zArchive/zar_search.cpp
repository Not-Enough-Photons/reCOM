#include "zar.h"

#include "gamez/zutil/util_stable.h"
#include "gamez/zutil/util_systemio.h"

namespace zar
{
	bool CZAR::Fetch(CKey* key, void* buf, size_t size)
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
			if (key->m_size != 0)
			{
				s32 offset = key->m_offset;
				size_t position = m_pFile->fseek(offset, SEEK_SET);

				success = offset == position;

				if (success && size <= key->m_size)
				{
					offset = m_pFile->fread(buf, size);

					success = size == offset;

					ZAR_SECURE(m_bSecure, buf, size);
				}
			}

			CloseKey(key);
		}

		return success;
	}

	bool CZAR::Fetch(const char* name, s32(*callback)(CZAR*, s32, void*), void* buf)
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
				s32 position = m_pFile->fseek(openKey->m_offset, SEEK_SET);
				if (position != -1)
				{
					hackStr = openKey->m_name;
					s32 callbackResult = callback(this, openKey->m_size, buf);

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

	bool CZAR::Fetch(const char* name, void* buf, size_t size)
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
					s32 offset = openKey->m_offset;
					s32 position = m_pFile->fseek(offset, SEEK_SET);
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

	bool CZAR::Fetch(const char* name, f32* buf)
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

	bool CZAR::Fetch(const char* name, u32* buf)
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

	bool CZAR::Fetch(const char* name, s32* buf)
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

	bool CZAR::FetchAll(s32(*callback)(CZAR*, char*, void*, s32, void*), void* buf)
	{
		s32 count = 0;
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
				s32 position = m_pFile->fseek(curKey->m_offset, SEEK_CUR);

				if (position != -1)
				{
					void* lipBuf = NULL;
					FetchLIP(curKey, &lipBuf);
					s32 result = callback(this, curKey->m_name, lipBuf, curKey->m_size, buf);

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
				s32 offset = key->m_offset;
				s32 position = m_pFile->fseek(offset, SEEK_SET);
				success = offset == position;

				if (success)
				{
					size_t size = m_pFile->fread(key->m_size, buf);
					success = size != 0;
				}
			}

			CloseKey(key);
		}

		return success;
	}

	size_t CZAR::FetchString(const char* name, char* buf, size_t size)
	{
		int zero = 0;
		int keyOffset = 0;

		bool success = false;

		CKey* key = GetOpenKey();
		CKey* stringKey = NULL;

		key = key->FindKey(name);

		if (key != NULL)
		{
			bool isOpen = false;
			size_t keySize = key->m_size;

			if (keySize <= size)
			{
				if (m_pFile == NULL)
				{
					isOpen = false;
				}
				else
				{
					isOpen = m_pFile->IsOpen();
				}

				stringKey = OpenKey(key);
				if (isOpen && stringKey != NULL)
				{
					if (key->m_size != 0)
					{
						keyOffset = key->m_offset;
						int position = m_pFile->fseek(keyOffset, SEEK_SET);

						if (keyOffset == position && keySize <= key->m_size)
						{
							keyOffset = m_pFile->fread(buf, keySize);
							success = keySize == keyOffset;
							Unsecurify(buf, keySize);
						}
					}

					CloseKey(key);
				}

				keyOffset = zero;

				if (success)
				{
					keyOffset = key->m_size;
				}
			}
		}

		return keyOffset;
	}
}
