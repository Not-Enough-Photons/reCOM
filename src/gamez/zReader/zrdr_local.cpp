#include "zrdr_local.h"

bool _NeedQuotes(_zrdr* reader)
{
    char* c = 0;
    strtol(reader->string, &c, 0);

    size_t length = strlen(reader->string);

    bool matches = reader->string + length == c;
	
    if (!matches)
    {
        for (u32 i = 0; i < length; i++)
        {
            if (isspace(reader->string[i]) != 0)
            {
                return true;
            }

            if (reader->string[i] == ';')
            {
                return true;
            }
        }
    }

    return matches;
}

bool _OutputASCII(FILE* out, _zrdr* reader, s32 offset)
{
    ZRDR_TYPE type = static_cast<ZRDR_TYPE>(reader->type);

    if (type != ZRDR_ARRAY)
    {
        if (type == ZRDR_STRING)
        {
            if (_NeedQuotes(reader))
            {
                fprintf(out, "\"%s\" ", reader->string);
                return true;
            }

            fprintf(out, "%s", reader->string);
            return true;
        }

        if (type != ZRDR_REAL)
        {
            if (type != ZRDR_INTEGER)
            {
                return true;
            }
			
            fprintf(out, "%d", reader->integer);
        }

        fprintf(out, "%f", reader->real);
        return true;
    }

    return true;
}