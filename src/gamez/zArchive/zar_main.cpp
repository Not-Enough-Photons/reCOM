#include <freebsd/strcasecmp.h>

#include "zar.h"

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

	CKey::~CKey()
	{
		clear();
	}

	CKey* CKey::InsertKey(CKey* key)
	{
		insert(begin(), key);
		return key;
	}

	CKey* CKey::FindKey(const char* name)
	{
		auto begin = this->begin();
		auto end = this->end();
		std::list<CKey*>::iterator it;

		for (it = begin; it != end; it++)
		{
			CKey* current = *it;

			if (current->m_size != -1 && strcasecmp(current->m_name, name) == 0)
			{
				break;
			}
		}

		if (it != end)
		{
			return *it;
		}

		return NULL;
	}

	bool CKey::Read(CZAR* archive, CBufferIO* buffer, s64 stableOffset)
	{
		struct KEY
		{
			s32 m_name;
			u32 m_offset;
			u32 m_size;
			u32 m_count;
		} key_t;

		buffer->fread(&key_t, sizeof(KEY));

		if (archive->m_root != this)
		{
			m_name = (char*)key_t.m_name + stableOffset;
			m_size = key_t.m_size;
			m_offset = key_t.m_offset;
		}

		while (key_t.m_count != 0)
		{
			CKey* archiveKey = archive->NewKey(NULL);
			archiveKey->Read(archive, buffer, stableOffset);
			insert(end(), archiveKey);
			key_t.m_count--;
		}

		return true;
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

		return true;
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
					m_pFileAlloc = new CFileIO();
				}

				m_pFile = new CBufferIO();

				m_data_padded = 16;

				m_root = new CKey("DEFAULT_ZAR_NAME");

				return;
			}

			free(m_filename);
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
			m_pFileAlloc = new CFileIO();
		}

		m_pFile = new CBufferIO();

		m_data_padded = 16;

		m_root = new CKey("DEFAULT_ZAR_NAME");
	}

	CZAR::~CZAR()
	{
		if (m_pFile != NULL)
		{
			if (m_pFile->IsOpen() && (m_pFile->GetMode() & 6) != 0)
			{

			}
		}
	}

	void CZAR::Close()
	{
		u32 mode = 0;
		bool isOpen = false;
		bool isBufferOpen = false;

		if (m_pFile == NULL)
		{
			isOpen = false;
			return;
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

		// TODO:
		// Redo this function definition

		return key;
	}

	CKey* CZAR::NewKey(const char* name)
	{
		CKey* key;

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
		if (key == NULL)
		{
			return NULL;
		}

		m_keys.insert(m_keys.begin(), key);
		return key;
	}

	CKey* CZAR::GetOpenKey() const
	{
		CKey* key;

		if (m_keys.empty())
		{
			key = m_root;
		}
		else
		{
			key = m_keys.front();
		}

		return key;
	}

	bool CZAR::Open(const char* name, s32 version, u32 mode, size_t padded_size)
	{
		if (name == NULL)
		{
			return false;
		}

		if (m_pFile == NULL)
		{
			m_pFileAlloc = new CFileIO();
			m_pFile = new CBufferIO();
		}

		bool isOpen = m_pFileAlloc->Open(name);

		if (!isOpen)
		{
			return false;
		}

		if (m_filename != NULL && m_filename != "DEFAULT_ZAR_NAME")
		{
			if (m_filename == name)
			{
				m_data_padded = padded_size;

				bool success = ReadDirectory(version, mode);

				if (success)
				{
					m_tail.appversion = version;
				}
				else
				{
					isOpen = false;

					if (m_pFile != NULL)
					{
						isOpen = m_pFile->IsOpen();
					}

					if (isOpen)
					{
						isOpen = false;

						if (m_pFile == NULL)
						{
							isOpen = m_pFile->IsOpen();
						}

						if (isOpen && m_modified)
						{
							WriteDirectory();
							m_modified = false;
						}
					}

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
					m_root->erase(m_root->begin(), m_root->end());
					m_stable->Destroy();
				}
			}

			free(&m_filename);
			m_filename = NULL;
		}

		if (name == NULL && name == "DEFAULT_ZAR_NAME")
		{
			m_filename = "DEFAULT_ZAR_NAME";
		}
		else
		{
			m_filename = strdup(name);
		}

		m_data_padded = padded_size;

		bool success = ReadDirectory(version, mode);

		if (success)
		{
			m_tail.appversion = version;
		}
		else
		{
			isOpen = false;

			if (m_pFile != NULL)
			{
				isOpen = m_pFile->IsOpen();
			}

			if (isOpen)
			{
				isOpen = false;

				if (m_pFile == NULL)
				{
					isOpen = m_pFile->IsOpen();
				}

				if (isOpen && m_modified)
				{
					WriteDirectory();
					m_modified = false;
				}
			}

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
			m_root->erase(m_root->begin(), m_root->end());
			m_stable->Destroy();
		}

		return success;
	}

	bool CZAR::ReOpen(s32 appver, s32 mode)
	{
		if (m_pFileAlloc == NULL)
		{
			return false;
		}
		
		if (m_pFileAlloc->IsOpen())
		{
			char* name = m_filename;

			if (name)
			{
				if (!m_pFileAlloc)
				{
					m_pFileAlloc = new CFileIO();
					m_pFile = new CBufferIO();
				}

				if (m_pFileAlloc->Open(name))
				{
					SetFilename(name);
					m_data_padded = 16;

					if (ReadDirectory(appver, mode))
					{
						m_tail.appversion = appver;
					}
					else
					{
						Close();
					}
				}
			}
		}
		else
		{
			return true;
		}

		return false;
	}

	void CZAR::CloseKey(CKey* key)
	{
		if (key != NULL && !m_keys.empty())
		{
			m_keys.erase(m_keys.begin());
		}
	}

	bool CZAR::Insert(zar::CKey* key, void* buf, size_t size)
	{
		s32 writeOffset = 0;
		char padChar = 0;
		bool success = false;

		if (buf != NULL && 0 < size)
		{
			s32 position = m_pFile->fseek(0, SEEK_END);
			success = position != -1;

			if (success)
			{
				s32 keySize = size;

				if (!m_bSecure)
				{
					writeOffset = m_pFile->fwrite(buf, size);
				}
				else
				{
					void* arrBuf = calloc(1, size);
					void* dest = arrBuf;
					memcpy(dest, buf, size);

					ZAR_SECURE(m_bSecure, buf, size)
				}

				success = size == writeOffset;

				if (success)
				{
					key->m_offset = position;
					key->m_size = size;

					s32 keysPerLine = size % m_data_padded;
					keySize = 0;

					if (keysPerLine != 0)
					{
						keySize = m_data_padded - keysPerLine;
					}

					padChar = '�';

					if (!m_bSecure)
					{
						padChar = 'P';
					}

					for (s32 i = 0; i < keySize; i++)
					{
						m_pFile->fwrite(&padChar, 1);
					}
				}
			}
		}

		return success;
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

	CKey* CZAR::Insert(const char* name, u32 value)
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

	CKey* CZAR::Insert(const char* name, s32 value)
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

	bool CZAR::ReadDirectory(s32 appver, u32 mode)
	{
		bool success = false;

		if (m_pFileAlloc == NULL)
		{
			return false;
		}

		if (!m_pFileAlloc->IsOpen())
		{
			return false;
		}

		s32 position = m_pFileAlloc->fseek(0xffffffffffffffa0, SEEK_END);
		size_t size = 0;

		if (position != -1)
		{
			size = m_pFileAlloc->fread(&m_tail, sizeof(TAIL));
		}
		else if (position == -1)
		{
			return false;
		}

		if (size == sizeof(TAIL) && m_tail.version == 0x20001)
		{
			position = m_pFileAlloc->fseek(m_tail.offset, SEEK_SET);

			if (position != -1)
			{
				int stable_size = m_tail.stable_size;
				void* stable_ptr = malloc(stable_size);

				m_pFileAlloc->fread(stable_ptr, stable_size);

				m_stable->Destroy();
				m_stable->LoadTable(stable_ptr, stable_size, true);

				int ofs = m_tail.stable_ofs;
				m_key_buffer.clear();
				m_key_buffer.reserve(m_tail.key_count);

				CKey* root_key = m_root;
				root_key->erase(root_key->begin(), root_key->end());

				CBufferIO bufferIO;

				size_t key_size = (s64)m_tail.key_count << 4;
				void* key_ptr = malloc(key_size);

				m_pFileAlloc->fread(key_ptr, key_size);
				Unsecurify(key_ptr, key_size);

				bufferIO.Open(key_ptr, key_size);

				m_root->Read(this, &bufferIO, (s64)stable_ptr - ofs);
				bufferIO.Close();

				m_databuffer_size = m_tail.offset;
				size = m_databuffer_size;

				if (size != 0)
				{
					m_databuffer = malloc(size);

					m_pFileAlloc->fseek(0, SEEK_SET);
					m_pFileAlloc->fread(m_databuffer, m_databuffer_size);
					Unsecurify(m_databuffer, m_databuffer_size);

					if (m_pFileAlloc != NULL)
					{
						m_pFileAlloc->Close();
						delete m_pFileAlloc;

						m_pFile = NULL;
						m_pFileAlloc = NULL;

						m_pFileAlloc = new CFileIO();
						m_pFile = new CBufferIO();

						m_pFile->Open(m_databuffer, m_databuffer_size);
					}
				}

				success = true;
			}
		}
		else
		{
			success = false;
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

	void CZAR::SetFilename(const char* name)
	{
		if (m_filename != NULL && m_filename != "DEFAULT_ZAR_NAME")
		{
			if (name == m_filename)
			{
				return;
			}

			zfree(m_filename);
			m_filename = NULL;
		}

		if (name == NULL || name == "DEFAULT_ZAR_NAME")
		{
			m_filename = "DEFAULT_ZAR_NAME";
		}
		else
		{
			m_filename = zstrdup(name);
		}
	}

	void CZAR::Securify(void* buf, size_t size)
	{
		ZAR_SECURE(m_bSecure, buf, size)
	}

	void CZAR::Unsecurify(void* buf, size_t size)
	{
		ZAR_SECURE(m_bSecure, buf, size)
	}
}