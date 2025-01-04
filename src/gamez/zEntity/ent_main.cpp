#include "zentity.h"

CEntity* ftsPlayer = NULL;
CharacterDynamics theCharacterDynamics;

zdb::CNode* CEntity::GetNode() const
{
	return m_node;
}