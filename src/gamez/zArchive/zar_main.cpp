#include "zar.h"

#include "bsd/strcasecmp.h"

#include "gamez/zUtil/util_main.h"
#include "gamez/zSystem/zsys_main.h"

namespace zar
{
	CKey::CKey()
	{
		m_name = NULL;
		m_size = 0;
		m_offset = 0;
	}

	CKey::CKey(char* name)
	{
		m_name = name;
		m_size = 0;
		m_offset = 0;
	}

	CKey* CKey::InsertKey(CKey* key)
	{
		insert(begin(), key);
		return key;
	}

	CKey* CKey::FindKey(const char* name)
	{
		CKey* key = NULL;

		for (auto it = begin(); it != end(); it++)
		{
			key = *it;

			if (key->m_offset != -1 && strcasecmp(name, key->m_name) == 0)
			{
				break;
			}
		}

		return key;
	}

	bool CKey::Read(CZAR* file, CIO* fileBuffer, int offset)
	{
		int i = 0;
		size_t keyOffset = 0;
		size_t keySize = 0;

		char* name = NULL;
		fileBuffer->fread(&name, 16);

		if (file->m_root != this)
		{
			m_name = name + offset;
			m_offset = keyOffset;
			m_size = keySize;
		}

		while (i != 0)
		{
			CKey* key = file->NewKey(NULL);
			key->Read(file, fileBuffer, offset);
			insert(begin(), key);
			i--;
		}
	}

	bool CKey::Write(CZAR* file)
	{
		file->Securify(m_name, 4);
		file->m_pFileAlloc->fwrite(m_name, 4);
		file->Unsecurify(m_name, 4);

		file->Securify(&m_offset, 4);
		file->m_pFileAlloc->fwrite(&m_offset, 4);
		file->Unsecurify(&m_offset, 4);

		file->Securify(&m_size, 4);
		file->m_pFileAlloc->fwrite(&m_size, 4);
		file->Unsecurify(&m_size, 4);

		file->Securify(this, 4);
		file->m_pFileAlloc->fwrite(this, 4);
		file->Unsecurify(this, 4);

		auto begin = this->begin();
		auto end = this->end();

		for (auto it = begin; it != end; it++)
		{
			CKey* key = *it;
			key->Write(file);
		}
	}

	CZAR::CZAR(const char* name, CIO* io)
	{
		m_pFileAlloc = NULL;
		m_databuffer = NULL;
		m_root = NULL;
		m_stable = NULL;
		m_filename = NULL;
		m_bCompress = false;
		m_bSecure = false;

		memset(&m_tail, 0, sizeof(TAIL));

		m_tail.version = 0x20001;

		m_stable = new CSTable(0, 1024);

		if (m_filename != "DEFAULT_ZAR_NAME")
		{
			if (m_filename == name)
			{
				if (name == "DEFAULT_ZAR_NAME")
				{
					m_filename = "DEFAULT_ZAR_NAME";
				}
				else
				{
					m_filename = strdup(name);
				}

				if (io == NULL)
				{
					io = new CFileIO();
					m_pFileAlloc = io;
				}

				m_pFile = io;

				m_data_padded = 16;

				m_root = new CKey("DEFAULT_ZAR_NAME");

				return;
			}

			free(&m_filename);
			m_filename = NULL;
		}

		if (name == "DEFAULT_ZAR_NAME")
		{
			m_filename = "DEFAULT_ZAR_NAME";
		}
		else
		{
			m_filename = strdup(name);
		}

		if (io == NULL)
		{
			io = new CFileIO();
			m_pFileAlloc = io;
		}

		m_pFile = io;

		m_data_padded = 16;
		
		m_root = new CKey("DEFAULT_ZAR_NAME");
	}

	CKey* CZAR::NewKey(const char* name)
	{
		CKey* key;

		unsigned int mode = m_pFile->GetMode();

		if ((mode & S_IXOTH) == 0)
		{
			char* keyName = m_stable->CreateString(name);
			key = new CKey(keyName);
		}
		else
		{
			if (name == NULL)
			{
				CKey* bufferedKey = new CKey();
				m_key_buffer.insert(m_key_buffer.begin(), bufferedKey);
			}
			else
			{
				char* keyName = m_stable->CreateString(name);
				key = new CKey(keyName);
				m_key_buffer.insert(m_key_buffer.begin(), key);
			}

			key = m_key_buffer.front();
		}

		return key;
	}

	CKey* CZAR::FindKey(const char* name)
	{
		CKey* key = NULL;

		if (m_keys.empty())
		{
			key = m_root;
		}
		else
		{
			key = m_keys.front();
		}

		if (key != NULL)
		{
			return key->FindKey(name);
		}

		return key;
	}

	CKey* CZAR::OpenKey(const char* keyName)
	{
		CKey* key = NULL;
		bool open = false;

		if (m_pFile == NULL)
		{
			open = false;
		}
		else
		{
			open = m_pFile->IsOpen();
		}

		if (!open)
		{
			key = NULL;
		}
		else
		{
			if (m_keys.empty())
			{
				key = m_root;
			}
			else
			{
				key = m_keys.front();
			}

			key = key->FindKey(keyName);
		}

		if (key != NULL)
		{
			m_keys.insert(m_keys.begin(), key);
		}

		return key;
	}

	CKey* CZAR::OpenKey(CKey* key)
	{
		if (key != NULL)
		{
			m_keys.insert(m_keys.begin(), key);
		}

		return key;
	}

	bool CZAR::Open(const char* name, int version, unsigned int mode, size_t padded_size)
	{
		bool readDirectory = false;

		if (name == NULL)
		{
			return false;
		}

		if (m_pFile == NULL)
		{
			m_pFileAlloc = new CFileIO();
			m_pFile = m_pFileAlloc;
		}

		bool openSuccessful = m_pFile->Open(name, mode);

		if (!openSuccessful)
		{
			return false;
		}

		char* filename = m_filename;
		
		if (filename != NULL && filename != "DEFAULT_ZAR_NAME")
		{
			if (filename == name)
			{
				// some goto crap
			}

			free(filename);
			m_filename = NULL;
		}

		if (name == NULL || name == "DEFAULT_ZAR_NAME")
		{
			m_filename = "DEFAULT_ZAR_NAME";
		}
		else
		{
			m_filename = strdup(name);
		}

		m_data_padded = padded_size;
		readDirectory = ReadDirectory(version, mode);
		
		if (readDirectory)
		{
			m_tail.appversion = version;
		}
		else
		{
			openSuccessful = false;
			if (m_pFile != NULL)
			{
				openSuccessful = m_pFile->IsOpen();
			}

			if (openSuccessful && (m_pFile->GetMode() & 6) != 0)
			{
				openSuccessful = false;

				if (m_pFile != NULL)
				{
					openSuccessful = m_pFile->IsOpen();
				}

				if (openSuccessful && m_modified)
				{
					WriteDirectory();
					m_modified = false;
				}
			}

			if (m_pFileAlloc == NULL && m_pFile != NULL)
			{
				m_pFile->Close();
			}
			else
			{
				m_pFileAlloc->Close();
				delete m_pFileAlloc;
				m_pFileAlloc = NULL;
				m_pFile = NULL;
			}

			m_key_buffer.clear();

			m_root->erase(m_root->begin(), m_root->begin());

			m_stable->Destroy();
		}

		return readDirectory;
	}

	void CZAR::Close()
	{
		unsigned int mode = 0;
		bool isOpen = false;
		bool isBufferOpen = false;

		if (m_pFile == NULL)
		{
			isOpen = false;
		}
		else
		{
			isOpen = m_pFile->IsOpen();
		}

		mode = m_pFile->GetMode();
		if (isOpen && (mode & 6) != 0)
		{
			isBufferOpen = false;

			if (m_pFile != NULL)
			{
				isBufferOpen = m_pFile->IsOpen();
			}

			if (isBufferOpen && m_modified)
			{
				WriteDirectory();
				m_modified = false;
			}
		}

		if (m_pFileAlloc == NULL && m_pFile != NULL)
		{
			m_pFile->Close();
		}
		else
		{
			m_pFileAlloc->Close();
			delete m_pFileAlloc;
			m_pFileAlloc = NULL;
			m_pFile = NULL;
		}

		m_key_buffer.clear();

		CKey* root = m_root;

		root->erase(root->begin(), root->end());
	}

	void CZAR::Close(bool clearBuffer)
	{
		if (m_pFileAlloc == NULL)
		{
			if (m_pFile != NULL)
			{
				m_pFile->Close();
			}
		}
		else
		{
			m_pFileAlloc->Close();
			delete m_pFileAlloc;
			m_pFileAlloc = NULL;
			m_pFile = NULL;
		}

		m_key_buffer.clear();

		CKey* key = m_root;

		key->erase(key->begin(), key->end());

		m_stable->Destroy();
	}

	void CZAR::CloseKeepDir()
	{
		m_pFile->Close();
	}

	CKey* CZAR::CreateKey(const char* name)
	{
		CKey* key = NULL;
		bool isOpen = false;

		if (m_pFile == NULL)
		{
			isOpen = false;
		}
		else
		{
			isOpen = m_pFile->IsOpen();
		}

		if (isOpen)
		{
			unsigned int mode = m_pFile->GetMode();

			if ((mode & 1) == 0)
			{
				char* keyName = m_stable->CreateString(name);
				key = new CKey(keyName);
			}
			else
			{
				if (name == NULL)
				{

				}
			}
		}

		return key;
	}

	void CZAR::CloseKey(CKey* key)
	{
		if (key == NULL && !m_keys.empty())
		{
			m_keys.erase(m_keys.begin());
		}
		else if (!m_keys.empty())
		{
			m_keys.erase(m_keys.begin());
		}
	}

	bool CZAR::Insert(zar::CKey* key, void* buf, size_t size)
	{
		int writeOffset = 0;
		unsigned char archiveCapacity = 0;
		bool success = false;

		if (buf != NULL && 0 < size)
		{
			int position = m_pFile->fseek(0, SEEK_END);
			success = position != -1;

			if (success)
			{
				int keySize = size;

				if (!m_bSecure)
				{
					writeOffset = m_pFile->fwrite(buf, size);
				}
				else
				{
					void* arrBuf = calloc(1, size);
					void* dest = arrBuf;
					memcpy(dest, buf, size);

					int offset = 0;
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

					writeOffset = m_pFile->fwrite(arrBuf, size);
					free(dest);
				}

				success = size == writeOffset;

				if (success)
				{
					key->m_offset = position;
					key->m_size = size;

					int keysPerLine = size % m_data_padded;
					keySize = 0;

					if (keysPerLine != 0)
					{
						keySize = m_data_padded - keysPerLine;
					}

					archiveCapacity = 175;

					if (!m_bSecure)
					{
						archiveCapacity = 80;
					}

					for (int i = 0; i < keySize; i++)
					{
						m_pFile->fwrite(&archiveCapacity, 1);
					}
				}
			}
		}
	}

	CKey* CZAR::Insert(const char* name, void* buf, size_t size)
	{
		CKey* newKey = NewKey(name);
		CKey* openKey = GetOpenKey();

		bool insertionSuccess = Insert(newKey, buf, size);

		if (!insertionSuccess && newKey != NULL)
		{
			delete newKey;
			newKey = NULL;
		}
		else
		{
			openKey->InsertKey(newKey);
		}

		return newKey;
	}

	CKey* CZAR::Insert(const char* name, unsigned int value)
	{
		CKey* newKey = NewKey(name);
		CKey* openKey = GetOpenKey();

		bool insertionSuccess = Insert(newKey, &value, sizeof(value));

		if (!insertionSuccess && newKey != NULL)
		{
			delete newKey;
			newKey = NULL;
		}
		else
		{
			openKey->InsertKey(newKey);
		}

		return newKey;
	}

	CKey* CZAR::Insert(const char* name, int value)
	{
		CKey* newKey = NewKey(name);
		CKey* openKey = GetOpenKey();

		bool insertionSuccess = Insert(newKey, &value, sizeof(value));

		if (!insertionSuccess && newKey != NULL)
		{
			delete newKey;
			newKey = NULL;
		}
		else
		{
			openKey->InsertKey(newKey);
		}

		return newKey;
	}

	bool CZAR::ReadDirectory(int appver, unsigned int mode)
	{
		int index = 0;
		int res = 0;
		int frontReserved = 0;
		size_t tailstableSize = 0;
		void* stablePtr = NULL;
		void* stableDest = NULL;
		CKey* rootKey;

		int flags;
		int key_count;
		size_t stable_size;
		int stable_ofs;
		int reserved[16];
		int tailReserved[16];
		int offset;
		int crc;
		int appversion;
		int version;

		size_t fileSize = 0;
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

		if (isOpen)
		{
			flags = 0;
			key_count = 0;
			stable_size = 0;
			stable_ofs = 0;
			reserved[0] = 0;
			reserved[1] = 0;
			reserved[2] = 0;
			reserved[3] = 0;
			reserved[4] = 0;
			reserved[5] = 0;
			reserved[6] = 0;
			reserved[7] = 0;
			reserved[8] = 0;
			reserved[9] = 0;
			reserved[10] = 0;
			reserved[11] = 0;
			reserved[12] = 0;
			reserved[13] = 0;
			reserved[14] = 0;
			reserved[15] = 0;
			offset = 0;
			crc = 0;
			appversion = 0;
			version = 0;

			fileSize = m_pFile->GetSize();

			if (fileSize == 0)
			{
				m_tail.flags = flags;
				m_tail.key_count = key_count;
				m_tail.stable_size = stable_size;
				m_tail.stable_ofs = stable_ofs;

				index = 8;

				do
				{
					index--;
					frontReserved = reserved[1];
					// reserved = reserved + 2;
					tailReserved[1] = frontReserved;
					// tailReserved = tailReserved + 2;
				} while (0 < index);

				m_tail.offset = offset;
				m_tail.crc = crc;
				m_tail.appversion = appversion;
				m_tail.version = version;
				m_tail.version = 0x20001;
				m_tail.appversion = appver;
				m_modified = true;
				m_pFile->fseek(0, SEEK_CUR);
				success = true;
			}
			else
			{
				fileSize = m_pFile->fseek(0xffffffffffffffa0, SEEK_END);

				success = fileSize != -1;

				if (success)
				{
					fileSize = m_pFile->fread(&flags, sizeof(TAIL));
					success = fileSize == sizeof(TAIL);
				}

				Unsecurify(&flags, sizeof(TAIL));

				if (success && version == 0x20001)
				{
					// reserved = reservedArr
					// tailReserved = m_tail.reserved;

					index = 8;

					m_tail.flags = flags;
					m_tail.key_count = key_count;
					m_tail.stable_size = stable_size;
					m_tail.stable_ofs = stable_ofs;

					do
					{
						index--;
						// frontReserved = reserved[1];
						// *tailReserved = *reserved;
						// reserved = reserved + 2;
						// tailReserved[1] = frontReserved;
						// tailReserved = tailReserved + 2;
					} while (0 < index);

					m_tail.offset = offset;
					m_tail.crc = crc;
					m_tail.appversion = appversion;
					m_tail.version = 0x20001;

					fileSize = m_pFile->fseek(offset, SEEK_CUR);
					success = fileSize != -1;

					if (success)
					{
						tailstableSize = m_tail.stable_size;
						stablePtr = malloc(tailstableSize);
						m_pFile->fread(stablePtr, tailstableSize);
						stableDest = stablePtr;

						Unsecurify(stableDest, tailstableSize);
						m_stable->Destroy();
						m_stable->LoadTable(stableDest, tailstableSize, true);

						index = m_tail.stable_ofs;
						m_key_buffer.clear();
						m_key_buffer.reserve(m_tail.key_count);
						rootKey = m_root;

						m_key_buffer.erase(m_key_buffer.begin(), m_key_buffer.end());

						CBufferIO* bufferIO = new CBufferIO();

						if (!m_memalign)
						{
							stablePtr = malloc(tailstableSize);
						}
						else
						{
							stablePtr = memalign(64, tailstableSize);
						}

						m_pFile->fread(stablePtr, tailstableSize);

						Unsecurify(stablePtr, tailstableSize);

						bufferIO->Open(stablePtr, tailstableSize);
						success = m_root->Read(this, bufferIO, (int)stableDest - index);

						bufferIO->Close();

						if ((mode & 0x20) == 0)
						{
							m_databuffer_size = m_tail.offset;
							tailstableSize = m_databuffer_size;

							if (tailstableSize != 0)
							{
								if (!m_memalign)
								{
									stableDest = malloc(tailstableSize);
									m_databuffer = stableDest;
								}
								else
								{
									stableDest = memalign(64, tailstableSize);
									m_databuffer = stableDest;
								}

								m_pFile->fseek(0, SEEK_CUR);
								m_pFile->fread(m_databuffer, m_databuffer_size);

								Unsecurify(m_databuffer, m_databuffer_size);

								if (m_pFileAlloc != NULL)
								{
									m_pFileAlloc->Close();
									delete m_pFileAlloc;

									m_pFile = NULL;
									m_pFileAlloc = NULL;

									CBufferIO* b = new CBufferIO();
									m_pFileAlloc = b;
									m_pFile = b;

									b->Open(m_databuffer, m_databuffer_size);
								}
							}
						}
					}
				}
			}
		}
		
		return success;
	}

	

	size_t CZAR::GetSize(const char* name)
	{
		CKey* key;

		if (m_keys.empty())
		{
			key = m_root;
		}
		else
		{
			key = m_root->front();
		}

		key = key->FindKey(name);

		if (key == NULL)
		{
			return -1;
		}
		else
		{
			return key->m_size;
		}

		return 0;
	}

	void* CZAR::ReleaseDataBuffer()
	{
		void* buffer = NULL;

		if (m_databuffer == NULL)
		{
			return NULL;
		}
		else
		{
			CBufferIO* fileAlloc = dynamic_cast<CBufferIO*>(m_pFile);

			if (fileAlloc != NULL)
			{
				fileAlloc->Release();
			}

			buffer = m_databuffer;
			m_databuffer = NULL;
		}

		return buffer;
	}

	/// <summary>
	/// Encrypts/secures the entire ZAR memory region.
	/// Performs a pass where all eight bytes per memory line are inverted.
	/// Basic encryption, but not secure.
	/// </summary>
	void CZAR::Securify(void* buf, size_t size)
	{
		int line = 0;

		if (m_bSecure && 0 < size)
		{
			if (8 < size)
			{
				do
				{
					// Yes, I know this fucking sucks.
					unsigned char* byte = (unsigned char*)((int)buf + line);
					line += 8;
					byte[0] = ~byte[0];
					byte[1] = ~byte[1];
					byte[2] = ~byte[2];
					byte[3] = ~byte[3];
					byte[4] = ~byte[4];
					byte[5] = ~byte[5];
					byte[6] = ~byte[6];
					byte[7] = ~byte[7];
				} while (line < size - 8);
			}

			for (; line < size; line++)
			{
				unsigned char* byte = (unsigned char*)((int)buf + line);
				byte[line] = ~byte[line];
			}
		}
	}

	/// <summary>
	/// Similar to CZAR::Securify, but inverts all bytes belonging to a ZAR memory region,
	/// exposing its contents.
	/// </summary>
	void CZAR::Unsecurify(void* buf, size_t size)
	{
		int line = 0;

		if (m_bSecure && 0 < size)
		{
			if (8 < size)
			{
				do
				{
					// Yes, I know this fucking sucks.
					unsigned char* byte = (unsigned char*)((int)buf + line);
					line += 8;
					byte[0] = ~byte[0];
					byte[1] = ~byte[1];
					byte[2] = ~byte[2];
					byte[3] = ~byte[3];
					byte[4] = ~byte[4];
					byte[5] = ~byte[5];
					byte[6] = ~byte[6];
					byte[7] = ~byte[7];
				} while (line < size - 8);
			}

			for (; line < size; line++)
			{
				unsigned char* byte = (unsigned char*)((int)buf + line);
				byte[line] = ~byte[line];
			}
		}
	}
}