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

		void SetStream(zdb::CFileIO* stream);
		zdb::CFileIO GetStream() const;

		zdb::CSTable GetStringTable() const;
	private:
		int32_t m_PaddingMaybe;
		int32_t m_Flags;
		zdb::CSTable* m_StringTable;
		std::string m_Name;
		zdb::CFileIO* m_Stream;
		zdb::CFileIO* m_StreamShallowCopy;
	};

	static void ZARMain(CZAR* archive, char* resourcePath, void* param_3, void* param_4);
}