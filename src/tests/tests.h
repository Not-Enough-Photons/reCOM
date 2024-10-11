#pragma once
#include "reader/zrdr_main.h"

static void test_ReaderHashing(const char* parentReader, const char* childReader)
{
	int rdr = CRdrArchive::EntryLookup(parentReader, childReader);
	std::cout << rdr << std::endl;
}