#include "zanim.h"

CZAnimMain ZAnim;
bool CZAnimMain::m_LoadFromZAR = false;

bool CZAnimMain::SplitName(char* name, char** splitname)
{
	bool split_success = false;
	char* haystack = NULL;

	if (!name)
	{
		*splitname = NULL;
		split_success = false;
	}
	else
	{
		char* separator = strstr(name, "::");

		if (!separator)
		{
			*splitname = name;
		}
		else
		{
			haystack = zstrdup(name);
			separator = strstr(haystack, "::");
			*separator = '\0';
			*splitname = separator + 2;
		}

		split_success = haystack != NULL;
	}

	return split_success;
}

bool CZAnimMain::InitCommands()
{
	AddCmd("QUAD_ALIGN", NULL, NULL, zAnimQuadAlignTick, NULL);
	
	ZAnim.m_cmd_if = *AddCmd("IF", zAnimLoad_If, NULL, zAnimIfTick, NULL);
	ZAnim.m_cmd_elseif = *AddCmd("ELSEIF", zAnimLoad_ElseIf, NULL, zAnimGoToEndIf, NULL);
	ZAnim.m_cmd_else = *AddCmd("Else", zAnimLoad_ElseIf, NULL, zAnimGoToEndIf, NULL);
	ZAnim.m_cmd_endif = *AddCmd("ENDIF", zAnimLoad_EndIf, NULL, zAnimEndIfTick, NULL);

	ZAnim.AddCmd("NODE_ACTIVE", zAnimLoadNodeActive, NULL, zAnimNodeActiveTick, NULL);
	ZAnim.AddCmd("NODE_RENDERED", zAnimLoadNodeRendered, NULL, zAnimRangeTestTick, NULL);
	ZAnim.AddCmd("RANGE_TEST", zAnimLoadRangeTest, NULL, zAnimRangeTestTick, NULL);
	ZAnim.AddCmd("RANDOM_WEIGHT", zAnimLoadRandomWeight, NULL, zAnimRandomWeightTick, NULL);
	ZAnim.AddCmd("FAIL", zAnimLoadFail, NULL, zAnimFailTick, NULL);
	ZAnim.AddCmd("ANIM_HEALTH", zAnimLoadAnimHealthTest, NULL, zAnimHealthTestTick, NULL);
	ZAnim.AddCmd("ANIM_LOD", zAnimLoadAnimLODTest, NULL, zAnimLODTestTick, NULL);
	ZAnim.AddCmd("LOOP", zAnimLoadLoop, NULL, zAnimLoopTick, NULL);
	ZAnim.AddCmd("WAIT", zAnimLoadWait, zAnimWaitBegin, zAnimWaitTick, NULL);
	ZAnim.AddCmd("OBJECT_BLENDMODE", zAnimLoadObjectBlendMode, NULL, zAnimObjectBlendModeTick, NULL);
	ZAnim.AddCmd("OBJECT_ACTIVE_STATE", zAnimLoadObjectActiveState, NULL, zAnimObjectActiveStateTick, NULL);
	ZAnim.AddCmd("OBJECT_TRANSLATE_STATE", zAnimLoadObjectTranslateState, NULL, zAnimObjectTranslateStateTick, NULL);
	ZAnim.AddCmd("OBJECT_ROTATE_STATE", zAnimLoadObjectRotateState, NULL, zAnimObjectRotateStateTick, NULL);
	ZAnim.AddCmd("OBJECT_MOTION", zAnimLoadObjectMotion, NULL, zAnimObjectMotionTick, NULL);
}

_zanim_cmd_hdr* CZAnimMain::AddCmd(const char* name,
	_zanim_cmd_hdr* (*parser)(_zrdr*),
	void(*begin)(_zanim_cmd_hdr*),
	bool(*tick)(_zanim_cmd_hdr*, float*),
	void(*end)(_zanim_cmd_hdr*))
{
	char* anim_name = NULL;
	
	return 0;
}