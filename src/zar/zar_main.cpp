#include "zar_main.h"

namespace zar
{
	void CZAR::Fetch(const char* key, undefined4 param_3)
	{
		bool ok = false;

		if (GetOpenKey() == 0)
		{
			ok = false;
		}
		else
		{
			CKey* zarKey = CKey::FindKey(key);
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
			CKey* zarKey = CKey::FindKey(key);
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