#include "zentity.h"

CharacterDynamics theCharacterDynamics;

zdb::CNode* CEntity::GetNode() const
{
	return m_node;
}