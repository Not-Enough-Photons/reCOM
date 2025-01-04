#include "ztex.h"

namespace zdb
{
	CTexManager* CTexManager::m_texmanager = NULL;

	void CBatchRelocator::AddToBatch(zdb::CTexHandle* handle) const
	{
		CDynTexList* dynTexList = CTexManager::m_texmanager->front();
		dynTexList->Add(handle, true);
	}

	void CBatchRelocator::ClearAll()
	{

	}

	void CBatchRelocator::EndBatchReloc()
	{

	}

	void CBatchRelocator::StartBatchReloc()
	{

	}

	void CBatchRelocator::TakeDrawPacket(void* spr, int qwc)
	{
		// zSysFifoKick(spr, qwc);
	}
}