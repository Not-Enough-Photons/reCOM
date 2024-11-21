#pragma once
#include "gamez/zAnim/anim_main.h"
#include "gamez/zNode/node_main.h"

class CZBodyPart;

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

	std::vector<CZBodyAnim> m_body_anims;
	std::vector<CZBodyPart> m_body_parts;
	std::vector<CZBodyPart> m_body_parts_aux;
};

class CBlendOverlay
{

};

class CZBodyAnim
{

};

class CZBodyPart
{
public:
private:
};