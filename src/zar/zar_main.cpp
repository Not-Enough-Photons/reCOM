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
		stable = NULL;
		name = "";
		version = 0x20001;
		
		stable = new CSTable(0, 1024);
		const char* zarName = name;

		if (zarName != 0 && zarName != DEFAULT_ZAR_NAME)
		{
			if (zarName == name)
			{
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
			io = new CIO();

			if (dynamic_cast<CFileIO*>(io) != NULL)
			{
				io = reinterpret_cast<CIO*>(new CFileIO());
			}

			fileIO = reinterpret_cast<CFileIO*>(io);
		}

		this->io = io;
		count = 16;
		root = new CKey(DEFAULT_ZAR_NAME);
	}

	CKey* CZAR::NewKey(const char* name)
	{

	}

	CKey* CZAR::FindKey(const char* name)
	{
		CKey* parent;

		if (keys.empty())
		{
			parent = root;
		}
		else
		{
			parent = keypairs.second();
		}

		CKey* child;
		if (parent != NULL)
		{
			child = parent->FindKey(name);
		}

		return child;
	}

	CKey* CZAR::OpenKey(const char* key)
	{
		if (io == NULL)
		{

		}
	}

	void CZAR::CloseKey(CKey* key)
	{
		CKey* target;
	}

	size_t CZAR::GetSize(const char* name)
	{
		zar::CKey* key;

		if (field_0x4 == 0)
		{
			key = root;
		}
		else
		{

		}
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

	undefined4 CZAR::ReleaseDataBuffer()
	{
		CBufferIO* buffer;
		undefined4 uVar1 = 0;

		if (field15_0x18 == 0)
		{
			uVar1 = 0;
		}
		else
		{
			// buffer = dynamic_cast<CBufferIO*>(field14_0x14);
			if (buffer != NULL)
			{
				buffer->Release();
			}

			uVar1 = field15_0x18;
			field15_0x18 = 0;
		}

		return uVar1;
	}
}