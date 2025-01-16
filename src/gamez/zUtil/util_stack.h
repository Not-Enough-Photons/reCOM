#include "util_systemio.h"

class CFileStack;

extern CFileStack fstack;

class CFileStack : public std::list<CBufferIO*>
{
public:
    void pop(bool close);
};