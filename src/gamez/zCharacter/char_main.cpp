#include "zchar.h"

CharacterDynamics theCharacterDynamics;

void HEALTH_PARAMS::Parse(_zrdr* reader)
{
    _zrdr* health = zrdr_findtag(reader, "health");

    if (health)
    {
        zrdr_findreal(health, "head", &m_head_health, 1);
        m_head_healthMax = m_head_health;

        zrdr_findreal(health, "body", &m_body_health, 1);
        m_body_healthMax = m_body_health;

        zrdr_findreal(health, "larm", &m_larm_health, 1);
        m_larm_healthMax = m_larm_health;

        zrdr_findreal(health, "rarm", &m_rarm_health, 1);
        m_rarm_healthMax = m_rarm_health;

        zrdr_findreal(health, "rleg", &m_rleg_health, 1);
        m_rleg_healthMax = m_rleg_health;

        zrdr_findreal(health, "lleg", &m_lleg_health, 1);
        m_lleg_healthMax = m_lleg_health;
    }

    _zrdr* armor = zrdr_findtag(reader, "armor");

    if (armor)
    {
        zrdr_findreal(armor, "head", &m_armor_head, 1);
        zrdr_findreal(armor, "body", &m_armor_body, 1);
        zrdr_findreal(armor, "larm", &m_armor_larm, 1);
        zrdr_findreal(armor, "rarm", &m_armor_rarm, 1);
        zrdr_findreal(armor, "rleg", &m_armor_rleg, 1);
        zrdr_findreal(armor, "lleg", &m_armor_lleg, 1);
    }
}