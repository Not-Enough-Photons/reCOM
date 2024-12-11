#include "body.h"

#include "gamez/zNode/znode.h"
#include "gamez/zMath/zmath.h"

CZBodyPart::CZBodyPart(zdb::CNode* node)
{
	m_id = -1;
	m_blendme = 1;
	m_node = node;
	m_parent = NULL;
	m_pos = CPnt3D::zero;
	m_rot = CQuat::identity;
}

void CZBodyPart::Orient()
{
	if (this != NULL)
	{
		m_node->SetPosition(m_pos.x, m_pos.y, m_pos.z);
	}

	if (&m_rot != NULL)
	{
		m_node->SetRotation(m_rot);
	}
}