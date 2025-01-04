#include "zweapon.h"

CZWeapon::CZWeapon()
{
	// AI parameter setup
	m_ai_params.m_min_range = 50.0f;
	m_ai_params.m_max_range = 1000.0f;
	m_ai_params.m_version = CZWeapon::AI_PARAMS::version;
	m_ai_params.m_custom = false;
	m_ai_params.m_hard_min = false;

	m_name = 0;
	m_description = 0;

	m_maxfiremode = FIREMODE::SAFETY;

	m_ammocap = 0;

	m_soundradius = 0.0f;
	m_soundradiusSq = 0.0f;

	m_encumb = ENCUMBRANCE::LIGHTLY_ENCUMBERED;

	m_effectiverange = 0.0f;
	m_maxrange = 0.0f;
	
	m_texname = 0;
	m_icontexname = 0;
	m_associatedgearname = 0;
	m_modelname = 0;
	
	m_icontex = NULL;

	m_ID = EQUIP_ITEM::EQUIP_NONE;

	m_nummags = 0;

	m_specialmaterialanimname = 0;
	m_defaultspecialanimname = 0;
	m_fireanimname = 0;
	m_hitanimname = 0;

	m_hitanim = NULL;
	m_specialmaterialanim = NULL;
	m_defaultspecialanim = NULL;
	m_zoomedfireanim = NULL;
	m_fireanim = NULL;

	m_texture = NULL;

	m_firewait = 0.1f;

	m_decalsetname = 0;
	// TODO: Implement CZDecalSet
	// m_decalset = NULL;

	m_muzzlevel = 0.0f;
	m_impactradius = 0.0f;

	m_reloadsoundname = 0;
	m_reloadsound = NULL;
	m_reloadtime = 0.0f;

	m_reloadAfterShot = false;

	m_hasFiremodes[0] = true;
	m_hasFiremodes[1] = false;
	m_hasFiremodes[2] = false;
	m_hasFiremodes[3] = false;
	m_hasFiremodes[4] = false;
}

void CZWeapon::AddLegalAmmo(CZAmmo* ammo)
{

}

void CZWeapon::ClearAnims()
{
	if (m_hitanim != NULL)
	{
		__free(m_hitanim);
		m_hitanim = NULL;
	}

	m_fireanim = NULL;
	m_zoomedfireanim = NULL;
	m_defaultspecialanim = NULL;
	
	if (m_specialmaterialanim != NULL)
	{
		__free(m_specialmaterialanim);
		m_specialmaterialanim = NULL;
	}
}

void CZWeapon::ClearTimer()
{
	m_timer_pCurval = 0;
	m_timer_bTimerRegistered = false;
	m_timer_bTimerCleared = true;
	m_timer_maxval = -1.0f;
	m_timer_bIncrTimer = 1;
}

void CZWeapon::Close()
{

}

void CZWeapon::Fire(CZProjectile& projectile)
{

}