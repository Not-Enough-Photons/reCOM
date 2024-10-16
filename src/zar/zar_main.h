#pragma once
#include <string>

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
		void* ReadDirectory();
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

	};
}