#include <cmath>

#include "zwep_ammo.h"

#include "system/zsys_main.h"
#include "util/util_stable.h"

namespace zdb
{
	CZAmmo::CZAmmo()
	{
		m_internalName = 0;
		m_displayName = 0;
		m_description = 0;
		m_hitAnimName = 0;
		m_ID = -1;
		m_projectilesFired = 1;
		m_blowbackFalloff = 0.0f;
		m_proximitySquared = 0.0f;
		m_accelerationFactor = 1.0f;
		m_volatile = false;
	}

	void CZAmmo::SetInternalName(const char* internalName)
	{
		char* str;

		if (m_internalName == 0)
		{
			zAllocateInst((void*)m_internalName, "zwep_ammo.cpp", 42);
		}

		m_internalName = 0;
		str = reinterpret_cast<char*>(CreateString(internalName, "zwep_ammo.cpp", 43));
		m_internalName = str;
	}

	void CZAmmo::SetDisplayName(const char* displayName)
	{
		char* str;

		if (m_displayName == 0)
		{
			zAllocateInst((void*)m_displayName, "zwep_ammo.cpp", 42);
		}

		m_displayName = 0;
		str = reinterpret_cast<char*>(CreateString(displayName, "zwep_ammo.cpp", 43));
		m_displayName = str;
	}

	void CZAmmo::SetDescription(const char* description)
	{
		char* str;

		if (m_description == 0)
		{
			zAllocateInst((void*)m_description, "zwep_ammo.cpp", 42);
		}

		m_description = 0;
		str = reinterpret_cast<char*>(CreateString(description, "zwep_ammo.cpp", 43));
		m_description = str;
	}

	void CZAmmo::SetID(int id)
	{
		m_ID = id;
	}

	void CZAmmo::SetImpactDamage(float impactDamage)
	{
		m_impactDamage = impactDamage;
	}

	void CZAmmo::SetHitAnimName(const char* hitAnimName)
	{
		m_hitAnimName = hitAnimName;
	}

	void CZAmmo::SetStun(float stun)
	{
		m_stun = stun;
	}

	void CZAmmo::SetPiercing(float piercing)
	{
		m_piercing = piercing;
	}

	void CZAmmo::SetExplosionDamage(float explosionDamage)
	{
		m_explosionDamage = explosionDamage;
	}

	void CZAmmo::SetExplosionRadius(float explosionRadius)
	{
		m_explosionRadius = explosionRadius;
	}

	void CZAmmo::SetProjectilesFired(int projectilesFired)
	{
		m_projectilesFired = projectilesFired;
	}

	void CZAmmo::SetBlowbackFalloff(float blowbackFalloff)
	{
		m_blowbackFalloff = blowbackFalloff;
	}

	void CZAmmo::SetProximitySquared(float proximity)
	{
		m_proximitySquared = proximity * proximity;
	}

	void CZAmmo::SetAccelerationFactor(float acceleration)
	{
		m_accelerationFactor = acceleration;
	}

	// "volatile" is a reserved keyword
	void CZAmmo::SetIsVolatile(bool volitile)
	{
		m_volatile = volitile;
	}
}