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
		CKey();
		CKey(const char* name);
		~CKey();

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
		~CZAR();

		void Open();

		CKey* CreateKey();
		CKey* NewKey(const char* name);

		CKey* OpenKey(const char* name);
		CKey* FindKey(const char* name);
		void CloseKey(CKey* key);

		bool Insert(CKey* key, void* buf, int size);

		void* ReadDirectory();
		void SetFileName();
		size_t GetSize(const char* key);

		void Fetch(const char* key, undefined4 param_3);
		bool Fetch(const char* key, undefined8 param_3);
		bool Fetch(const char* key, undefined param_3, undefined8 param_4);

		CKey* GetOpenKey();

		void* ReleaseDataBuffer();
	private:
		const char* name;
		int version;

		int count;
		int seekPosition;

		CKey* root;

		CBufferIO* bufferIO;
		CFileIO* fileIO;
		void* buffer;

		CSTable* stringTable;

		std::list<CKey*> keys;
	};
}