#include <ctype.h>

#include "zrdr.h"
#include "zrdr_local.h"

#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_stack.h"
#include "SDL3/SDL_egl.h"

std::list<char*> zrdr_symbols;

s32 defcount = 0;
bool init = false;

bool _preproc_filter(char* token, bool param_2)
{
	bool done = false;
	s32 defidx = defcount;
	char pathbuf[MAX_ZRDR_PATH_LEN + 1];
	
	if (!init)
	{
		defcount = 0;
		init = true;
	}

	u8 pptoken = _get_pptoken(token) & 255;

	if (pptoken != pptoken_undef)
	{
		if (pptoken == pptoken_include)
		{
			defidx = 0;
			
			do
			{
				CBufferIO* file = fstack.front();
				bool readtoken = file->fread(token, 1);

				// Reached the end of the line?
				if (!readtoken)
				{
					if (fstack.size() > 1)
					{
						fstack.pop(true);
						continue;
					}
				}
				else
				{
					
				}

				if (isalpha(*token) != 0)
				{
					// concatenate paths for zrdr includes
					const char* fpath = zrdr_findfile(pathbuf, cur_zrdr_path);
					CBufferIO file;

					if (!file.Open(fpath))
					{
						file.Close();
					}
					else
					{
						fstack.insert(fstack.begin(), &file);
						file.Release();
						file.Close();
					}

					return true;
				}

				if (defcount > MAX_ZRDR_PATH_LEN)
				{
					return true;
				}

				pathbuf[defidx] = *token;
				pathbuf[defidx + 1] = '\0';
				defidx++;
			} while (true);
		}

		if (pptoken == pptoken_endif)
		{
			defcount--;
		}
		else if (pptoken == pptoken_else)
		{
			if (param_2)
			{
				
			}
			else
			{
				// TODO:
				// why the FUCK ARE THERE
				// SO MANY GOD DAMN NESTED LOOPS JESUS CHRIST
				while (defidx <= defcount)
				{
					do
					{
						if (*token == '#')
						{
							break;
						}

						while (true)
						{
							CBufferIO* buf = fstack.front();

							if (buf->fread(token, 1))
							{
								break;
							}

							if (fstack.size() > 2)
							{
								done = false;
								continue;
							}

							fstack.pop(true);
						}

						done = true;
					} while (done);

					_preproc_filter(token, false);
				}
			}
		}
		else if (pptoken == pptoken_ifdef)
		{
			defcount++;

			if (!_eval_defined(token))
			{
				do
				{
					if (defcount <= defidx)
					{
						return false;
					}

					do
					{
						if (*token == '#')
						{
							break;
						}

						while (true)
						{
							CBufferIO* file = fstack.front();
							if (!file->fread(token, 1))
							{
								break;
							}

							if (fstack.size() > 2)
							{
								break;
							}

							fstack.pop(true);
						}
						
					} while (true);
				}
				while (!_preproc_filter(token, true));
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}

int _get_pptoken(char* token)
{
	s32 tokenidx = 0;
	char preprocbuf[MAX_ZRDR_PATH_LEN + 1];
	
	do
	{
		bool valid = true;

		while (true)
		{
			CBufferIO* file = fstack.front();
			bool readtoken = file->fread(token, 1);

			// Reached the end of the line?
			if (!readtoken)
			{
				break;
			}
			
			if (!valid)
			{
				return pptoken_undef;
			}

			if (isalpha(*token) != 0)
			{
				// #ifdef SYMBOL
				if (strcmp(preprocbuf, "ifdef") == 0)
				{
					return pptoken_ifdef;
				}

				// #else
				if (strcmp(preprocbuf, "else") == 0)
				{
					return pptoken_else;
				}

				// #endif
				if (strcmp(preprocbuf, "endif") == 0)
				{
					return pptoken_endif;
				}

				// #include "path/to/rdr"
				if (strcmp(preprocbuf, "include") == 0)
				{
					return pptoken_include;
				}
			}

			if (tokenidx > MAX_ZRDR_PATH_LEN)
			{
				return pptoken_undef;
			}

			preprocbuf[tokenidx] = *token;
			preprocbuf[tokenidx + 1] = '\0';
			tokenidx++;
		}

		if (fstack.size() < 2)
		{
			valid = false;
			return pptoken_undef;
		}
		
		fstack.pop(true);
	} while (true);
}

bool _eval_defined(char* token)
{
	s32 symidx = 0;
	char symbolbuf[MAX_ZRDR_PATH_LEN + 1];

	do
	{
		while (true)
		{
			CBufferIO* file = fstack.front();

			if (!file->fread(token, 1))
			{
				break;
			}

			if (isalpha(*token) != 0)
			{
				auto it = zrdr_symbols.begin();

				while (it != zrdr_symbols.end())
				{
					if (strcmp(symbolbuf, *it) == 0)
					{
						break;
					}
				}

				return *it != zrdr_symbols.front();
			}

			if (symidx > MAX_ZRDR_PATH_LEN)
			{
				return false;
			}

			symbolbuf[symidx] = *token;
			symbolbuf[symidx + 1] = '\0';
			symidx++;
		}

		if (fstack.size() < 2)
		{
			return false;
		}

		fstack.pop(true);
	}
	while (true);
}

void _resolveA(_zrdr* reader, const _zrdr* other, char* name)
{
	s32 idx = 0;
	s32 rdridx = 8;
	
	if (reader->type == ZRDR_STRING)
	{
		reader->string = zstrdup(name);
	}
	else
	{
		idx = 1;

		if (reader->type == ZRDR_ARRAY)
		{
			rdridx = 8;

			while (true)
			{
				
			}
		}
	}
}

void _resolveB(_zrdr* self, _zrdr* root, char* name)
{
	if (self->type == ZRDR_STRING)
	{
		// Assign string pointer to point at the entry in the string table
		self->string += (s32)name;
	}
	else if (self->type == ZRDR_ARRAY)
	{
		self->string += (s32)root;
	
		for (u32 i = 1; i < self->array->integer; i++)
		{
			_zrdr* child = &self->array[i];
			
			if (child->type == ZRDR_STRING)
			{
				child->string += (s32)name;
			}
			else if (child->type == ZRDR_ARRAY)
			{
				child->string += (s32)root;
				for (u32 j = 1; j < child->array->integer; j++)
				{
					_resolveB(&child->array[j], root, name);
				}
			}
		}
	}
}

CRdrFile* zrdr_read(const char* name, const char* path, s32 flags)
{
	if (path && strlen(path) < MAX_ZRDR_PATH_LEN)
	{
		strcpy(cur_zrdr_path, path);
	}

	cur_zrdr_flags = flags;

	CRdrFile* rdrfile = CRdrArchive::FindRdr(name);

	// Is the zrdr file non-compiled?
	if (flags & 1U != 0 || !rdrfile)
	{
		CBufferIO* io = new CBufferIO();

		// Search for it in the game disc directory
		if (!io->Open(zrdr_findfile(name, path)))
		{
			io->Close();
		}
		else
		{
			// Insert into file stack
			fstack.insert(fstack.begin(), io);

			rdrfile = new CRdrFile();

			// Check for any syntax errors
			if (rdrfile->ValidateFormat())
			{
				// Begin tokenization and create zrdr structure
				_zrdr* array = rdrfile->ReadArray();
				rdrfile->type = array->type;
				rdrfile->array = array->array;

				// Why is this here?
				zfree(array);
			}
			// Syntax error check failed
			else
			{
				// delete array;
				rdrfile = NULL;
			}

			if (!fstack.empty())
			{
				fstack.erase(fstack.begin(), fstack.end());
			}

			io->Close();
		}
	}
	
	return rdrfile;
}

_zrdr* CRdrFile::ReadArray()
{
	std::list<_zrdr*> arrays;
	_zrdr* array = NULL;
	char token = 1;
	bool endtag = false;
	
	while (!endtag && token != 0)
	{
		token = ReadToken(&array);

		if (token == 0)
		{
			continue;
		}
		
		if (array)
		{
			arrays.insert(arrays.begin(), array);
		}

		// Is the token the start of a new tag?
		if (token == '(')
		{
			arrays.insert(arrays.begin(), ReadArray());
		}
		// Is the token the end of the tag we're in?
		else if (token == ')')
		{
			endtag = true;
		}
	}

	// Allocate a parent and child node
	_zrdr* parent = zrdr_alloc(sizeof(_zrdr), 1);
	parent->type = ZRDR_ARRAY;

	_zrdr* child = zrdr_alloc(sizeof(_zrdr), arrays.size());
	child->type = ZRDR_INTEGER;

	// Set parent node equal to child, and append the size of
	// the child node to the first array element
	parent->array = child;
	parent->array->type = ZRDR_INTEGER;
	parent->array->integer = arrays.size();

	// When working with readers of this version,
	// The first index (0) is ALWAYS used to store the length.
	// In future zReader versions this was put into the
	// "length" bitfield.
	// When iterating through them, target the second index to access
	// the arrays.
	for (u32 i = 1; i < parent->array->integer; i++)
	{
		// The arrangement of each zReader node should go as follows:
		// Length, name, array
		array = arrays.front();
		arrays.erase(arrays.begin());

		parent->array[i] = *array;
		parent->array[i].array[0] = *array;
		zfree(array);
	}
	
	return parent;
}

char CRdrFile::ReadToken(_zrdr** array)
{
	CBufferIO* file = NULL;
	char pathbuf[783];
	u32 pathidx = 0;
	bool valid = false;
	char token = 0;
	bool nonum = false;
	
	do
	{
		file = fstack.front();

		if (!file->fread(&token, 1))
		{
			return 0;
		}

		valid = true;

		if (token == ';')
		{
			do
			{
				if (token == '\n')
				{
					break;
				}
				
				while (true)
				{
					file = fstack.front();

					if (!file->fread(&token, 1))
					{
						break;
					}
					
					if (fstack.size() < 2)
					{
						valid = false;
						return 0;
					}

					fstack.pop(true);
				}

				valid = true;
			} while (valid);
		}
		else
		{
			if (pathidx == 0 && token == '#')
			{
				_preproc_filter(&token, false);
			}

			// TODO:
			// Better character sanitization
			// You'll never know what kind of crazy characters can be made
			if (token == '(' || token == ')' || isspace(token))
			{
				if (pathidx == 0)
				{
					*array = NULL;
					return token;
				}

				_zrdr* zunion = MakeUnion(pathbuf, nonum);
				*array = zunion;
				return token;
			}

			if (pathidx > MAX_ZRDR_PATH_LEN)
			{
				*array = NULL;
				return 0;
			}

			if (token == '\"')
			{
				nonum = true;

				while (true)
				{
					file = fstack.front();

					if (file->fread(&token, 1) || fstack.size() < 2)
					{
						break;
					}

					fstack.pop(true);
				}

				while (token != '\"')
				{
					pathbuf[pathidx] = token;
					pathidx++;

					while (true)
					{
						file = fstack.front();

						if (file->fread(&token, 1) || fstack.size() < 2)
						{
							break;
						}

						fstack.pop(true);
					}
				}

				pathbuf[pathidx] = '\0';
				pathidx++;
			}
			else
			{
				pathbuf[pathidx] = token;
				pathbuf[pathidx + 1] = '\0';
				pathidx++;
			}

			continue;
		}

		if (fstack.size() < 2)
		{
			valid = false;
			return 0;
		}
		
		fstack.pop(true);
	}
	while (true);
}

_zrdr* CRdrFile::MakeUnion(const char* name, bool isstr)
{
	char* end;
	_zrdr* zunion = zrdr_alloc(sizeof(_zrdr), 1);
	zunion->type = ZRDR_NULL;

	size_t size = strlen(name);

	if (!isstr && size > 0)
	{
		s64 inum = strtol(name, &end, 10);

		if (size == end - name)
		{
			zunion->type = ZRDR_INTEGER;
			zunion->integer = inum;
			return zunion;
		}

		double dnum = strtod(name, &end);

		if (size == end - name)
		{
			zunion->type = ZRDR_REAL;
			zunion->real = dnum;
			return zunion;
		}
	}

	zunion->type = ZRDR_STRING;
	char* str = m_strings.CreateString(name);
	zunion->string = str;
	return zunion;
}

