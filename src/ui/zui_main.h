#pragma once
#include "ai/ai_main.h";
#include "node/node_world.h"

enum TextColor
{
	WHITE,
	YELLOW,
	BLUE,
	ORANGE,
	RED,
	PURPLE
};

enum TextAlignment
{
	LEFT,
	CENTER,
	RIGHT
};

class C2D
{
public:
	static void Init();
	static void Open();
};

class C2DPoly : public C2D
{
public:
	C2DPoly();
};

class C2DBitmap : public C2D
{
public:
	C2DBitmap();
};

class CPlainBmp : public C2D
{

};

class C2DMessageString : public C2D
{

};

class CZUI
{
public:
	static void InitializeCommandEntry(FT_COMMAND command);
	static const char* GetTeamName(FIRE_TEAM team);
	static const char* GetRawCommandType(FT_COMMAND command);
	static const char* GetCommandDisplayName(FT_COMMAND command);
	static const char* GetProperRegroupDisplay(FT_COMMAND command);
	static const char* GetCommandDescription(FT_COMMAND command);
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