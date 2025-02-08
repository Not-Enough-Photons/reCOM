#include "zutil.h"

#include "gamez/zArchive/zar.h"

s32 _countKeys(zar::CKey* key)
{
    s32 count = 1;

    auto base_it = key->begin();

    while (base_it != key->end())
    {
        zar::CKey* level1_key = *base_it;
        s32 count_lvl1 = 1;

        auto level1_it = level1_key->begin();

        while (level1_it != level1_key->end())
        {
            zar::CKey* level2_key = *level1_it;
            s32 count_lvl2 = 1;

            auto level2_it = level2_key->begin();
            
            while (level2_it != level2_key->end())
            {
                zar::CKey* level3_key = *level2_it;
                
                s32 count_lvl3 = _countKeys(level3_key);
                count_lvl2 = count_lvl2 + count_lvl3;

                ++level2_it;
            }

            ++level1_it;
            count_lvl1 = count_lvl1 + count_lvl2;
        }
        
        ++base_it;
        count = count + count_lvl1;
    }

    return count;
}
