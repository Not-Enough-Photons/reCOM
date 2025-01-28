#include "zui.h"

#include "gamez/zUtil/util_stable.h"

CUIVariableSpec::CUIVariableSpec(_zrdr* reader)
{
    m_name = zrdr_findstring(reader, "NAME");
    m_array = NULL;
    m_stable = CSTable(0, 1024);

    _zrdr* var_value = zrdr_findtag(reader, "VALUE");

    if (var_value && var_value->type == ZRDR_ARRAY && var_value->array->integer == 2)
    {
        if (var_value->array->integer == 1)
        {
            var_value = NULL;
        }
        else
        {
            var_value = &var_value[1];
        }
    }

    if (var_value)
    {
        // m_array = new _zrdr(var_value, m_stable);
    }
}
