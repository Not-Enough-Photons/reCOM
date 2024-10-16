#pragma once
#include <string>

#include "reader/zrdr_main.h"
#include "util/util_stable.h"

typedef char undefined;
typedef int undefined4;
typedef long undefined8;

namespace zar
{
	const char* g_DefaultArchiveName = "ROOT";

	class CZAR
	{
	public:
		CZAR(const char* name, char* param_2);

		void Open();
		CKey* CreateKey();
		void* ReadDirectory();
		void SetFileName();
		size_t GetSize(const char* key);

		void Fetch(const char* key, undefined4 param_3);
		bool Fetch(const char* key, undefined8 param_3);
		bool Fetch(const char* key, undefined param_3, undefined8 param_4);

		CKey* GetOpenKey();
	private:
		int32_t m_PaddingMaybe;
		int32_t m_Flags;
		CSTable* m_StringTable;
		std::string m_Name;
		CFileIO* m_Stream;
		CFileIO* m_StreamShallowCopy;
	};

	class CKey
	{
	public:
		static CKey* FindKey(const char* key);
	};
}