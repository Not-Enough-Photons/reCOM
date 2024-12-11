#include "zcam.h"

CAppCamera::CAppCamera(zdb::CWorld* world, zdb::CCamera* camera)
{
	m_cameraAim = { 0.0f, 20.0f, 0.0f };
	m_cameraTie = { 0.0f, 20.0f, 0.0f };
	m_camGoalPos = { 40.0f, 20.0f, 0.0f };

	m_short_tether_timer = -1.0f;

	m_padid = 0;

	m_camera = camera;
	m_camera_effects = NULL;
	m_entity = NULL;

	m_z_nominal = 500.0f;

	m_camera_mode = PLAYER_CAM_STATE::type_01;
	m_camera_last_mode = PLAYER_CAM_STATE::type_01;
	m_cam_death_state = CAM_DEATH_STATE::type_00;

	m_goal_t_len = sqrtf(m_camGoalPos.z * m_camGoalPos.z + m_camGoalPos.x * m_camGoalPos.x + m_camGoalPos.y * m_camGoalPos.y);

	CEntity* player = ftsGetPlayer();

	if (player != NULL)
	{
		// isPlayer = false;
		// if (player->field54_0xc0 != (CEntityCtrl*)0x0)
		// {
		// 		isPlayer = (bool)(**(code**)((int)player->field54_0xc0->vtable + 0x2c))();
		// }
		// if ((isPlayer != false) && (player->field54_0xc0 != (CEntityCtrl*)0x0))
		// {
		// 		this->m_padid = (uint)player->field54_0xc0[0xb].m_throttle[1];
		// }
	}

	m_entity = static_cast<CZSealBody*>(player);

	// Player doesn't exist. Don't reference non-existent player nodes.
	if (m_entity == NULL)
	{
		m_camera_effects = NULL;
		m_skel_root = NULL;
	}
	else
	{
		// Player does exist. Find related nodes.
		zdb::CNode* node = m_entity->GetNode();
		m_camera_effects = node->FindChild("camera_effects", true);
		m_skel_root = m_entity->FindPart("skel_root");
	}

	m_wiggle_amp = theCharacterDynamics.m_cam_wiggle.amplitude;
	m_wiggle_duration = theCharacterDynamics.m_cam_wiggle.duration;
	m_wiggle_inv_duration = 1.0f / theCharacterDynamics.m_cam_wiggle.duration;
	m_wiggle_rate = theCharacterDynamics.m_cam_wiggle.rate;
	m_wiggle_inv_rate = 1.0f / theCharacterDynamics.m_cam_wiggle.rate;

	if (!m_wiggle_echo)
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

void CAppCamera::TickCameraWiggle(float delta, zdb::CCamera* camera)
{
	float wiggle_cur_time = m_wiggle_cur_time;

	if (m_wiggle_duration < wiggle_cur_time)
	{
		m_screen.right = 0;

	}
}