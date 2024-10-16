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
}