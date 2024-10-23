#pragma once
#include <string>
#include <list>

#include "boost/compressed_pair.hpp"

#include "placeholder.h"
#include "reader/zrdr_main.h"
#include "util/util_stable.h"

namespace zar
{
	const char* DEFAULT_ZAR_NAME = "ROOT";

	class CKey
	{
	public:
		CKey(const char* name);

		CKey* InsertKey(CKey* key);
		CKey* FindKey(const char* key);
	private:
		std::list<CKey*> keys;
		const char* name;
		int size;
		int field14_0x14;
	};

	class CZAR
	{
	public:
		CZAR(const char* name, CIO* io);

		void Open();

		CKey* CreateKey();
		CKey* NewKey(const char* name);

		CKey* OpenKey(const char* name);
		CKey* FindKey(const char* name);
		void CloseKey(CKey* key);

		void* ReadDirectory();
		void SetFileName();
		size_t GetSize(const char* key);

		void Fetch(const char* key, undefined4 param_3);
		bool Fetch(const char* key, undefined8 param_3);
		bool Fetch(const char* key, undefined param_3, undefined8 param_4);

		CKey* GetOpenKey();

		undefined4 ReleaseDataBuffer();
	private:
		const char* name;
		int version;

		int* field_0x4;
		int field15_0x18;
		CIO* io;
		CFileIO* fileIO;

		CSTable* stable;

		CKey* root;
		std::list<CKey*> keys;
		boost::compressed_pair<char, CKey*> keypairs;
		int count;
	};
}