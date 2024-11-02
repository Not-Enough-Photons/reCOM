#include "zar_main.h"

namespace zar
{
	CKey::CKey(const char* name)
	{
		this->name = name;
		size = 0;
		field14_0x14 = 0;
	}

	CKey* CKey::InsertKey(CKey* key)
	{
		keys.insert(keys.begin(), key);
		return key;
	}

	CKey* CKey::FindKey(const char* name)
	{
		auto begin = keys.begin();
		auto end = keys.end();

		for (auto it = begin; it != end; it++)
		{
			CKey* current = *it;
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
}