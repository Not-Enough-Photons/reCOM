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

bool ZWepReader::Read(zar::CZAR& archive, CZWeaponList* weapons, void* ammo)
{
	u32 version = 0;

	archive.Fetch("WEAPON_ZAR_VERSION", &version);
	
	if (version != 0)
	{
		return false;
	}

	char key_name_buf[256];
	char str_val[256];
	s32 int_val;
	f32 f_val;
	
	auto ammunition_key = archive.OpenKey("Ammunition");
	sprintf_s(key_name_buf, 256, "AMMO:NumEntries");
	u32 num_ammo_entries = 0;
	
	if (archive.Fetch(key_name_buf, &num_ammo_entries))
	{
		for (u32 i = 0; i < num_ammo_entries; i++)
		{
			sprintf_s(key_name_buf, 256, "AMMO%d", i);
			auto key = archive.OpenKey(key_name_buf);

			CZAmmo zammo;

			if (archive.FetchString("Name", str_val, 255))
			{
				// zammo.SetName(str_val);
			}

			if (archive.Fetch("ID", &int_val))
			{
				// zammo.SetID(int_val);
			}

			if (archive.FetchString("DESCRIPTION", str_val, 255))
			{
				// zammo.SetDescription(str_val);
			}

			if (archive.FetchString("HitAnimName", str_val, 255))
			{
				// zammo.SetHitAnimName(str_val);
			}

			if (archive.Fetch("ImpactDamage", &f_val))
			{
				// zammo.SetImpactDamage(f_val);
			}

			if (archive.Fetch("Stun", &f_val))
			{
				// zammo.SetStun(f_val);
			}

			if (archive.Fetch("ArmorPierce", &f_val))
			{
				// zAmmo.SetArmorPierce(f_val);
			}

			if (archive.Fetch("ExplosionDamage", &f_val))
			{
				// zammo.SetExplosionDamage(f_val);
			}

			if (archive.Fetch("ExplosionRadius", &f_val))
			{
				// zammo.SetExplosionRadius(f_val);
			}

			// ammo.AddAmmo(&ammo);

			archive.CloseKey(key);
		}
	}

	return true;
}

EQUIP_ITEM CZWeapon::GetIDType(EQUIP_ITEM id)
{
	if (id > EQUIP_ITEM::EQUIP_PISTOL && id < EQUIP_ITEM::EQUIP_SMG)
	{
		return EQUIP_ITEM::EQUIP_PISTOL;
	}

	if (id > EQUIP_ITEM::EQUIP_SMG && id < EQUIP_ITEM::EQUIP_ASSAULT_RIFLE)
	{
		return EQUIP_ITEM::EQUIP_SMG;
	}

	if (id > EQUIP_ITEM::EQUIP_ASSAULT_RIFLE && id < EQUIP_ITEM::EQUIP_SHOTGUN)
	{
		return EQUIP_ITEM::EQUIP_ASSAULT_RIFLE;
	}

	if (id > EQUIP_ITEM::EQUIP_SHOTGUN && id < EQUIP_ITEM::EQUIP_MACHINEGUN)
	{
		return EQUIP_ITEM::EQUIP_SHOTGUN;
	}

	if (id > EQUIP_ITEM::EQUIP_MACHINEGUN && id < EQUIP_ITEM::EQUIP_SNIPER_RIFLE)
	{
		return EQUIP_ITEM::EQUIP_MACHINEGUN;
	}

	if (id > EQUIP_ITEM::EQUIP_SNIPER_RIFLE && id < EQUIP_ITEM::GRENADE)
	{
		return EQUIP_ITEM::EQUIP_SNIPER_RIFLE;
	}

	if (id > EQUIP_ITEM::EQUIP_HEAVYWEAPON && id < EQUIP_ITEM::EQUIP_EXPLOSIVE)
	{
		return EQUIP_ITEM::EQUIP_HEAVYWEAPON;
	}

	if (id > EQUIP_ITEM::EQUIP_EXPLOSIVE && id < EQUIP_ITEM::EQUIP_MELEE)
	{
		return EQUIP_ITEM::EQUIP_EXPLOSIVE;
	}

	if (id > EQUIP_ITEM::EQUIP_MELEE && id < EQUIP_ITEM::EQUIP_LAUNCHED_GRENADE)
	{
		return EQUIP_ITEM::EQUIP_MELEE;
	}

	if (id > EQUIP_ITEM::EQUIP_LAUNCHED_GRENADE && id < EQUIP_ITEM::EQUIP_EQUIPMENT)
	{
		return EQUIP_ITEM::EQUIP_LAUNCHED_GRENADE;
	}

	if (id > EQUIP_ITEM::EQUIP_EQUIPMENT && id < EQUIP_ITEM::EQUIP_ARMOR)
	{
		return EQUIP_ITEM::EQUIP_EQUIPMENT;
	}

	if (id > EQUIP_ITEM::EQUIP_ARMOR && id < EQUIP_ITEM::EQUIP_END)
	{
		return EQUIP_ITEM::EQUIP_ARMOR;
	}

	if (id >= EQUIP_ITEM::EQUIP_END)
	{
		return EQUIP_ITEM::EQUIP_NONE;
	}
	
	return EQUIP_ITEM::EQUIP_NONE;
}

bool CZWeapon::IsPrimary(EQUIP_ITEM item)
{
	EQUIP_ITEM item_id = GetIDType(item);

	if (item_id == EQUIP_ITEM::EQUIP_SMG)
	{
		return true;
	}

	if (item_id == EQUIP_ITEM::EQUIP_ASSAULT_RIFLE)
	{
		return true;
	}

	if (item_id == EQUIP_ITEM::EQUIP_SHOTGUN)
	{
		return true;
	}

	if (item_id == (EQUIP_ITEM::MARK46MOD0 | EQUIP_ITEM::MARK23))
	{
		return true;
	}

	if (item_id == EQUIP_ITEM::EQUIP_HEAVYWEAPON)
	{
		return true;
	}

	if (item_id == EQUIP_ITEM::EQUIP_SNIPER_RIFLE)
	{
		return true;
	}

	return false;
}

bool CZWeapon::IsSecondary(EQUIP_ITEM item)
{
	return GetIDType(item) == EQUIP_ITEM::EQUIP_PISTOL;
}

bool CZWeapon::IsDirectFire() const
{
	EQUIP_ITEM type = GetIDType(m_ID);

	if (type == EQUIP_ITEM::EQUIP_LAUNCHED_GRENADE)
	{
		return false;
	}

	if (type == EQUIP_ITEM::GRENADE)
	{
		return false;
	}

	if (type == EQUIP_ITEM::EQUIP_EXPLOSIVE)
	{
		return false;
	}

	if (type == EQUIP_ITEM::EQUIP_EQUIPMENT)
	{
		return false;
	}

	return true;
}
