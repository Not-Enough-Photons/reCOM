#include "zsys.h"

#include "gamez/zVideo/zvid.h"

#include <SDL3/SDL_render.h>

CTTY theTerminal;

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