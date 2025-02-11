#include "zanim.h"

CZAnimMain ZAnim;
bool CZAnimMain::m_LoadFromZAR = false;

_zanim_cmd_set* CZAnimMain::GetCmdEntry(char* name, bool param_2)
{
	char* buf = NULL;
	char* splitname = SplitName(name, &buf);

	return NULL;
}

_zanim_cmd_set* CZAnimMain::GetCmdSet(char* name, bool param_2)
{
	_zanim_cmd_set* current_set = NULL;
	u32 i = 0;
	
	while (true)
	{
		current_set = &m_cmdset_list[i];
		if (m_cmdset_count <= current_set->count)
		{
			if (param_2)
			{
				current_set = (_zanim_cmd_set*)zrealloc(m_cmdset_list, m_cmdset_count + 1);
				m_cmdset_list = current_set;
				memset(m_cmdset_list + m_cmdset_count, 0, sizeof(_zanim_cmd_set));
				
				if (name)
				{
					m_cmdset_list[m_cmdset_count].name = zstrdup(name);
				}
			}
		}
	}
}

char* CZAnimMain::SplitName(char* name, char** splitname)
{
	char* haystack = NULL;

	if (!name)
	{
		*splitname = NULL;
		haystack = NULL;
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
	}

	return haystack;
}

bool CZAnimMain::InitCommands()
{
	//AddCmd("QUAD_ALIGN", NULL, NULL, zAnimQuadAlignTick, NULL);
	//
	//ZAnim.m_cmd_if = *AddCmd("IF", zAnimLoad_If, NULL, zAnimIfTick, NULL);
	//ZAnim.m_cmd_elseif = *AddCmd("ELSEIF", zAnimLoad_ElseIf, NULL, zAnimGoToEndIf, NULL);
	//ZAnim.m_cmd_else = *AddCmd("Else", zAnimLoad_ElseIf, NULL, zAnimGoToEndIf, NULL);
	//ZAnim.m_cmd_endif = *AddCmd("ENDIF", zAnimLoad_EndIf, NULL, zAnimEndIfTick, NULL);
	//
	//ZAnim.AddCmd("NODE_ACTIVE", zAnimLoadNodeActive, NULL, zAnimNodeActiveTick, NULL);
	//ZAnim.AddCmd("NODE_RENDERED", zAnimLoadNodeRendered, NULL, zAnimRangeTestTick, NULL);
	//ZAnim.AddCmd("RANGE_TEST", zAnimLoadRangeTest, NULL, zAnimRangeTestTick, NULL);
	//ZAnim.AddCmd("RANDOM_WEIGHT", zAnimLoadRandomWeight, NULL, zAnimRandomWeightTick, NULL);
	//ZAnim.AddCmd("FAIL", zAnimLoadFail, NULL, zAnimFailTick, NULL);
	//ZAnim.AddCmd("ANIM_HEALTH", zAnimLoadAnimHealthTest, NULL, zAnimHealthTestTick, NULL);
	//ZAnim.AddCmd("ANIM_LOD", zAnimLoadAnimLODTest, NULL, zAnimLODTestTick, NULL);
	//ZAnim.AddCmd("LOOP", zAnimLoadLoop, NULL, zAnimLoopTick, NULL);
	//ZAnim.AddCmd("WAIT", zAnimLoadWait, zAnimWaitBegin, zAnimWaitTick, NULL);
	//ZAnim.AddCmd("OBJECT_BLENDMODE", zAnimLoadObjectBlendMode, NULL, zAnimObjectBlendModeTick, NULL);
	//ZAnim.AddCmd("OBJECT_ACTIVE_STATE", zAnimLoadObjectActiveState, NULL, zAnimObjectActiveStateTick, NULL);
	//ZAnim.AddCmd("OBJECT_TRANSLATE_STATE", zAnimLoadObjectTranslateState, NULL, zAnimObjectTranslateStateTick, NULL);
	//ZAnim.AddCmd("OBJECT_ROTATE_STATE", zAnimLoadObjectRotateState, NULL, zAnimObjectRotateStateTick, NULL);
	//ZAnim.AddCmd("OBJECT_MOTION", zAnimLoadObjectMotion, zAnimObjectMotionBegin, zAnimObjectMotionTick, NULL);
	//ZAnim.AddCmd("OBJECT_MOTION_FROM_TO", zAnimLoadObjectMotionFromTo, zAnimObjectMotionFromToBegin, zAnimObjectMotionFromToTick, NULL);
	//ZAnim.AddCmd("OBJECT_OPACITY_FROM_TO", zAnimLoadObjectOpacityFromTo, zAnimObjectOpacityFromToBegin, zAnimObjectOpacityFromToTick, NULL);
	//ZAnim.AddCmd("OBJECT_MOTION_SI_SCRIPT", zAnimLoadObjectMotionSIScript, zAnimMultiObjectMotionScriptBegin, zAnimMultiObjectMotionScriptTick, NULL);
	//ZAnim.AddCmd("PARTICLE_SOURCE", zAnimLoadParticleSource, NULL, zAnimParticleSourceTick, NULL);
	//ZAnim.AddCmd("CAMERA", zAnimLoadCamera, zAnimCameraBegin, zAnimCameraTick, NULL);
	//ZAnim.AddCmd("DESTRUCTION_SOURCE", zAnimLoadDestructor, NULL, zAnimDestructorTick, NULL);
	//ZAnim.AddCmd("SOUND", zAnimLoadSound, NULL, zAnimSoundTick, NULL);
	//ZAnim.AddCmd("LIGHT", zAnimLoadLight, NULL, zAnimLightTick, NULL);
	//ZAnim.AddCmd("WHILE", zAnimLoadWhile, NULL, zAnimWhileTick, NULL);
	//
	//ZAnim.m_cmd_endwhile = *ZAnim.AddCmd("END_WHILE", zAnimLoadEndWhile, NULL, zAnimEndWhileTick, NULL);
	//ZAnim.m_cmd_ExprOperator = *ZAnim.AddCmd("EXPRESSION", NULL, NULL, NULL, NULL);
	//
	//ZAnim.AddCmd("BREAK", zAnimLoadBreak, NULL, zAnimBreakTick, NULL);
	//ZAnim.AddCmd("CALL_ANIMATION", zAnimLoadCallAnim, zAnimCallAnimBegin, zAnimCallAnimTick, NULL);
	//ZAnim.AddCmd("STOP_ANIMATION", zAnimLoadStopAnim, NULL, zAnimStopAnimTick, NULL);
	//ZAnim.AddCmd("PAUSE_ANIMATION", zAnimLoadPauseAnim, NULL, zAnimPauseAnimTick, NULL);
	//ZAnim.AddCmd("RESUME_ANIMATION", zAnimLoadResumeAnim, NULL, zAnimResumeAnimTick, NULL);
	//ZAnim.AddCmd("INVALIDATE_ANIMATION", zAnimLoadInvalidateAnim, NULL, zAnimInvalidateAnimTick, NULL);
	//ZAnim.AddCmd("CALL_SEQUENCE", zAnimLoadCallSequence, NULL, zAnimCallSequenceTick, NULL);
	//ZAnim.AddCmd("STOP_SEQUENCE", zAnimLoadStopSequence, NULL, zAnimStopSequenceTick, NULL);
	//ZAnim.AddCmd("DEBUG", zAnimLoadDebug, NULL, zAnimDebugTick, NULL);
	//ZAnim.AddCmd("OBJECT_ADD_CHILD", zAnimLoadObjectAddChild, NULL, zAnimObjectAddChildTick, NULL);
	//ZAnim.AddCmd("OBJECT_DELETE_CHILD", zAnimLoadObjectDeleteChild, NULL, zAnimObjectDeleteChildTick, NULL);
	//ZAnim.AddCmd("MESSAGE", zAnimLoadMessage, NULL, zAnimMessageTick, NULL);
	//ZAnim.AddCmd("TIMER", zAnimLoadTimer, NULL, zAnimTimerTick, NULL);
	//ZAnim.AddCmd("FIRE_WEAPON", zAnimLoadFireWeapon, NULL, zAnimFireWeaponTick, NULL);
	//ZAnim.AddCmd("ui::UI_COMMAND", zAnimLoadUIMenu, NULL, zAnimUIMenuTick, NULL);
	//ZAnim.AddCmd("ui::UI_APP_COMMAND", zAnimLoadUIAppMenu, NULL, zAnimUIAppMenuTick, NULL);

	return true;
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