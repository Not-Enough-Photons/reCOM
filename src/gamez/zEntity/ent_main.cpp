#include "ent_main.h"
#include "node/node_world.h"

void SealInitCharacterDynamics()
{
	if (!theCharacterDynamics.loadedCD)
	{
		_zrdr* reader = zrdr_read("dynamics.rdr", "data/common", 0);
		theCharacterDynamics.Load(reader);
		zrdr_free(reader);
	}
}

void CharacterDynamics::Load(_zrdr* reader)
{
	if (!loadedCD)
	{
		loadedCD = true;
		zrdr_findreal(reader, "gravity", &gravity, 1);
		zrdr_findreal(reader, "DamageToNewtons", &newtonDamage, 1);
		zrdr_findreal(reader, "jump_factor", &jumpFactor, 1);
		zrdr_findreal(reader, "land_fall_rate", &landFallRate, 1);
		zrdr_findreal(reader, "land_hard_fall_rate", &landHardFallRate, 1);
		zrdr_findreal(reader, "ground_touch_distance", &groundTouchDistance, 1);
		zrdr_findreal(reader, "max_slope", &maxSlope, 1);
		maxSlope = cosf(maxSlope * 0.01745329f);
		zrdr_findreal(reader, "step_height", &stepHeight, 1);
		zrdr_findreal(reader, "FALLING_DAMAGE_LIMIT", &fallDamageLimit, 1);
		zrdr_findreal(reader, "FALLING_DAMAGE_HEAVY", &fallDamageHeavy, 1);
		zrdr_findreal(reader, "FALLING_DAMAGE_DEATH", &fallDamageDeath, 1);
		fallDamageLimit *= zdb::CWorld::m_scale;
		fallDamageHeavy *= zdb::CWorld::m_scale;
		fallDamageDeath *= zdb::CWorld::m_scale;

		int i = 0;
		float gravity = theCharacterDynamics.gravity;
		while (i < 3)
		{
			float damageLimit = sqrtf((fallDamageLimit + i) * 2.0f) / gravity;
			i++;
		}
	}
}