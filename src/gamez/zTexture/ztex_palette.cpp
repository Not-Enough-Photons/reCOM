#include "ztex.h"
#include "gamez/zArchive/zar.h"

namespace zdb
{
    bool CTexPalette::Read(zar::CZAR& archive)
    {
        if (archive.Fetch("par", this, sizeof(PALETTE_PARAMS)))
        {
            m_buffer = zmalloc(m_size);
            archive.Fetch("buf", m_buffer, m_size);
        }
        else
        {
            return false;
        }

        m_id = m_gsaddr;
        return true;
    }
}
