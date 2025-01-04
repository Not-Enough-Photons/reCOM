#include "zcam.h"

#include "gamez/zEntity/zentity.h"
#include "gamez/zSeal/zseal.h"
#include "gamez/zSystem/zsys.h"

CAppCamera* appCamera = NULL;

bool camera_tether_intersects_something;
f32 save_short_tether_length;
f32 DeltaRot;
f32 DeltaAim;

CAppCamera::CAppCamera(zdb::CWorld* world, zdb::CCamera* camera)
{
	m_cameraAim.x = 0.0f;
	m_cameraAim.y = 20.0f;
	m_cameraAim.z = 0.0f;

	m_cameraTie.x = 0.0f;
	m_cameraTie.y = 20.0f;
	m_cameraTie.z = 0.0f;

	m_camGoalPos.x = 40.0f;
	m_camGoalPos.y = 20.0f;
	m_camGoalPos.z = 0.0f;

	m_short_tether_timer = -1.0f;

	m_padid = 0;

	m_camera = camera;
	m_camera_effects = NULL;
	m_entity = NULL;

	m_z_nominal = 500.0f;
	m_camera_mode = PLAYER_CAM_STATE::cam_mode_tether;
	m_camera_last_mode = PLAYER_CAM_STATE::cam_mode_tether;

	m_death_state_timer = 0;

	float goalX = m_camGoalPos.x;
	float goalY = m_camGoalPos.y;
	float goalZ = m_camGoalPos.z;
	float goalSqr = (goalZ * goalZ) + (goalX * goalX) + (goalY * goalY);
	m_goal_t_len = goalSqr;

	CZSealBody* player = static_cast<CZSealBody*>(ftsGetPlayer());

	if (player != NULL)
	{
		bool isPlayer = false;

		if (player->m_control != NULL)
		{
			isPlayer = static_cast<CSealCtrl*>(player->m_control)->IsPlayer();
		}

		if (isPlayer)
		{
			m_padid = static_cast<CSealCtrl*>(player->m_control)->m_padid;
		}
	}

	m_entity = player;

	if (m_entity == NULL)
	{
		m_camera_effects = NULL;
		m_skel_root = NULL;
	}
	else
	{
		zdb::CNode* playerNode = m_entity->GetNode();
		zdb::CNode* cameraEffects = playerNode->FindChild("camera_effects", true);
		m_camera_effects = cameraEffects;
		m_skel_root = m_entity->FindPart("skel_root");
	}

	m_wiggle_amp = theCharacterDynamics.m_cam_wiggle.amplitude;
	m_wiggle_duration = theCharacterDynamics.m_cam_wiggle.duration;
	m_wiggle_inv_duration = 1.0f / m_wiggle_duration;
	m_wiggle_rate = theCharacterDynamics.m_cam_wiggle.rate;
	m_wiggle_inv_rate = 1.0f / m_wiggle_rate;

	if (m_wiggle_echo)
	{
		m_wiggle_scalar = 1.0f;
	}
	else if (m_wiggle_scalar < 1.0f)
	{
		m_wiggle_scalar = 1.0f;
	}

	m_wiggle_cur_time = 0.0f;
	m_wiggle_echo = false;
}

CAppCamera::~CAppCamera()
{
	m_skel_root = NULL;
	m_entity = NULL;
	m_camera_effects = NULL;
	m_camera = NULL;
}

_zanim_cmd_hdr* CAppCamera::CmdParse3rdPersonTest(_zrdr* reader)
{
	_zanim_cmd_hdr* cmd = NULL;

	if (reader == NULL)
	{
		cmd = NULL;
	}
	else
	{
		_zanim_cmd_hdr* cmd = static_cast<_zanim_cmd_hdr*>(__calloc(1, sizeof(_zanim_cmd_hdr)));
		cmd->quad_align = false;
		cmd->timeless = false;
	}

	return cmd;
}

void CAppCamera::RegisterAnimCommands()
{
	ZAnim.AddCmd("CAMERA_3RD_PERSON", CmdParse3rdPersonTest, NULL, CmdTick3rdPersonTest, NULL);
}

bool CAppCamera::CmdTick3rdPersonTest(_zanim_cmd_hdr* header, float* delta)
{
	return appCamera->m_camera_mode != PLAYER_CAM_STATE::cam_mode_FP;
}

void CAppCamera::SetZoom(float zoom)
{
	m_camera->m_Zmin = zoom;
	m_camera->m_Zmax = zoom;
	m_camera->m_RangeScale = 1.0f / zoom;
}

void CAppCamera::ResetDeathCam()
{
	m_death_state_timer = 0;
	m_allow_player_death_cam_control = true;
	save_short_tether_length = 10000.0f;
	DeltaRot = 0.0f;
	DeltaAim = 0.0f;
}

void CAppCamera::TickCameraWiggle(float delta, zdb::CCamera* camera)
{
	float wiggle = 0.0f;
	float wiggle_cur_time = m_wiggle_cur_time;

	if (m_wiggle_duration < wiggle_cur_time)
	{
		// camera->unkown01 = 0.0f;
		// camera->unkown02 = 0.0f;
		m_wiggle_echo = false;
	}
	else
	{
		float wiggle_inv_duration = wiggle_cur_time * m_wiggle_inv_duration;
		wiggle_cur_time *= 2.0f * PI * m_wiggle_inv_rate;

		if (wiggle_inv_duration < 0.0f)
		{
			wiggle_inv_duration = 0.0f;
		}

		wiggle = 1.0f;

		if (wiggle_inv_duration <= 1.0f)
		{
			wiggle = wiggle_inv_duration;
		}

		wiggle = (1.0f - wiggle) * m_wiggle_amp * m_wiggle_scalar;
		wiggle_inv_duration = sinf(wiggle_cur_time);
		// camera->unka = wiggle * wiggle_cur_time + camera->unka;
		// camera->unkb = wiggle * 0.5 * wiggle_inv_duration + camera->unkb;
		m_wiggle_cur_time += delta;
	}
}

void CAppCamera::WiggleEcho(bool echo)
{
	m_wiggle_echo = echo;

	if (echo)
	{
		m_wiggle_cur_time = 0.0f;
	}
}

void CAppCamera::WiggleScalar(float wiggle)
{
	if (!m_wiggle_echo)
	{
		m_wiggle_scalar = wiggle;
	}
	else if (m_wiggle_scalar < wiggle)
	{
		m_wiggle_scalar = wiggle;
	}
}