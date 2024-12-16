#pragma once
#include "gamez/zAnim/zanim.h"
#include "gamez/zNode/znode.h"

class CZBodyPart;
class CBlendOverlay;

class CBody
{
public:
	void SmoothAnims(float scale);
	CZBodyPart* FindPart(const char* part);
	void* NewBodyPart(zdb::CNode* node, CZBodyPart* part);
	zdb::CNode& NullNode() const;
protected:
	bool m_take_snapshot;

	CBlendOverlay* m_overlay;

	char m_maxid;
	char m_state;

	float m_interp1;
	float m_interp2;

	CActiveAnimPool* m_active_anim_pool;

	std::vector<CZBodyAnim*> m_body_anims;
	std::vector<CZBodyPart*> m_body_parts;
	std::vector<CZBodyPart*> m_body_parts_aux;
};

class CBlendOverlay
{

};

class CZBodyAnim : protected CZSIScript
{
private:
	short m_id;
	short m_animType;
	short m_basepart;
	unsigned short m_flags;

	unsigned int m_callback0_index : 8;
	unsigned int m_callback1_index : 8;
	unsigned int m_callback2_index : 8;
	unsigned int m_callback3_index : 8;
};

class CZBodyPart
{
public:
	CZBodyPart(zdb::CNode* node);
	~CZBodyPart();
public:
	void Orient();
private:
	CPnt3D m_pos;
	zdb::CNode* m_node;
	CQuat m_rot;
	CZBodyPart* m_parent;
	short m_id;
	short m_blendme;
	CPnt3D m_saved_pos;
	CQuat m_saved_rot;
};