#pragma once
#include <list>

#include "gamez/zGame/zgame.h"
#include "gamez/zTwoD/ztwod.h"
#include "gamez/zWeapon/zweapon.h"

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

class CZUI
{

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

extern CUIVarManager theUIVarManager;

