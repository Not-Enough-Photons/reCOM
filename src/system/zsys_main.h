#pragma once
namespace zdb
{
	class CZMemoryManager
	{
	public:
		void zAllocClassInstance(bool valid, long long addressSpace, char* classFile, size_t size);
	};
}