#include <GL/glew.h>

#include <SDL3_image/SDL_image.h>

#include "gamez/zEntity/zentity.h"
#include "gamez/zFTS/fts_state.h"
#include "gamez/zIMGUI/zimgui.h"
#include "gamez/zVideo/zvid.h"
#include "gamez/zTexture/ztex.h"

SDL_AudioStream* audiostream;
u8* snd_data = NULL;
u32 snd_len = NULL;

CTestState::CTestState()
{
    m_name = zstrdup("TestState");
}

bool CTestState::Init()
{
    CSnd::Init();
    zar::CKey* key = CSnd::m_vagArchive.OpenKey("TC8_01.wav");
    void* buffer = zmalloc(key->GetSize());
    CSnd::m_vagArchive.Fetch(key, buffer, key->GetSize());
    
    SDL_IOStream* stream = SDL_IOFromMem(buffer, key->GetSize());
    
    snd_data = NULL;
    snd_len = NULL;
    SDL_AudioSpec audioSpec { SDL_AUDIO_S16, 1, 11025 };
    audiostream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);
    SDL_LoadWAV_IO(stream, false, &audioSpec, &snd_data, &snd_len);

    SDL_ResumeAudioStreamDevice(audiostream);
    
    return true;
}

void CTestState::Tick(f32 dT)
{
    if (SDL_GetAudioStreamAvailable(audiostream) < (s32)snd_len)
    {
        SDL_PutAudioStreamData(audiostream, snd_data, snd_len);
    }
    // zVid_Swap(true);
    // CZIMGUI::Tick(dT);
    SDL_RenderClear(theWindow->GetRenderer());
}
