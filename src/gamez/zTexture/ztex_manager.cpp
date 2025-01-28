#include "ztex.h"

namespace zdb
{
	CTexManager* CTexManager::m_texmanager = NULL;

	void CTexManager::doAddBuffer(const char* name, f32 param_2, f32 param_3)
	{
		
	}
	
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

	void CBatchRelocator::TakeDrawPacket(void* spr, s32 qwc)
	{
		// zSysFifoKick(spr, qwc);
	}
}