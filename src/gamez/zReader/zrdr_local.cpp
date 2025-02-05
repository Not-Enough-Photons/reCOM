#include "zrdr_local.h"

#include <locale>

bool _NeedQuotes(_zrdr* reader)
{
    char* c = 0;
    
    strtol(reader->string, &c, 10);

    size_t length = strlen(reader->string);

    bool matches = reader->string + length == c;
	
    if (!matches)
    {
        for (u32 i = 0; i < length; i++)
        {
            std::locale loc;
            if (std::isspace(reader->string[i], loc))
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
    u32 node_idx = 0;
    u32 child_count = 0;
    ZRDR_TYPE type = static_cast<ZRDR_TYPE>(reader->type);

    if (type != ZRDR_ARRAY)
    {
        if (type == ZRDR_STRING)
        {
            if (_NeedQuotes(reader))
            {
                fprintf_s(out, "\"%s\"", reader->string);
                return true;
            }

            fprintf_s(out, "%s", reader->string);
            return true;
        }

        if (type != ZRDR_REAL)
        {
            if (type != ZRDR_INTEGER)
            {
                return true;
            }
			
            fprintf_s(out, " %i ", reader->integer);
        }

        fprintf_s(out, " %f ", reader->real);
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

        node_idx = 0;

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

    node_idx = 0;

    while (true)
    {
        _zrdr* node = NULL;
        type = static_cast<ZRDR_TYPE>(reader->type);
        child_count = 0;

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

    node_idx = 0;
    
    do
    {
        _zrdr* node = NULL;
        type = static_cast<ZRDR_TYPE>(reader->type);
        child_count = 0;
        
        if (type == ZRDR_ARRAY)
        {
            child_count = reader->array->integer - 1;
        }
        else
        {
            child_count = 0;
        }

        if (child_count <= node_idx + 1)
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

        if (node && node->type == ZRDR_STRING)
        {
            child_count = 0;

            if (type == ZRDR_ARRAY)
            {
                child_count = reader->array->integer - 1;
            }

            if (node_idx + 1 < child_count)
            {
                node = &reader->array[node_idx] + 2;
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

        node_idx++;
    } while (true);

    bool ungrouparray = true;

    if (ungrouparray)
    {
        fprintf_s(out, ")\n");

        node_idx = 0;

        if (offset - 1 > 0)
        {
            do
            {
                fprintf_s(out, " ");
                node_idx++;
            } while (node_idx < offset - 1);

            type = static_cast<ZRDR_TYPE>(reader->type);
            node_idx = 0;

            if (type == ZRDR_ARRAY)
            {
                node_idx = reader->array->integer - 1;
            }

            if (child_count == node_idx)
            {
                fprintf_s(out, "\n");

                child_count = 0;

                if (offset - 1 > 0)
                {
                    do
                    {
                        fprintf_s(out, " ");
                        child_count++;
                    } while (child_count < offset - 1);
                }
            }
            return true;
        }
    }
    else
    {
        fprintf_s(out, ")");
    }

    type = static_cast<ZRDR_TYPE>(reader->type);
    
    node_idx = 0;

    if (type == ZRDR_ARRAY)
    {
        node_idx = reader->array->integer - 1;
    }

    if (child_count == node_idx)
    {
        fprintf_s(out, "\n");

        child_count = 0;

        if (offset - 1 > 0)
        {
            do
            {
                fprintf_s(out, " ");
                child_count++;
            } while (child_count < offset - 1);
        }
    }
    
    return true;
}