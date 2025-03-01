#pragma once
#include "gamez/zArchive/zar.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zUtil/util_stable.h"

#define MAX_ZRDR_PATH_LEN 767

#define pptoken_ifdef 0 
#define pptoken_else 1
#define pptoken_endif 2
#define pptoken_include 3
#define pptoken_undef 4

struct _zrdr;
class CRdrFile;

enum ZRDR_TYPE
{
	ZRDR_NULL,
	ZRDR_INTEGER,
	ZRDR_REAL,
	ZRDR_STRING,
	ZRDR_ARRAY
};

extern s32 cur_zrdr_flags;
extern char cur_zrdr_path[256];
extern std::list<char*> zrdr_symbols;

void _resolveA(_zrdr* reader, const _zrdr* other, char* tag);
void _resolveB(_zrdr* self, _zrdr* root, char* tag);
int _get_pptoken(char* token);
bool _preproc_filter(char* token, bool param_2);
bool _eval_defined(char* token);

/// Opens a zReader file.
/// @param reader Reader file name.
/// @param path Path to the reader file.
/// @param dummy Unused.
/// @return A zReader instance.
CRdrFile* zrdr_read(const char* reader, const char* path = NULL, s32 dummy = 0);

/// Concatenates a path to a zReader file.
/// @param file The name of the file.
/// @param path Path to the reader file.
/// @return The zReader file path created by this function.
const char* zrdr_findfile(const char* file, const char* path);

/// Frees a zReader object's memory.
/// @param reader The reader to free.
/// @return The number of bytes freed.
s32 zrdr_free(CRdrFile* reader);

/// Frees a node inside of a zReader array.
/// @param array The array to free.
void zrdr_freearray(_zrdr* array);

/// Finds a string.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @return The string from the found node. If NULL, this means that the tag doesn't exist.
char* zrdr_findstring(_zrdr* reader, const char* tag);

/// Finds an integer.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param output The output of the search, stored as a pointer.
/// @param startidx The start index of the array. Usually 1.
/// @return Successful if true, failure otherwise.
bool zrdr_findint(_zrdr* reader, const char* tag, s32* output, s32 startidx = 1);

/// Finds an unsigned integer. Will convert to a signed integer.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param output The output of the search, stored as a pointer.
/// @param startidx The start index of the array. Usually 1.
/// @return Successful if true, failure otherwise.
bool zrdr_finduint(_zrdr* reader, const char* tag, u32* output, s32 startidx = 1);

/// Finds a float, or a real decimal number.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param output The output of the search, stored as a pointer.
/// @param startidx The start index of the array. Usually 1.
/// @return Successful if true, failure otherwise.
bool zrdr_findreal(_zrdr* reader, const char* tag, f32* output, s32 startidx = 1);

/// Finds a boolean.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param output The output of the search, stored as a pointer.
/// @param startidx The start index of the array. Usually 1.
/// @return Successful if true, failure otherwise.
bool zrdr_findbool(_zrdr* reader, const char* tag, bool* output);

/// Finds a vector consisting of X and Y coordinates.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param output The output of the search, stored as a pointer.
/// @return Successful if true, failure otherwise.
bool zrdr_findPNT2D(_zrdr* reader, const char* tag, PNT2D* output);

/// Finds a vector consisting of X, Y, and Z coordinates.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param output The output of the search, stored as a pointer.
/// @return Successful if true, failure otherwise.
bool zrdr_findPNT3D(_zrdr* reader, const char* tag, PNT3D* output);

/// Finds a tag in a list of nodes.
/// A tag is the name associated with an array, or array-less object.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @return The tag node of the array. NULL if not found.
_zrdr* zrdr_findtag(_zrdr* reader, const char* tag);

/// Finds a tag in a list of nodes, which takes in a starting index.
/// A tag is the name associated with an array, or array-less object.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param startidx The index to start the search. Usually 1 because of a length reservation.
/// @return The tag node of the array. NULL if not found.
_zrdr* zrdr_findtag_startidx(_zrdr* reader, const char* tag, u32 startidx);

/// Converts an output value into an integer.
/// @param reader A zReader array node.
/// @param output The output of the search, stored as a pointer.
/// @param size The size of the element in bytes.
/// @return Whether or not the cast/search was successful.
bool zrdr_toINT(_zrdr* reader, s32* output, s32 size);

/// Converts an output value into a true or false value.
/// @param reader A zReader array node.
/// @param output The output of the search, stored as a pointer.
/// @return Whether or not the cast/search was successful.
bool zrdr_tobool(_zrdr* reader, bool* output);

/// Goes to the next tag in a node list and returns it.
/// @param reader A zReader array node.
/// @param tag The name of the tag to find.
/// @param size The size of the element in bytes.
/// @param other The other tag to go towards.
/// @return The tag node of the array. NULL if not found.
_zrdr* _zrdr_nexttag(_zrdr* reader, const char* tag, size_t size, _zrdr* other);

struct _zrdr
{
	_zrdr();
	_zrdr(_zrdr* reader, CSTable* stable);

	bool IsArray() const;
	void Clone(const _zrdr* other, const CSTable* table);
	int GetInt() const;
	char* Get(int offset) const;
	bool Write(FILE* file);

	u32 type : 8;
	u32 isclone : 1;
	u32 packed : 1;
	u32 unused : 6;
	u32 length : 16;
	
	union
	{
		f32 real;
		s32 integer;
		char* string;
		_zrdr* array;
	};
};

class CRdrFile : public _zrdr
{
public:
	CRdrFile();

	static CRdrFile* Load(zar::CZAR* archive, zar::CKey* key);

	zar::CKey* Insert(zar::CZAR* archive, zar::CKey* key);
	_zrdr* MakeUnion(const char* name, bool isstr);
	char ReadToken(_zrdr** array);
	_zrdr* ReadArray();
	bool Resolve(bool resolveA);

	bool ValidateFormat();

	CSTable m_strings;
	char* m_buffer;
	u32 m_size;
};

class CRdrArchive : public zar::CZAR
{
public:
	static s32 version; 
	
	static std::list<zar::CZAR*> m_list;

	static zar::CZAR* AddArchive(const char* name, const char* path);
	static bool RemoveArchive(const char* name, const char* path);

	static CRdrFile* FindRdr(const char* reader);

	static void OpenAll();
	static void CloseAll();
};
