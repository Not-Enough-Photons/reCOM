#pragma once
#include <cstdint>
#include <fstream>

namespace zdb
{
	typedef struct ZDBHeader
	{
		int32_t identifier;
		int32_t version;
		uint8_t unknown_00;
		uint8_t count_offset;
		int32_t zero_padding;
	} zdb_header_t;

	typedef struct ZDBExternalRefEntry
	{
	} zdb_extern_ref_t;
}