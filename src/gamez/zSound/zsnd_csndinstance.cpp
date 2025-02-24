#include "zsnd.h"

#include "gamez/zSeal/zseal.h"

bool CSndInstance::m_allpaused = false;

std::list<CSndInstance*> CSndInstance::m_instancelist;
CSndInstance* CZSealBody::m_heartbeat_sndisnt = NULL;
s32 CZSealBody::m_heartbeat_curindex = 0;

void CSndInstance::ReleaseSoundInstance(CSndInstance* instance)
{
    
}

void CSndInstance::PauseAllSounds()
{
    if (!m_isDisabled)
    {
        m_allpaused = true;

        auto it = m_instancelist.begin();

        while (it != m_instancelist.end())
        {
            CSndInstance* instance = *it;

            if (!m_isDisabled)
            {
                instance->m_paused = true;

                if (instance->m_handle = 0xffffffff)
                {
                    if (instance->m_continueASAP)
                    {
                        instance->m_continueASAP = false;
                    }

                    instance->m_pauseASAP = true;
                }
                else
                {
                    // TODO: Wrapper for 989snd
                    // snd_PauseSound(instance->m_handle);
                }
            }
            
            ++it;
        }
    }
}

void CSndInstance::Stop()
{
    if (!m_isDisabled)
    {
        if (m_handle == 0xffffffff)
        {
            m_terminateASAP = true;
            m_terminateOnFinish = true;
        }
        else
        {
            // TODO: Wrappers for 989snd
            // snd_StopSound(m_handle);
        }
    }
}
