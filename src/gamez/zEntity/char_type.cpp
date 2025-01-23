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
        _zrdr* ai_settings = zrdr_findtag(reader, "ai_settings");
    }

    return true;
}
