#pragma once
#include <list>

#include "gamez/zTwoD/ztwod.h"
#include "gamez/zWeapon/zweapon.h"

class CUIVariable;
class CUIVariableSpec;
class CUIVarManager;

s32 ZuiInit();

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

class CUIVariable : public _zrdr
{
public:
	void Set(_zrdr* reader);

	char* m_varname;
	std::vector<void*> m_attached_items;
	UIVAR_LONGEVITY m_longevity;
};

class CUIVariableSpec
{
public:
	CUIVariableSpec(_zrdr* reader);

	char* m_name;
	_zrdr* m_array;
	CSTable m_stable;
	u32 m_type;
};

class CUIVarManager
{
public:
	CUIVariable* Add(const char* name, _zrdr* reader, UIVAR_LONGEVITY longevity);
};

extern CUIVarManager theUIVarManager;

