#include "zentity.h"

#include "gamez/zReader/zrdr.h"

bool CCharacterType::Open(const char* path)
{
    _zrdr* reader = zrdr_read(path, NULL, 0);

    if (reader)
    {
        _zrdr* ai_settings = zrdr_findtag(reader, "ai_settings");
    }

    return true;
}
