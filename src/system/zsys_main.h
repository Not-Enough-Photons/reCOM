#pragma once
namespace zdb
{
	class CZMemoryManager
	{
	public:
		void zProfileClass(bool valid, long long addressSpace, char* classFile, size_t size);
		void zAlloc();
		void zDeAlloc();
	};
}