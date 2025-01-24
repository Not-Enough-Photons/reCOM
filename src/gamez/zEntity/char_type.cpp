#include "zentity.h"

#include "gamez/zReader/zrdr.h"



CCharacterType::CCharacterType()
{
    m_name = NULL;
    m_ref_count = 0;
    m_model_file = NULL;
    m_model_file = NULL;
    m_parentID = 0;
    m_model = NULL;

    m_weapons.reserve(8);

    m_controller_id = 0;
}


bool CCharacterType::Open(const char* path)
{
    _zrdr* reader = zrdr_read(path, NULL, 0);

    if (reader)
    {
        _zrdr* gear = zrdr_findtag(reader, "gear");

        if (gear)
        {
            s32 i = 1;
            
            do
            {
                _zrdr* cur = &gear->array[i];
                
                char* name = zrdr_findstring(cur, "name");
                char* model_name = zrdr_findstring(cur, "model");
                _zrdr* ofs = zrdr_findtag(cur, "ofs");
                i++;
            }
            while (i < gear->array->integer);
        }
    }

    return true;
}
