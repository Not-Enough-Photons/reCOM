#include "zar_main.h"

namespace zar
{
	CKey* CZAR::NewKey(const char* name)
	{

	}

	size_t CZAR::GetSize(const char* name)
	{
		zar::CKey* key;

		if (field_0x4 == 0)
		{
			key = mainkey;
		}
		else
		{

		}
	}

	CKey* CKey::FindKey(const char* name)
	{
		CKey* found;
		std::list<CKey*>::iterator begin = m_keys.begin();
		std::list<CKey*>::iterator end = m_keys.end();
		
		for (std::list<CKey*>::iterator it = begin; it != end; it++)
		{
			
		}

		return found;
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
			buffer = dynamic_cast<CBufferIO*>(field14_0x14);
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