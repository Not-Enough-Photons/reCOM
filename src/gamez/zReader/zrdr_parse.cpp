#include <ctype.h>

#include "zrdr.h"

#include "gamez/zUtil/util_stack.h"

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

// TODO:
// complete this function
_zrdr* zrdr_read(const char* name, const char* path, s32 flags)
{
	if (path && strlen(path) < MAX_ZRDR_PATH_LEN)
	{
		strcpy(cur_zrdr_path, path);
	}

	cur_zrdr_flags = flags;

	CRdrFile* rdrfile = CRdrArchive::FindRdr(name);
	
	if (flags & 1U != 0 || !rdrfile)
	{
		CBufferIO* io = new CBufferIO();
		if (!io->Open(zrdr_findfile(name, path)))
		{
			io->Close();
		}
		else
		{
			fstack.insert(fstack.begin(), io);

			rdrfile = new CRdrFile();

			if (rdrfile->ValidateFormat())
			{
				_zrdr* array = rdrfile->ReadArray();
				rdrfile->type = array->type;
				// rdrfile = array;
			}
		}

		rdrfile = NULL;
	}
	else
	{
		
	}
	
	return NULL;
}