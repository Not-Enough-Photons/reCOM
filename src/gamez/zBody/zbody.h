#pragma once
#include "gamez/zAnim/zanim.h"
#include "gamez/zNode/znode.h"

class CZBodyPart;
class CBlendOverlay;
class CZBodyAnim;

class CBody
{
public:
	void SmoothAnims(f32 scale);
	CZBodyPart* FindPart(const char* name);
	void* NewBodyPart(zdb::CNode* node, CZBodyPart* part);
	zdb::CNode& NullNode() const;
protected:
	bool m_take_snapshot;

	CBlendOverlay* m_overlay;

	s8 m_maxid;
	s8 m_state;

	f32 m_interp1;
	f32 m_interp2;

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
	s16 m_id;
	s16 m_animType;
	s16 m_basepart;
	u16 m_flags;

	u32 m_callback0_index : 8;
	u32 m_callback1_index : 8;
	u32 m_callback2_index : 8;
	u32 m_callback3_index : 8;
};

class CZBodyPart
{
	friend class CBody;
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
	s16 m_id;
	s16 m_blendme;
	CPnt3D m_saved_pos;
	CQuat m_saved_rot;
};