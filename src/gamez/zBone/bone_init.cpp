#include "zbone.h"

bool is_init = false;
u32 bone_archive_version = 0;

CScriptArchive boneArchive;

bool zBoneInit()
{
    if (!is_init)
    {
        is_init = true;
    }

    return true;
}

bool zBoneOpen()
{
    bool isopen = false;
    bool opened = false;

    if (is_init)
    {
        isopen = false;

        if (boneArchive.m_pFile)
        {
            isopen = boneArchive.m_pFile->IsOpen();
        }

        if (!isopen)
        {
            boneArchive.Open("run/motion.zar", bone_archive_version, 1, 16);
            opened = false;

            if (boneArchive.m_pFile)
            {
                opened = boneArchive.m_pFile->IsOpen();
            }
        }
    }

    return opened;
}

bool zBoneLoadAll()
{
    return true;
}

bool zBoneClose()
{
    return true;
}