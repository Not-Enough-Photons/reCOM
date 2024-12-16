#include <cmath>

#include "zwep_weapon.h"

#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_stable.h"

CZWeaponStance::CZWeaponStance()
{
	m_reticuleKnock = 0.0f;
	m_reticuleKnockReturn = 0.0f;
	m_reticuleKnockMax = 0.0f;
	m_sniperDistPPFrameX = 0.0f;
	m_sniperDistPPFrameY = 0.0f;
	m_sniperDistLimitX = 0.0f;
	m_sniperDistLimitY = 0.0f;
	m_sniperDecayRate = 0.0f;
	m_targetDilateUponFire = 0.0f;
	m_targetDilateUponMovement = 0.0f;
	m_targetDilateUponMovementSqrt = 0.0f;
	m_targetConstrict = 0.0f;
	m_targetMin = 0.0f;
	m_targetMax = 0.0f;
	m_fireRifleKickRate = 0.0f;
	m_fireRifleKickBaseDist = 0.0f;
	m_fireRifleKickRandomDist = 0.0f;
	m_wiggleReport = 0.03f;
	m_knockCount = 3;
	m_knockEntryStrength = 1.0f;
	return;
}

void CZWeaponStance::SetReticuleKnock(float knock)
{
	m_reticuleKnockMax = knock;
}

void CZWeaponStance::SetReticuleKnockReturn(float knockReturn)
{
	m_reticuleKnockMax = knockReturn;
}

void CZWeaponStance::SetReticuleKnockMax(float max)
{
	m_reticuleKnockMax = max;
}

void CZWeaponStance::SetTargetDilateUponFire(float dilate)
{
	m_targetDilateUponFire = dilate;
}

void CZWeaponStance::SetTargetDilateUponMovement(float dilate)
{
	m_targetDilateUponMovement = dilate;
	m_targetDilateUponMovementSqrt = sqrt(dilate);
}

void CZWeaponStance::SetTargetConstrict(float constriction)
{
	m_targetConstrict = constriction;
}

void CZWeaponStance::SetTargetMin(float min)
{
	m_targetMin = min;
}

void CZWeaponStance::SetTargetMax(float max)
{
	m_targetMax = max;
}

void CZWeaponStance::SetSniperDistPPFrameX(float frame)
{
	m_sniperDistPPFrameX = frame;
}

void CZWeaponStance::SetSniperDistPPFrameY(float frame)
{
	m_sniperDistPPFrameY = frame;
}

void CZWeaponStance::SetSniperDistLimitX(float limit)
{
	m_sniperDistLimitX = limit;
}

void CZWeaponStance::SetSniperDistLimitY(float limit)
{
	m_sniperDistLimitY = limit;
}

void CZWeaponStance::SetSniperDecayRate(float decay)
{
	m_sniperDecayRate = decay;
}

void CZWeaponStance::SetFireRifleKickRate(float rate)
{
	m_fireRifleKickRate = rate;
}

void CZWeaponStance::SetFireRifleKickReturnRate(float returnRate)
{
	m_fireRifleKickReturnRate = returnRate;
}

void CZWeaponStance::SetFireRifleKickBaseDist(float distance)
{
	m_fireRifleKickBaseDist = distance;
}

void CZWeaponStance::SetFireRifleKickRandomDist(float randomDistance)
{
	m_fireRifleKickRandomDist = randomDistance;
}

void CZWeaponStance::SetKnockCount(int knocks)
{
	m_knockCount = knocks;
}

void CZWeaponStance::SetKnockEntryStrength(float strength)
{
	m_knockEntryStrength = strength;
}

void CZWeaponStance::SetWiggleReport(float wiggleReport)
{
	m_wiggleReport = wiggleReport;
}

CZWeapon::CZWeapon()
{
	m_internalName = 0;
	m_displayName = 0;
	m_description = 0;
	m_effectiveRange = 0.0f;
	m_maximumRange = 0.0f;
	m_muzzleVelocity = 0.0f;
	m_gravityAcceleration = -1.0f;
	m_impactRadius = 0.0f;
}

void CZWeapon::SetInternalName(const char* internalName)
{
	char* str;

	if (m_internalName != 0)
	{
		zAllocateInst((void*)m_internalName, "zwep_weapon.cpp", 551);
	}

	m_internalName = 0;
	if (internalName == 0)
	{
		str = 0;
	}
	else
	{
		str = reinterpret_cast<char*>(CreateString(internalName, "zwep_weapon.cpp", 552));
	}

	m_internalName = str;
}

void CZWeapon::SetDisplayName(const char* displayName)
{
	char* str;

	if (m_displayName != 0)
	{
		zAllocateInst((void*)m_displayName, "zwep_weapon.cpp", 551);
	}

	m_displayName = 0;
	if (displayName == 0)
	{
		str = 0;
	}
	else
	{
		str = reinterpret_cast<char*>(CreateString(displayName, "zwep_weapon.cpp", 552));
	}

	m_displayName = str;
}

void CZWeapon::SetDescription(const char* description)
{
	char* str;

	if (m_description != 0)
	{
		zAllocateInst((void*)m_description, "zwep_weapon.cpp", 551);
	}

	m_description = 0;
	if (description == 0)
	{
		str = 0;
	}
	else
	{
		str = reinterpret_cast<char*>(CreateString(description, "zwep_weapon.cpp", 552));
	}

	m_description = str;
}

CZFTSWeapon::CZFTSWeapon() : CZWeapon()
{
	CZWeaponStance* weaponStance;

	do
	{
		weaponStance = new CZWeaponStance();
		weaponStance++;
	} while (m_rumbleHighExceeds);

	m_firstZoomLevel = 0;
	m_secondZoomLevel = 0;
	m_thirdZoomLevel = 0;
	m_rumbleHighExceeds = false;
	m_rumbleHighTime = 0.0f;
	m_rumbleLowExceeds = false;
	m_rumbleLowTime = 0.0f;
	m_rumbleLowPower = 2.35099e-38f;
	m_accuracyBurstCountMin = 2.35099e-38f;
	m_accuracyScalarMin = 1.0f;
	m_accuracyScalarMax = 1.0f;
	m_normalizedRange = 0.0f;
	m_slotCost = 1;
}

void CZFTSWeapon::SetAccuracyBurstCountMin(int min)
{
	float range = 0.0f;
	float normalizedRange = 0.0f;

	m_accuracyBurstCountMin = min;
	range = (m_accuracyBurstCountMax - m_accuracyBurstCountMin);
	if (range >= 0.0f)
	{
		normalizedRange = (m_accuracyScalarMax - m_accuracyScalarMin) / range;
	}

	m_normalizedRange = normalizedRange;
}

void CZFTSWeapon::SetAccuracyBurstCountMax(int max)
{
	float range = 0.0f;
	float normalizedRange = 0.0f;

	m_accuracyBurstCountMax = max;
	range = (m_accuracyBurstCountMax - m_accuracyBurstCountMin);
	if (range >= 0.0f)
	{
		normalizedRange = (m_accuracyScalarMax - m_accuracyScalarMin) / range;
	}

	m_normalizedRange = normalizedRange;
}

void CZFTSWeapon::SetAccuracyScalarMin(float min)
{
	float range = 0.0f;
	float normalizedRange = 0.0f;

	m_accuracyScalarMin = min;
	range = (m_accuracyBurstCountMax - m_accuracyBurstCountMin);
	if (range >= 0.0f)
	{
		normalizedRange = (m_accuracyScalarMax - m_accuracyScalarMin) / range;
	}

	m_normalizedRange = normalizedRange;
}

void CZFTSWeapon::SetAccuracyScalarMax(float max)
{
	float range = 0.0f;
	float normalizedRange = 0.0f;

	m_accuracyScalarMin = max;
	range = (m_accuracyBurstCountMax - m_accuracyBurstCountMin);
	if (range >= 0.0f)
	{
		normalizedRange = (m_accuracyScalarMax - m_accuracyScalarMin) / range;
	}

	m_normalizedRange = normalizedRange;
}

float CZProjectile::ResolveDamage(float target, float source, float* currentDamage, float* newDamage)
{
	float oldDmg = target - *newDamage * ((10.0f - source) / 10.0f);
	if (oldDmg <= 0.0f)
	{
		oldDmg = 0.0f;
	}

	float newDmg = *newDamage - (target - oldDmg) / 4.0f;
	*newDamage = newDmg;
	if (newDmg <= 0.0f)
	{
		*newDamage = 0.0f;
	}

	newDmg = *currentDamage;
	*currentDamage = newDmg - oldDmg;
	if (newDmg - oldDmg <= 0.0f)
	{
		*currentDamage = 0.0f;
	}

	return *currentDamage;
}

CZWeapon* CZWeaponList::GetWeaponByIndex(int index) const
{
	int i = 0;
	CZWeapon* weapon;

	auto begin = weapons.begin();
	auto tail = weapons.end();
	auto current = tail;
	while (true)
	{
		current--;

		if (current == begin)
		{
			return NULL;
		}

		if (i == index)
		{
			break;
		}

		weapon = *current;
		i++;
	}

	return weapon;
}
