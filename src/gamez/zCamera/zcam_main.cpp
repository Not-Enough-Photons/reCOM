#include "zcam.h"

namespace zdb
{
	void CCamera::RegisterAnimCommands()
	{
		ZAnim.AddCmd("DYNAMICS_RELEASE_CAMERA", CmdParseRelease, NULL, CmdTickControlSwitch, NULL);
		ZAnim.AddCmd("DYNAMICS_ACQUIRE_CAMERA", CmdParseAcquire, NULL, CmdTickControlSwitch, NULL);
		ZAnim.AddCmd("CAMERA_INDOORS", CmdParseIndoorsTest, NULL, CmdTickIndoorsTest, NULL);
		ZAnim.AddCmd("SET_CAMERA_REGION_TEST", CmdParseSetRegions, NULL, CmdTickSetRegions, NULL);
		ZAnim.AddCmd("GET_CAMERA_REGION_TEST", CmdParseGetRegions, NULL, CmdTickGetRegions, NULL);
		ZAnim.AddCmd("CAMERA_PARAMS", CmdParseParams, CmdBeginParams, CmdTickParams, NULL);
	}

	float CCamera::GetScaledRangeSquared(const CPnt3D& point)
	{
		float x = point.point.x;
		float y = point.point.y;
		float z = point.point.z;
		CPnt3D pnt;
		pnt.point.x = x;
		pnt.point.y = y;
		pnt.point.z = z;
		return m_scaledrange * (pnt.point.z * pnt.point.z + pnt.point.x * pnt.point.x + pnt.point.y * pnt.point.y);
	}
}
