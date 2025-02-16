#include "zsys.h"

#include "gamez/zVideo/zvid.h"

#include <SDL3/SDL_render.h>

#include "SDL3/SDL_log.h"

CTTY theTerminal;

void CTTY::Print(char* string, ZLOG_LEVEL level)
{
    Print(string, strlen(string));

    if (m_buffer)
    {
        switch (level)
        {
        case ZLOG_LEVEL::LVL_INFO:
            SDL_Log(m_buffer);
            break;
        case ZLOG_LEVEL::LVL_WARN:
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, m_buffer);
            break;
        case ZLOG_LEVEL::LVL_ERROR:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, m_buffer);
            break;
        case ZLOG_LEVEL::LVL_CRITICAL:
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, m_buffer);
            break;
        }
    }
}

void CTTY::Print(char* buffer, size_t size)
{
    memset(m_buffer, 0, 1024);
    strcpy_s(m_buffer, size, buffer);
}

void CTTY::Render()
{
    SDL_SetRenderDrawColor(theWindow->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(theWindow->GetRenderer(), 0, 0, m_buffer);
    SDL_RenderPresent(theWindow->GetRenderer());
}