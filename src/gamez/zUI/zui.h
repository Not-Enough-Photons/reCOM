#pragma once
#include <list>

// #include "gamez/zAI/zai.h"
#include "gamez/zAnim/zanim.h"
#include "gamez/zNode/znode.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zInput/zinput.h"
// #include "gamez/zTexture/ztex.h"
#include "gamez/zTwoD/ztwod.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"

class C2D;
class C2DFontEntry;
class CUIVariable;
class CUIVariableSpec;
class CUIVarManager;

enum UIVAR_LONGEVITY
{
	UIVL_DORMANT,
	UIVL_TEMPORARY,
	UIVL_PERMANENT,
	UIVL_PERSISTENT
};

enum tag_string_type
{
	STRING_PLAIN,
	STRING_GLOWY,
	STRING_NUM_TYPES
};

class CZUI
{
public:
	// static void InitializeCommandEntry(FT_COMMAND command);
	// static const char* GetTeamName(FIRE_TEAM team);
	// static const char* GetRawCommandType(FT_COMMAND command);
	// static const char* GetCommandDisplayName(FT_COMMAND command);
	// static const char* GetProperRegroupDisplay(FT_COMMAND command);
	// static const char* GetCommandDescription(FT_COMMAND command);
};

class CInGameWeaponSel : C2D
{
public:
	CInGameWeaponSel();
	~CInGameWeaponSel();

	void HudTick(float delta);
	void GetPrevItem(int param_1);
	void Clear();
	void Init(zdb::CWorld* world);
	void SelectWeapon();
	void SelectEquipment();
	bool CanSelectWeapon(int index) const;
};

class CUIVariable
{
public:
	void Set(_zrdr* reader);
};

class CUIVarManager
{
public:
	CUIVariable* Add(const char* name, _zrdr* reader, UIVAR_LONGEVITY longevity);
};

static CUIVarManager theUIVarManager;

class CHUD
{

};

class CCompassAnchor
{

};