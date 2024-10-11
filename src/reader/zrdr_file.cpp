#include "zrdr_main.h"
#include "zrdr_parse.h"

int CRdrArchive::GetReaderHashDifference(unsigned char parentByte, unsigned char childByte)
{
    int parentOffset = static_cast<int>(parentByte);
    int childOffset = static_cast<int>(childByte);

    if ((ZAR_HASH_TABLE[parentByte] & 1) != 0)
    {
        parentOffset = parentByte + 32;
    }

    if ((ZAR_HASH_TABLE[childByte] & 1) != 0)
    {
        childOffset = childByte + 32;
    }

    return childOffset = parentOffset - childOffset;
}

int CRdrArchive::GetNextReader(const char* parentReader, const char* childReader)
{
    char parentChar = *parentReader;
    char childChar = *childReader;

    if (parentChar != 0)
    {
        int parentValue = static_cast<int>(parentChar + 32);
        int childValue = static_cast<int>(childChar + 32);

        if ((ZAR_HASH_TABLE[parentChar] & 1) == 0)
        {
            parentValue = static_cast<int>(parentChar);
        }

        if ((ZAR_HASH_TABLE[childChar] & 1) == 0)
        {
            childValue = static_cast<int>(childChar);
        }

        if (parentValue != childValue)
        {
            return GetReaderHashDifference(*parentReader, *childReader);
        }

        parentReader++;

        unsigned char parentByte = 0;
        unsigned char childByte = 0;

        while (true)
        {
            std::cout << *childReader << std::endl;
            childReader++;

            parentByte = *parentReader;

            if (parentByte == 0)
            {
                break;
            }

            childByte = *childReader;
            parentValue = parentByte;
            if ((ZAR_HASH_TABLE[parentByte] & 1) != 0)
            {
                std::cout << "Parent byte is in the hash table" << std::endl;
                parentValue = parentByte + 32;
            }

            childValue = childByte + 32;
            if ((ZAR_HASH_TABLE[childByte] & 1) == 0)
            {
                std::cout << "Child byte is in the hash table" << std::endl;
                childValue = childByte;
            }

            if (parentValue != childValue)
            {
                std::cout << "Parent value does not equal the child value!" << std::endl;
                break;
            }

            parentReader++;
        }
    }

    return GetReaderHashDifference(*parentReader, *childReader);
}