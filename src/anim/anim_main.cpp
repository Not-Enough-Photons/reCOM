#include "anim_main.h"
#include "util/util_stable.h"

#define PLACEHOLDER_FUNCTION NULL

int InitAnimLang()
{
	// FUN_001e7b10(0x562120);
	ParseAIKeywords();
	ParseResetBodyKeyword();
	ParseValveKeywords();
	ParseCameraKeywords();
	ParseThirdPersonCamKeyword();
	ParsePlayerConditionKeywords();
	ParseWindKeyword();

	ParseScriptKeyword((void*)0x562120, "HUD_ON", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_OFF", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_LETTERBOX_ON", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_LETTERBOX_OFF", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_TRIGGER_MISSION_CAM", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_START_DEFUSE_TIMER", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_STOP_DEFUSE_TIMER", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "HUD_TRIGGER_POPUP", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "NVG_NOISE", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "START_IMAGE_RECORDER", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((void*)0x562120, "STOP_IMAGE_RECORDER", PLACEHOLDER_FUNCTION, 0, PLACEHOLDER_FUNCTION, 0);

	ParseExecuteActionKeyword();
	ParseDecalRemovalKeyword();
}

int ParseScriptKeywords()
{
	// NOTE:
	// nullptrs are placeholders for functions that are not implemented yet.
	// When implemented, they will go right into the lexer/parser
	// of the animation event language Zipper used.
	// Seems to be some hybrid of VBScript and SoftImage's scripting language.

	// Align variable to quadword boundary?
	ParseScriptKeyword((int*)0x562120, "QUAD_ALIGN", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Branch keywords
	ParseScriptKeyword((int*)0x562120, "IF", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "ELSEIF", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "ELSE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "ENDIF", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Node specific function keywords
	ParseScriptKeyword((int*)0x562120, "OBJECT_MAKE_WORLDCHILD", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "NODE_ACTIVE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "NODE_RENDERED", 0, 0, PLACEHOLDER_FUNCTION, 0);

	ParseScriptKeyword((int*)0x562120, "RANGE_TEST", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "RANDOM_WEIGHT", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Disgustingly, overwhelmingly and utterly failed.
	ParseScriptKeyword((int*)0x562120, "FAIL", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Animation lifetime keywords?
	ParseScriptKeyword((int*)0x562120, "ANIM_HEALTH", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "ANIM_LOD", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Loop keywords
	ParseScriptKeyword((int*)0x562120, "LOOP", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "WAIT", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Object state keywords
	ParseScriptKeyword((int*)0x562120, "OBJECT_BLENDMODE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_ACTIVE_STATE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_TRANSLATE_STATE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_ROTATE_STATE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_AIM", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_MOTION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_MOTION_FROM_TO", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "WHEEL_MOTION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "SCROLL_MOTION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_OPACITY_FROM_TO", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_MOTION_SI_SCRIPT", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// VFX keywords
	ParseScriptKeyword((int*)0x562120, "PARTICLE_SOURCE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "CAMERA", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "DESTRUCTION_SOURCE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "SOUND", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "UPDATE_SHADOW_MAP_LIGHTING", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "LIGHT", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "BLUR3D", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "IRIS_EFFECT", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "SCALE_COLOR", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "TRUE_COLOR_SCALE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "RIPPLE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "RIPPLE_NODE_GROUP", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Range-based loop keywords
	ParseScriptKeyword((int*)0x562120, "WHILE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "END_WHILE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "FOR_CHILDREN", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "END_FOR_CHILDREN", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "EXPRESSION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "BREAK", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Animation playback and state keywords
	ParseScriptKeyword((int*)0x562120, "CALL_ANIMATION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "STOP_ANIMATION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "PAUSE_ANIMATION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "RESUME_ANIMATION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "INVALIDATE_ANIMATION", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "CALL_SEQUENCE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "STOP_SEQUENCE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "DEBUG", 0, 0, PLACEHOLDER_FUNCTION, 0);

	// Useful/utility keywords
	ParseScriptKeyword((int*)0x562120, "OBJECT_ADD_CHILD", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "OBJECT_DELETE_CHILD", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "MESSAGE", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "TIMER", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "FIRE_WEAPON", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "REMOVE_SATCHELS", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "ui::UI_COMMAND", 0, 0, PLACEHOLDER_FUNCTION, 0);
	ParseScriptKeyword((int*)0x562120, "ui::UI_APP_COMMAND", 0, 0, PLACEHOLDER_FUNCTION, 0);

	return 1;
}

void ParseScriptKeyword(void* ptr, char* token, int param_3, void(*func), bool(*condition), int param_6)
{
	char* src = 0;
	char* trim = 0;

	// Resolve namespace if there is one defined in the command token
	// Example:
	// ui::COMMAND will get shortened to COMMAND, and then a function is determined from there.
	trim = TrimUpTowards(token, "::");
	if (trim != 0)
	{
		src = reinterpret_cast<char*>(CreateString(token, "anim_main.cpp", 489));
		trim = TrimUpTowards(src, "::");
		*trim = '\0';
		token = trim + 2;
	}
}

bool CmdAddNode(zdb::CNode* node)
{
	zdb::Vector3 position;
	zdb::Quaternion rotation;
	zdb::Quaternion aQStack_50;

	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	zdb::Quaternion::Normalize(&rotation);
	// FUN_00256080(lVar2, aQStack_50) - quaternion related
	// FUN_00254c20(aQStack_50, &local_10, 1) - quaternion related
	zdb::Quaternion::ToEuler(&aQStack_50, &position);

	return true;
}