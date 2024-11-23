#include "zar.h"

#include "gamez/zUtil/util_main.h"

namespace zar
{
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

	CKey* CKey::FindKey(char* name)
	{
		auto begin = this->begin();
		auto end = this->end();

		for (auto it = begin; it != end; it++)
		{
			CKey* current = *it;
		}
	}

	bool CKey::Read(CZAR* file, CIO* fileBuffer, int offset)
	{

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
		fileIO = NULL;
		root = NULL;
		stringTable = NULL;
		name = "";
		memset(buffer, 0, 96);
		version = 0x20001;
		
		stringTable = new CSTable(0, 1024);
		const char* zarName = name;

		if (zarName != 0 && zarName != DEFAULT_ZAR_NAME)
		{
			if (zarName == name)
			{
				if (io == NULL)
				{
					io = new CFileIO();
					fileIO = reinterpret_cast<CFileIO*>(io);
				}

				bufferIO = reinterpret_cast<CBufferIO*>(io);
				count = 16;
				root = new CKey(DEFAULT_ZAR_NAME);

				return;
			}
			
			this->name = 0;
		}

		if (name == 0 || name == DEFAULT_ZAR_NAME)
		{
			this->name = DEFAULT_ZAR_NAME;
		}
		else
		{
			zarName = strdup(name);
			this->name = zarName;
		}

		if (io == NULL)
		{
			io = new CFileIO();
			fileIO = reinterpret_cast<CFileIO*>(io);
		}

		bufferIO = reinterpret_cast<CBufferIO*>(io);
		count = 16;
		root = new CKey(DEFAULT_ZAR_NAME);
	}

	CKey* CZAR::NewKey(const char* name)
	{
		CKey* newKey;
		OpenFlags mode = fileIO->GetMode();

		if ((mode & OpenFlags::READ) == 0)
		{
			const char* str = stringTable->CreateString(name);
			newKey = new CKey(str);
		}
		else
		{
			if (name == 0)
			{
				CKey* insert = new CKey();
			}
			else
			{

			}
		}
	}

	CKey* CZAR::FindKey(const char* name)
	{

	}

	CKey* CZAR::OpenKey(const char* key)
	{
		if (bufferIO == NULL)
		{

		}
	}

	void CZAR::Open(char* name, int version, OpenFlags mode, int count)
	{
		if (!string_exists(name))
		{
			return;
		}

		if (bufferIO == NULL)
		{
			fileIO = new CFileIO();
			bufferIO = new CBufferIO();
		}

		int fd = bufferIO->Open(name, mode);

		if (fd == 0)
		{
			return;
		}

		this->count = count;

	}

	void CZAR::CloseKey(CKey* key)
	{
		CKey* target;
	}

	bool CZAR::Insert(zar::CKey* key, void* buf, int size)
	{
		bool valid = false;

		if (buf != NULL && size > 0)
		{
			int seekPos = bufferIO->fseek(0, SEEK_SET);
			valid = seekPos != -1;

			if (valid)
			{
				int written = bufferIO->fwrite(buf, size);
				valid = size == written;

				if (valid)
				{
					seekPosition = seekPos;
					size = size;
					written = size % count;

					int countOffset = 0;

					if (written == 0)
					{
						countOffset = 0;
					}
					else
					{
						countOffset = count - written;
					}

					int* localBuf = new int;
					*localBuf = 175;
					for (int i = 0; i < countOffset; i++)
					{
						bufferIO->fwrite(&localBuf, 1);
					}
				}
			}
		}

		return valid;
	}

	size_t CZAR::GetSize(const char* name)
	{

	}

	void CZAR::Fetch(const char* key, undefined4 param_3)
	{
		bool ok = false;

		if (GetOpenKey() == 0)
		{
			ok = false;
		}
		else
		{
			// CKey* zarKey = CKey::FindKey(key);
			// ok = Fetch(...);
		}

		if (!ok)
		{
			// result != '\0';
		}
	}

	bool CZAR::Fetch(const char* key, undefined8 param_3)
	{
		bool ok = false;

		if (GetOpenKey() == 0)
		{
			ok = false;
		}
		else
		{
			// CKey* zarKey = CKey::FindKey(key);
			// ok = Fetch(...);
		}

		return ok != false;
	}

	void* CZAR::ReleaseDataBuffer()
	{
		CBufferIO* bufferIO;
		void* buf = 0;

		if (this->buffer == NULL)
		{
			buf = NULL;
		}
		else
		{
			// bufferIO = dynamic_cast<CIO*>(bufferIO);
			if (bufferIO != NULL)
			{
				bufferIO->Release();
			}

			buf = this->buffer;
			this->buffer = NULL;
		}

		return buf;
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
					unsigned char* byte = reinterpret_cast<unsigned char*>((int)buf + line);
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
				unsigned char* byte = reinterpret_cast<unsigned char*>((int)buf + line);
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
					unsigned char* byte = reinterpret_cast<unsigned char*>((int)buf + line);
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
				unsigned char* byte = reinterpret_cast<unsigned char*>((int)buf + line);
				byte[line] = ~byte[line];
			}
		}
	}
}