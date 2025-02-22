#include "zrdr_local.h"

bool CRdrEditor::push(const char* tag)
{
    if (tag && *tag != 0)
    {
        _zrdr* node = zrdr_alloc(sizeof(_zrdr), 1);
        node->type = ZRDR_STRING;

        node->string = m_strings.CreateString(tag);

        std::vector<_zrdr*> top = m_stack.top();
        top.insert(top.end(), node);
    }

    std::vector<_zrdr*> array;
    m_stack.push(array);
    return false;
}

bool CRdrEditor::pop()
{
    return true;
}

bool CRdrEditor::addint(const char* tag, s32 value)
{
    return true;
}

bool CRdrEditor::addintnode(s32 value)
{
    return true;
}

bool CRdrEditor::addSTRING(const char* tag, const char* value)
{
    return true;
}

bool CRdrEditor::addPNT3D(const char* tag, const PNT3D& value)
{
    return true;
}

bool CRdrEditor::addrdrnode(_zrdr* node)
{
    return true;
}

bool CRdrEditor::addstringnode(const char* node)
{
    return true;
}
