#pragma once
#include "math/zmath_main.h"
#include "node/node_main.h"
#include "reader/zrdr_main.h"

enum AnimTypes
{

};

struct zanim_cmd_hdr
{

};

static int InitAnimLang();
static int ParseScriptKeywords();
static int ParseAIKeywords();
static int ParseResetBodyKeyword();
static int ParseValveKeywords();
static int ParseCameraKeywords();
static int ParseThirdPersonCamKeyword();
static int ParsePlayerConditionKeywords();
static int ParseWindKeyword();
static int ParseExecuteActionKeyword();
static int ParseDecalRemovalKeyword();
static void ParseScriptKeyword(void* ptr, char* token, int param_3, void(*func), bool(*condition), int param_6);

static bool CmdAddNode(zdb::CNode node);
static bool CmdRemoveNode(zdb::CNode node);

class CZAnim
{
public:
	void AddNewNodeRef();
	void OnWeaponHitInit();
	void GetNode();
};

class CZAnimEx : public CZAnim
{
	void AddAnimEx();
};

class CZAnimSet
{
public:
	void GetName();
};

class CZAnimNameIndexTable
{
public:
	void GetName();
};

class CZAnimMain
{
public:
	static void Open(const char* name);
	void AddCmd(const char* name, zanim_cmd_hdr*(*)(zrdr*), void(*)(zanim_cmd_hdr*), bool(*)(zanim_cmd_hdr*, float*), void(*)(zanim_cmd_hdr*));
	void GetAnimSet();
	void GetAnimSetIndex();
};

static CZAnimMain ZAnim;

class CZBodyAnimBlend
{
public:
	void SetFractionalTime(float time);
private:
	float m_time;
};

class CSealAnim
{
public:
	CSealAnim();
	~CSealAnim();
};