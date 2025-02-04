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

    for (u32 i = 0; i + 1 < reader->array->integer - 1; i++)
    {
        _zrdr* node = NULL;
        
        if (i < reader->array->integer - 1)
        {
            node = &reader->array[i] + 1;
        }
        else
        {
            node = NULL;
        }

        if (node && node->type == ZRDR_STRING)
        {
            if (i + 1 < reader->array->integer - 1)
            {
                node = &reader->array[i] + 2;
            }
            else
            {
                node = NULL;
            }

            if (node && node->type == ZRDR_ARRAY)
            {
                break;
            }
        }
    }

    bool grouparray = false;
    for (u32 i = 0; i + 1 < reader->array->integer - 1; i++)
    {
        _zrdr* node = NULL;
        
        if (i < reader->array->integer - 1)
        {
            node = &reader->array[i] + 1;
        }
        else
        {
            node = NULL;
        }

        if (node && node->type == ZRDR_STRING)
        {
            if (i + 1 < reader->array->integer - 1)
            {
                node = &reader->array[i] + 2;
            }
            else
            {
                node = NULL;
            }

            if (node && node->type == ZRDR_ARRAY)
            {
                grouparray = true;
                break;
            }
        }
    }

    if (grouparray)
    {
        fprintf_s(out, "(\n");

        u32 node_idx = 0;

        if (offset + 1 > 0)
        {
            do
            {
                fprintf_s(out, " ");
                node_idx++;
            } while (node_idx < offset + 1);
        }
    }
    else
    {
        fprintf_s(out, "(");
    }

    u32 node_idx = 0;

    while (true)
    {
        _zrdr* node = NULL;
        type = static_cast<ZRDR_TYPE>(reader->type);
        u32 child_count = 0;

        if (type == ZRDR_ARRAY)
        {
            child_count = reader->array->integer - 1;
        }

        if (child_count <= node_idx)
        {
            break;
        }

        child_count = 0;

        if (type == ZRDR_ARRAY)
        {
            child_count = reader->array->integer - 1;
        }

        if (node_idx < child_count)
        {
            node = &reader->array[node_idx] + 1;
        }
        else
        {
            node = NULL;
        }

        _OutputASCII(out, node, offset + 1);
        node_idx++;
    }

    do
    {
        _zrdr* node = NULL;
        type = static_cast<ZRDR_TYPE>(reader->type);
        u32 child_count = 0;
        
        if (type == ZRDR_ARRAY)
        {
            
        }
    }
    while (true);
    
    return true;
}