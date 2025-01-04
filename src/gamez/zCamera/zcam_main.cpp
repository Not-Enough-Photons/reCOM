#include "zcam.h"

#include "gamez/zMath/zmath.h"
#include "gamez/zSeal/zseal.h"

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

	void CCamera::CmdBeginParams(_zanim_cmd_hdr* header)
	{
		CCamera* worldCamera = zdb::CWorld::m_world->m_camera;

		if (worldCamera != NULL)
		{

		}
	}

	_zanim_cmd_hdr* CCamera::CmdParseRelease(_zrdr* reader)
	{
		_zanim_cmd_hdr* cmd = NULL;
		return cmd;
	}

	_zanim_cmd_hdr* CCamera::CmdParseAcquire(_zrdr* reader)
	{
		_zanim_cmd_hdr* cmd = NULL;
		return cmd;
	}

	_zanim_cmd_hdr* CCamera::CmdParseIndoorsTest(_zrdr* reader)
	{
		_zanim_cmd_hdr* cmd = NULL;
		return cmd;
	}

	_zanim_cmd_hdr* CCamera::CmdParseSetRegions(_zrdr* reader)
	{
		_zanim_cmd_hdr* cmd = NULL;
		return cmd;
	}

	_zanim_cmd_hdr* CCamera::CmdParseGetRegions(_zrdr* reader)
	{
		_zanim_cmd_hdr* cmd = NULL;
		return cmd;
	}

	_zanim_cmd_hdr* CCamera::CmdParseParams(_zrdr* reader)
	{
		_zanim_cmd_hdr* cmd = NULL;
		return cmd;
	}

	bool CCamera::CmdTickControlSwitch(_zanim_cmd_hdr* header, f32* dT)
	{
		if (header->timeless)
		{
			// m_dynamics_controlled = false;
		}
		else if (!header->timeless)
		{
			// m_dynamics_controlled = true;
		}

		return true;
	}

	bool CCamera::CmdTickIndoorsTest(_zanim_cmd_hdr* header, f32* dT)
	{
		return true;
	}

	bool CCamera::CmdTickSetRegions(_zanim_cmd_hdr* header, f32* dT)
	{
		return true;
	}

	bool CCamera::CmdTickGetRegions(_zanim_cmd_hdr* header, f32* dT)
	{
		return true;
	}

	bool CCamera::CmdTickParams(_zanim_cmd_hdr* header, f32* dT)
	{
		return true;
	}
}