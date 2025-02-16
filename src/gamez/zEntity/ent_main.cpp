#include "zentity.h"

u32 recycler_index = 0;
CEntity* recycler = NULL;
std::vector<CEntity*> CEntity::m_list;

CEntity::CEntity(TYPE type, zdb::CNode* node)
{
	
}

void CEntity::OpenRecycler(u32 index)
{
	recycler_index = index;
}

bool CEntity::EntityIsValid(CEntity* entity)
{
	bool valid = false;
	auto it = m_list.begin();
	while (it != m_list.end())
	{
		if (*it == entity)
		{
			valid = true;
			break;
		}
		
		++it;
	}

	return valid;
}

u32 CEntity::GetEntityIndex() const
{
	u32 index = -1;

	if (this)
	{
		index = m_index;
	}
	
	return index;
}

std::vector<CEntity*>& CEntity::GetEntityList()
{
	return m_list;
}

bool CEntity::IsAlive() const
{
	return m_isAlive;
}

void CEntity::JoinTeam(u32 team)
{
	if (team < 32)
	{
		m_team = team;
	}
}

void CEntity::OnDeath()
{
	m_isAlive = false;
	m_control->OnDeath();
}

void CEntity::SetController(CEntityCtrl* controller)
{
	if (m_control)
	{
		m_control->m_entity = NULL;
	}

	m_control = controller;

	if (m_control)
	{
		m_control->m_entity = this;
	}
}

void CEntity::SetDisplayName(const char* name)
{
	if (m_display_name)
	{
		zfree(m_display_name);
	}

	m_display_name = NULL;

	m_display_name = zstrdup(name);
}

zdb::CNode* CEntity::GetNode() const
{
	return m_node;
}