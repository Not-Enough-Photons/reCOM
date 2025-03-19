#include "zar.h"
#include "Apps/FTS/gamever.h"
#include "gamez/zUtil/zutil.h"
#include "SDL3/SDL_stdinc.h"

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

			if (current->m_size != -1 && SDL_strcasecmp(current->m_name, name) == 0)
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

	bool CKey::Write(CZAR* archive)
	{
		archive->Securify(m_name, 4);
		archive->m_pFile->fwrite(m_name, 4);
		archive->Unsecurify(m_name, 4);

		archive->Securify(&m_offset, 4);
		archive->m_pFile->fwrite(&m_offset, 4);
		archive->Unsecurify(&m_offset, 4);

		archive->Securify(&m_size, 4);
		archive->m_pFile->fwrite(&m_size, 4);
		archive->Unsecurify(&m_size, 4);

		archive->Securify(this, 4);
		archive->m_pFile->fwrite(this, 4);
		archive->Unsecurify(this, 4);

		auto begin = this->begin();
		auto end = this->end();

		for (auto it = begin; it != end; ++it)
		{
			CKey* key = *it;
			key->Write(archive);
		}

		return true;
	}

	bool CKey::Write(CZAR* archive, FILE* file)
	{
		archive->Securify(m_name, 4);
		fwrite(m_name, 1, sizeof(s32), file);
		archive->Unsecurify(m_name, 4);

		archive->Securify(&m_offset, 4);
		fwrite(&m_offset, 1, sizeof(s32), file);
		archive->Unsecurify(&m_offset, 4);

		archive->Securify(&m_size, 4);
		fwrite(&m_size, 1, sizeof(s32), file);
		archive->Unsecurify(&m_size, 4);

		archive->Securify(this, 4);
		fwrite(this, 1, sizeof(s32), file);
		archive->Unsecurify(this, 4);

		auto begin = this->begin();
		auto end = this->end();

		for (auto it = begin; it != end; ++it)
		{
			CKey* key = *it;
			key->Write(archive, file);
		}

		return true;
	}

	void CKey::fixupKey(CSTable* table, CKey* key)
	{
		char* keyname = table->FindString(key->m_name);
		key->m_name = keyname;

		auto key_iterator = key->begin();

		while (key_iterator != key->end())
		{
			CKey* child = *key_iterator;

			char* childname = table->FindString(child->m_name);
			child->m_name = childname;

			auto child_iterator = child->begin();
			while (child_iterator != child->end())
			{
				fixupKey(table, *child_iterator);
				++child_iterator;
			}
			
			++key_iterator;
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

		if (m_filename && m_filename != "DEFAULT_ZAR_NAME")
		{
			if (m_filename == name)
			{
				m_data_padded = padded_size;

				bool success = false;
				
				if (GetGame() == game_SOCOM1_BETA)
				{
					success = ReadDirectory(version, mode);
				}
				else if (GetGame() == game_SOCOM1 || GetGame() == game_SOCOM2_BETA)
				{
					success = ReadDirectory_V2(version, mode);
				}

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

			zfree(m_filename);
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

		bool success = false;
				
		if (GetGame() == game_SOCOM1_BETA)
		{
			success = ReadDirectory(version, mode);
		}
		else if (GetGame() == game_SOCOM1 || GetGame() == game_SOCOM2_BETA)
		{
			success = ReadDirectory_V2(version, mode);
		}

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

					if (GetGame() == game_SOCOM1_BETA)
					{
						if (ReadDirectory(appver, mode))
						{
							m_tail.appversion = appver;
						}
						else
						{
							Close();
						}	
					}
					else if (GetGame() == game_SOCOM1 || GetGame() == game_SOCOM2_BETA)
					{
						if (ReadDirectory_V2(appver, mode))
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

		size_t position = m_pFileAlloc->fseek(-96, SEEK_END);
		size_t size = 0;

		if (position != -1)
		{
			size = m_pFileAlloc->fread(&m_tail, sizeof(TAIL));
		}
		else if (position == -1)
		{
			return false;
		}

		if (size == sizeof(TAIL) && m_tail.version == ZAR_VERSION_1)
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

	bool CZAR::ReadDirectory_V2(s32 appver, u32 mode)
	{
		s32 padding = 0;
		s32 key_ofs = 0;
		
		bool success = false;

		if (m_pFileAlloc == NULL)
		{
			return false;
		}

		if (!m_pFileAlloc->IsOpen())
		{
			return false;
		}

		size_t position = m_pFileAlloc->fseek(0, SEEK_SET);
		size_t size = 0;

		if (position != -1)
		{
			size = m_pFileAlloc->fread(&m_head, sizeof(HEAD));
		}
		else if (position == -1)
		{
			return false;
		}

		Unsecurify(&m_head, sizeof(HEAD));
		
		if (size == sizeof(HEAD) && m_head.version == ZAR_VERSION_2)
		{
			s32 stable_size = m_head.stable_size;
			void* stable_ptr = zmalloc(stable_size);

			m_pFileAlloc->fread(stable_ptr, stable_size);

			Unsecurify(stable_ptr, stable_size);

			m_stable->Destroy();
			m_stable->LoadTable(stable_ptr, stable_size, true);

			s32 ofs = m_head.stable_ofs;
			m_key_buffer.clear();
			m_key_buffer.reserve(m_head.key_count);
			
			m_root->erase(m_root->begin(), m_root->end());

			CBufferIO bufferIO;

			size_t key_size = (s64)m_head.key_count * 16;
			void* key_ptr = malloc(key_size);

			m_pFileAlloc->fread(key_ptr, key_size);
			Unsecurify(key_ptr, key_size);

			bufferIO.Open(key_ptr, key_size);

			success = m_root->Read(this, &bufferIO, (s64)stable_ptr - ofs);
			bufferIO.Close();

			padding = m_head.padding;
			key_ofs = key_size + stable_size + sizeof(HEAD);
			s32 calc_alignment = key_ofs % padding;
	
			if (calc_alignment == 0)
			{
				padding = 0;
			}
			else
			{
				padding = padding - calc_alignment;
			}

			m_pFileAlloc->fseek(padding, SEEK_CUR);

			if ((mode & 32) == 0)
			{
				if (size != 0)
				{
					m_databuffer_size = m_head.offset;
					m_databuffer = zmalloc(m_databuffer_size);
					m_rootOffset = padding + key_ofs;
					m_pFileAlloc->fseek(m_rootOffset, SEEK_CUR);
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
						m_rootOffset = 0;
					}
				}
			}
			else
			{
				m_rootOffset = padding + key_ofs;
			}
		}

		return success;
	}

	bool CZAR::WriteDirectory()
	{
		bool success = false;

		if (m_pFile && m_pFile->IsOpen())
		{
			u32 pos = m_pFile->fseek(0, SEEK_END);
			success = pos != -1;
			
			if (success)
			{
				m_tail.version = ZAR_VERSION_1;
				m_tail.offset = m_pFile->ftell();
				m_tail.key_count = _countKeys(m_root);
				m_stable->Pack(CKey::fixupKey, m_root);
				m_tail.stable_size = m_stable->m_bytes;
				m_tail.stable_ofs = (s32)m_stable->m_buffer;

				if (!m_bSecure)
				{
					m_pFile->fwrite(m_stable->m_buffer, m_stable->m_bytes);
				}
				else
				{
					void* array = zcalloc(1, m_stable->m_bytes);
					memcpy(array, m_stable->m_buffer, m_stable->m_bytes);
					Securify(array, m_stable->m_bytes);
					m_pFile->fwrite(array, m_stable->m_bytes);
					zfree(array);
				}

				m_root->Write(this);
				Securify(&m_tail, sizeof(TAIL));
				m_pFile->fwrite(&m_tail, sizeof(TAIL));
				Unsecurify(&m_tail, sizeof(TAIL));
			}

			m_modified = false;
		}

		return success;
	}

	bool CZAR::WriteDirectory(FILE* file)
	{
		bool success = false;

		if (file)
		{
			fwrite((void*)m_pFile->m_file, 1, m_pFile->m_filesize, file);
			
			if (fseek(file, 0, SEEK_END) != -1)
			{
				m_tail.version = ZAR_VERSION_1;
				m_tail.offset = ftell(file);
				m_tail.key_count = _countKeys(m_root);
				m_stable->Pack(CKey::fixupKey, m_root);
				m_tail.stable_size = m_stable->m_bytes;
				m_tail.stable_ofs = (s32)m_stable->m_buffer;

				if (!m_bSecure)
				{
					fwrite(m_stable->m_buffer, 1, m_stable->m_bytes, file);
					s32 pos = ftell(file);
					s32 align = pos % 16;
					s32 nextpos = 16 - align;
					char padding = '\0';

					for (u32 i = 0; i < nextpos; i++)
					{
						fwrite(&padding, 1, 1, file);
					}
				}
				else
				{
					void* array = zcalloc(1, m_stable->m_bytes);
					memcpy(array, m_stable->m_buffer, m_stable->m_bytes);
					Securify(array, m_stable->m_bytes);
					m_pFile->fwrite(array, m_stable->m_bytes);
					zfree(array);
				}

				m_root->Write(this, file);
				Securify(&m_tail, sizeof(TAIL));
				fwrite(&m_tail, 1, sizeof(TAIL), file);
				Unsecurify(&m_tail, sizeof(TAIL));
			}

			m_modified = false;
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
		
		CBufferIO* fileAlloc = dynamic_cast<CBufferIO*>(m_pFile);

		if (fileAlloc != NULL)
		{
			fileAlloc->Release();
		}

		buffer = m_databuffer;
		m_databuffer = NULL;

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
