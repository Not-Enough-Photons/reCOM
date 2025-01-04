#include "zweapon.h"

void CZProjectile::Reset()
{
	if (m_pickup != NULL)
	{
		// m_pickup->Destroy();
		m_pickup = NULL;
	}

	m_heading = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;

	m_done = false;
	m_isfirsthit = true;
	m_isfirsthit = true;
	m_useflyout = true;
	m_lastHitWasPerson = true;
	m_lastHitWasVolumetric = true;
	m_echo = true;

	m_intersecthandle = -1;
	m_animinstance = NULL;
	m_shottype = PROJECTILE_TYPE::NORMAL;
	m_state = PROJECTILE_STATE::PROJECTILE_EXPIRED;

	m_currange = 0.0f;
	m_shooterID = 0;

	m_time = 9999999.0f;
	m_removaltime = 9999999.0f;

	m_framestartpos = CPnt3D::zero;
	m_frameendpos = CPnt3D::zero;
	m_startpos = CPnt3D::zero;

	m_instance->SetModel(NULL);

	if (m_weapon != NULL)
	{
		// m_currange = m_weapon->GetMaxRange();

		if (m_currange == 0.0f)
		{
			m_shottype = m_shottype;
		}
		else
		{
			m_shottype = PROJECTILE_TYPE::ONE_FRAME;
		}
	}

	if (m_ammo != NULL)
	{
		m_ammo = m_ammo;
	}
}

zdb::CNode* CZProjectile::GetInstance() const
{
	return m_instance;
}