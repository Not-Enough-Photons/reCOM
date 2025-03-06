#include "zvis.h"

namespace zdb
{
    void CMesh::SetMeshTextureSelects(_word128* wtexture, _word128* wname)
    {
        if (!wtexture->u8[2])
        {
            wtexture->u8[2] = 1;

            _word128* cur = wtexture + 1;
            
            if (wtexture->u16[0])
            {
                for (u32 i = 0; i < wtexture->u16[0]; i++)
                {
                    if (cur->u8[2] == 6)
                    {
                        ResolveTextureName(wname, cur);
                    }

                    cur++;
                }
            }
        }
    }
}