#include "zrdr_main.h"
#include "zrdr_parse.h"

CZAREntry* CRdrIO::GetRootEntry(CZAREntry* entry, const char* name)
{
	void* nextP = NULL;
	CZAREntry* next = NULL;

	uint32_t baseEntries = 0;
	uint32_t entryIdx = 0;

	if (entry != NULL && entry->descriptor == ZEntryDescriptor::FOLDER)
	{
		baseEntries = entry->entries;

		for (int it = 0; nextP == NULL && it < baseEntries; it++)
		{
			entryIdx = 0;
			if (entry->descriptor == ZEntryDescriptor::FOLDER)
			{
				entryIdx = entry->entries;
			}

			next = NULL;
			if (it < baseEntries)
			{
				next = entry->next + it * EIGHT_BYTES;
			}

			if (next->descriptor == ZEntryDescriptor::FOLDER)
			{
				nextP = GetRootEntry(next, name, 0);
			}
			else
			{
				bool isRoot = false;
				if (next->descriptor == ZEntryDescriptor::STRING)
				{
					isRoot = strcmp(name, (char*)next->next) == 0;
				}

				if (isRoot)
				{
					nextP = entry->next + (it + 1) * EIGHT_BYTES;
				}
			}
		}
	}
}

CZAREntry* CRdrIO::GetRootEntry(CZAREntry* entry, const char* name, int it)
{
	void* nextP = NULL;
	CZAREntry* next = NULL;

	uint32_t baseEntries = 0;
	uint32_t entryIdx = 0;

	if (entry != NULL && entry->descriptor == ZEntryDescriptor::FOLDER)
	{
		baseEntries = entry->entries;

		for (; nextP == NULL && it < baseEntries; it++)
		{
			entryIdx = 0;
			if (entry->descriptor == ZEntryDescriptor::FOLDER)
			{
				entryIdx = entry->entries;
			}

			next = NULL;
			if (it < baseEntries)
			{
				next = entry->next + it * EIGHT_BYTES;
			}

			if (next->descriptor == ZEntryDescriptor::FOLDER)
			{
				nextP = GetRootEntry(next, name, 0);
			}
			else
			{
				bool isRoot = false;
				if (next->descriptor == ZEntryDescriptor::STRING)
				{
					isRoot = strcmp(name, (char*)next->next) == 0;
				}

				if (isRoot)
				{
					nextP = entry->next + (it + 1) * EIGHT_BYTES;
				}
			}
		}
	}
}

CZAREntry* CRdrIO::ReadRoot(CZAREntry* entry, const char* name)
{
	CZAREntry* result = NULL;
	CZAREntry* root = GetRootEntry(entry, name, 0);
	CZAREntry* available = NULL;
	ZEntryDescriptor descriptor;

	if (root != NULL)
	{
		if (root->descriptor == ZEntryDescriptor::STRING)
		{
			result = root->next;
		}
		else if (root->descriptor == ZEntryDescriptor::FOLDER)
		{
			if (root->entries == 0)
			{
				available = NULL;
			}
			else
			{
				available = root->next;
			}

			if (available != NULL)
			{
				if (root->entries == 0)
				{
					descriptor = ZEntryDescriptor::END;
				}
				else
				{
					descriptor = root->next->descriptor;
				}

				if (descriptor == ZEntryDescriptor::STRING)
				{
					descriptor = ZEntryDescriptor::END;
					if (root->entries != 0)
					{
						descriptor = root->next->descriptor;
					}

					result = NULL;
					if (descriptor == ZEntryDescriptor::STRING)
					{
						result = root->next->next;
					}
				}
			}
		}
	}

	return result;
}