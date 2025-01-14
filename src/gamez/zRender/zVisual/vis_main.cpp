#include "zvis.h"

#include "gamez/zArchive/zar.h"

namespace zdb
{
	CCamera* CVisual::m_camera = NULL;

	CVisual* CVisual::Create(zar::CZAR& archive)
	{
		CVisual* visual = NULL;
		u32 vtype = 0;
		archive.Fetch("vtype", &vtype);

		if (vtype == 2)
		{
			visual = new CSubMesh();
		}
		else if (vtype == 1)
		{
			visual = new CMesh();
		}
		else if (vtype == 0 || vtype == -1)
		{
			visual = new CVisual();
		}

		if (visual != NULL)
		{
			visual->Read(archive);
		}
	}

	bool CVisual::Read(zar::CZAR& archive)
	{
		return true;
	}
}