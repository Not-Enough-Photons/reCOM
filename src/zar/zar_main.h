#pragma once
#include <string>
#include <list>

#include "placeholder.h"
#include "reader/zrdr_main.h"
#include "util/util_stable.h"

namespace zar
{
	const char* g_DefaultArchiveName = "ROOT";

	class CZAR
	{
	public:
		CZAR(const char* name, char* param_2);

		void Open();
		CKey* CreateKey();
		CKey* NewKey(const char* name);
		void* ReadDirectory();
		void SetFileName();
		size_t GetSize(const char* key);

		void Fetch(const char* key, undefined4 param_3);
		bool Fetch(const char* key, undefined8 param_3);
		bool Fetch(const char* key, undefined param_3, undefined8 param_4);

		CKey* GetOpenKey();

		undefined4 ReleaseDataBuffer();
	private:
		int* field_0x4;
		int field15_0x18;
		CIO* field14_0x14;
		CKey* mainkey;
	};

	class CKey
	{
	public:
		CKey* FindKey(const char* key);
	private:
		std::list<CKey*> m_keys;
	};
}