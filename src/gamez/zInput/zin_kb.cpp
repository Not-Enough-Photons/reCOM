#include "zinput.h"

#include <SDL3/SDL_keyboard.h>

s32 InitKeyreadStuff()
{
    return SDL_HasKeyboard();
}

void CKeyboard::Tick(f32 delta)
{

}