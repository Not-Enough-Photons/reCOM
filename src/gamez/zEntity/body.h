#pragma once
#include "gamez/zNode/node_main.h"

class CZBodyPart;

class CBody
{
public:
	void SmoothAnims(float scale);
	CZBodyPart* FindPart(const char* part);
	void* NewBodyPart(zdb::CNode* node, CZBodyPart* part);
	zdb::CNode& NullNode() const;
private:

};

class CZBodyPart
{
public:
private:
};