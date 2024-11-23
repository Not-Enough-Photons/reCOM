#include "seal.h"

#include "gamez/zReader/zrdr_main.h"

void HEALTH_PARAMS::Parse(_zrdr* reader)
{
	auto root = zrdr_findtag(reader, "health");

	if (root != NULL)
	{
		zrdr_findreal(root, "head", &m_head_health, 1);
		m_head_healthMax = m_head_health;

		zrdr_findreal(root, "body", &m_body_health, 1);
		m_body_healthMax = m_body_health;

		zrdr_findreal(root, "larm", &m_larm_health, 1);
		m_larm_healthMax = m_larm_health;

		zrdr_findreal(root, "rarm", &m_rarm_health, 1);
		m_rarm_healthMax = m_rarm_health;

		zrdr_findreal(root, "rleg", &m_rleg_health, 1);
		m_rleg_healthMax = m_rleg_health;

		zrdr_findreal(root, "lleg", &m_lleg_health, 1);
		m_lleg_healthMax = m_lleg_health;
	}

	root = zrdr_findtag(reader, "armor");

	if (root != NULL)
	{
		zrdr_findreal(root, "head", &m_armor_head, 1);
		zrdr_findreal(root, "body", &m_armor_body, 1);
		zrdr_findreal(root, "larm", &m_armor_larm, 1);
		zrdr_findreal(root, "rarm", &m_armor_rarm, 1);
		zrdr_findreal(root, "rleg", &m_armor_rleg, 1);
		zrdr_findreal(root, "lleg", &m_armor_lleg, 1);
	}
}