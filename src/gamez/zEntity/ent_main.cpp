#include "zentity.h"

CharacterDynamics theCharacterDynamics;

CEntity::CEntity(TYPE type, zdb::CNode* node)
{
	
}


zdb::CNode* CEntity::GetNode() const
{
	return m_node;
}