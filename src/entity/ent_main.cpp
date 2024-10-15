#include <cmath>

#include "ent_main.h"
#include "zwep_weapon.h"
#include "system/zsys_main.h"
#include "util/util_stable.h"
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
}