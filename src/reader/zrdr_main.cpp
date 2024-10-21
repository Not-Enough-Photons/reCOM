#include "zrdr_main.h"
#include "zrdr_parse.h"

#include "entity/zwep_ammo.h"

CZAREntry* CRdrIO::zrdr_findtag(CZAREntry* entry, const char* name)
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

CZAREntry* CRdrIO::zrdr_findtag_startidx(CZAREntry* entry, const char* name, int it)
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

int CRdrIO::zrdr_readreal(CZAREntry* entry, const char* name, float* output, int maxDepth)
{
	int ok = 0;
	CZAREntry* root = GetRootEntry(entry, name, 0);
	CZAREntry* next = NULL;

	if (root != NULL && root->descriptor == ZEntryDescriptor::FOLDER && maxDepth <= root->entries)
	{
		ok = 1;
		int i = 0;

		if (0 < maxDepth)
		{
			do
			{
				float value = 0.0f;

				int rootEntries = 0;
				if (root->descriptor == ZEntryDescriptor::FOLDER)
				{
					rootEntries = root->entries;
				}

				next = NULL;
				if (i < rootEntries)
				{
					next = root->next + i * EIGHT_BYTES;
				}

				if (next->descriptor == ZEntryDescriptor::VALUE)
				{
					value = *(float*)next->next;
				}
				else if (next->descriptor == ZEntryDescriptor::NONE)
				{
					value = *(float*)next->next;
				}
				else
				{
					value = 0.0f;
				}

				i++;
				*output = value;
				output++;
			} while (i < maxDepth);
		}
	}

	return ok;
}

int CRdrIO::zrdr_readstring(CZAREntry* entry, const char* name, void* buf)
{
	int status = 0;
	CZAREntry* root = GetRootEntry(entry, name, 0);

	if (root != NULL && buf != NULL)
	{
		if (root->descriptor == ZEntryDescriptor::FOLDER && root->entries != 0)
		{
			if (root->entries == 0)
			{
				root = NULL;
			}
			else
			{
				root = root->next;
			}
		}

		if (root->descriptor == ZEntryDescriptor::NONE && root->next == NULL)
		{
			buf = 0;
			status = 1;
		}
		else if (root->descriptor == ZEntryDescriptor::STRING)
		{
			buf = (void*)root->next;
			status = 1;
		}
	}

	return status;
}

void* CRdrIO::zrdr_findbool(CZAREntry* entry, double param_2, int param_3);
{
	auto tag = zrdr_findtag_startidx(entry, param_2, 1);
}

void CRdrIO::ReadZAmmo(void* param_1, CZAREntry* entry)
{
	const char* fileErr = "NOT FOUND";
	char* outStr;
	int outInt;
	float outFloat;

	zdb::CZAmmo* ammo = new zdb::CZAmmo();

	if (ReadString(entry, "InternalName", &outStr)) { ammo->SetInternalName(outStr); }
	else { ammo->SetInternalName(fileErr); }

	if (ReadString(entry, "DisplayName", &outStr)) { ammo->SetDisplayName(outStr); }
	else { ammo->SetDisplayName(fileErr); }

	if (ReadString(entry, "Description", &outStr)) { ammo->SetDescription(outStr); }
	else { ammo->SetDescription(fileErr); }

	if (ReadInt(entry, "ID", &outInt, 1)) { ammo->SetID(outInt); }
	else { ammo->SetID(0); }

	if (ReadFloat(entry, "ImpactDamage", &outFloat, 1)) { ammo->SetImpactDamage(outFloat); }
	else { ammo->SetImpactDamage(0.0f); }

	if (ReadString(entry, "HitAnimName", &outStr)) { ammo->SetHitAnimName(outStr); }
	else { ammo->SetHitAnimName(fileErr); }

	if (ReadFloat(entry, "Stun", &outFloat, 1)) { ammo->SetStun(outFloat); }
	else { ammo->SetStun(0.0f); }

	if (ReadFloat(entry, "Piercing", &outFloat, 1)) { ammo->SetPiercing(outFloat); }
	else { ammo->SetPiercing(0.0f); }

	if (ReadFloat(entry, "Explosion_Damage", &outFloat, 1)) { ammo->SetExplosionDamage(outFloat); }
	else { ammo->SetExplosionDamage(0.0f); }

	if (ReadFloat(entry, "Explosion_Radius", &outFloat, 1)) { ammo->SetExplosionRadius(outFloat); }
	else { ammo->SetExplosionRadius(0.0f); }

	if (ReadInt(entry, "NumProjectilesFired", &outInt, 1)) { ammo->SetProjectilesFired(outInt); }
	else { ammo->SetProjectilesFired(0); }

	if (ReadFloat(entry, "Blowback_Falloff", &outFloat, 1)) { ammo->SetBlowbackFalloff(outFloat); }
	else { ammo->SetBlowbackFalloff(0.0f); }

	if (ReadFloat(entry, "Blowback_End", &outFloat, 1)) { ammo->SetBlowbackFalloff(outFloat); }
	else { ammo->SetExplosionRadius(0.0f); }

	if (ReadFloat(entry, "ProximityDistance", &outFloat, 1)) { ammo->SetProximitySquared(outFloat); }
	else { ammo->SetProximitySquared(0.0f); }

	if (ReadFloat(entry, "AccelerationFactor", &outFloat, 1)) { ammo->SetAccelerationFactor(outFloat); }
	else { ammo->SetAccelerationFactor(1.0f); }
}

void CFileIO::Release()
{
	field4_0x4 = 0xffffffff;
}

void CBufferIO::Release()
{
	field14_0x14 = 0;
	field15_0x18 = 0;
	field16_0x1c = 0;
	field13_0x10 = 0;
	CFileIO::Release();
}