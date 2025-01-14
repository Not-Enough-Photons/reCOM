#include "znode.h"

namespace zdb
{
	bool CModel::Read(CSaveLoad& sload)
	{
		zar::CKey* modelkey = sload.m_zfile.GetOpenKey();
		if (modelkey != NULL)
		{
			CNode::Read(sload);
			SetName(modelkey->GetName());
		}

		return true;
	}
}