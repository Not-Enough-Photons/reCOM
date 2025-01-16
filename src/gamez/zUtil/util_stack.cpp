#include "util_stack.h"

CFileStack fstack;

void CFileStack::pop(bool close)
{
    if (!empty())
    {
        CBufferIO* top = front();

        if (close)
        {
            top->Close();
        }
        else
        {
            top->Release();
        }
    }

    erase(begin(), end());
}