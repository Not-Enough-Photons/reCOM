#pragma once
#include <string>

#include "reader/zrdr_main.h"
#include "util/util_stable.h"

namespace zar
{
	class CZAR
	{
	public:
		CZAR(const char* name, char* param_2);

		void SetName(std::string name);
		std::string GetName() const;

		void SetStream(CFileIO* stream);
		CFileIO GetStream() const;

		CSTable GetStringTable() const;
	private:
		int32_t m_PaddingMaybe;
		int32_t m_Flags;
		CSTable* m_StringTable;
		std::string m_Name;
		CFileIO* m_Stream;
		CFileIO* m_StreamShallowCopy;
	};

	static void ZARMain(CZAR* archive, char* resourcePath, void* param_3, void* param_4);
}