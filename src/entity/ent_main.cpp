#include "ent_main.h"
#include "zwep_weapon.h"

#include "ui/zui_main.h"

namespace zdb
{
	float CZSealEx::DamagePlayer(float source, float param_2)
	{
		float difference = source - m_OldHealth * ((10.0f - param_2) / 10.0f);

		if (difference <= 0.0f)
		{
			difference = 0.0f;
		}

		float dampenedDamage = m_OldHealth - (source - difference) / 4.0f;
		m_OldHealth = dampenedDamage;

		if (dampenedDamage <= 0.0f)
		{
			m_OldHealth = 0.0f;
		}

		dampenedDamage = m_Health;
		m_Health = dampenedDamage - difference;
		
		if (m_Health <= 0.0f)
		{
			m_Health = 0.0f;
		}

		return m_Health;
	}


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

	CZFTSWeapon::CZFTSWeapon() : CZWeapon()
	{
		CZWeaponStance* weaponStance;

		do
		{
			weaponStance = new CZWeaponStance();
			weaponStance++;
		} while (m_rumbleHighExceeds);

		m_rumbleHighExceeds = false;
		m_rumbleHighTime = 0.0f;
		m_rumbleLowExceeds = false;
		m_rumbleLowTime = 0.0f;
		m_rumbleLowPower = 2.35099e-38f;
		m_accuracyBurstCountMin = 2.35099e-38f;
		m_accuracyScalarMin = 1.0f;
		m_accuracyScalarMax = 1.0f;
		m_slotCost = 1;
	}
}