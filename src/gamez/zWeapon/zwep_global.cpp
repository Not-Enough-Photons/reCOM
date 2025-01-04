#include "zweapon.h"

namespace zwep
{
	u32 personMaterialId = 0xffffffff;
}

bool CZWeapon::m_timer_bTimerRegistered = false;
bool CZWeapon::m_timer_bTimerCleared = false;
bool CZWeapon::m_timer_bIncrTimer = false;
f32 CZWeapon::m_timer_pCurval = 0.0f;
f32 CZWeapon::m_timer_maxval = 0.0f;

bool CZWeapon::m_allowFireAnimations = false;
bool CZWeapon::m_allowImpactAnimations = false;
bool CZWeapon::m_allowWeaponIntersection = false;

u32 CZWeapon::AI_PARAMS::version = 1;
CSnd* CZWeapon::m_bulletPassSound = NULL;

bool CZWeapon::IsPrimary(EQUIP_ITEM item)
{
	EQUIP_ITEM type = GetIDType(item);

	// TODO:
	// None of this makes sense
	// Perhaps we should double check EQUIP_ITEM?
	if (type == EQUIP_ITEM::AKS74 ||
		type == EQUIP_ITEM::EQUIP_GRENADE ||
		type == EQUIP_ITEM::EQUIP_EQUIPMENT ||
		type == EQUIP_ITEM::KEVLAR_ARMOR)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CZWeapon::IsSecondary(EQUIP_ITEM item)
{
	// TODO:
	// None of this makes sense
	// Perhaps we should double check EQUIP_ITEM?
	return GetIDType(item) == EQUIP_ITEM::EQUIP_NONE;
}