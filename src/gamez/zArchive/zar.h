#pragma once
#include <list>
#include <vector>

#include "gamez/zSystem/zsys.h"
#include "gamez/zutil/util_stable.h"
#include "gamez/zutil/util_systemio.h"

#define ZAR_VERSION_1 0x20001
#define ZAR_VERSION_2 0x20002

#define ZAR_SECURE(secure, buf, size)\
	int line = 0; \
	if (secure && 0 < size)\
	{\
		if (8 < size)\
		{\
			do\
			{\
				unsigned char* byte = (unsigned char*)((s64)buf + line);\
				line += 8;\
				byte[0] = ~byte[0];\
				byte[1] = ~byte[1];\
				byte[2] = ~byte[2];\
				byte[3] = ~byte[3];\
				byte[4] = ~byte[4];\
				byte[5] = ~byte[5];\
				byte[6] = ~byte[6];\
				byte[7] = ~byte[7];\
			} while (line < size - 8);\
		}\
			for (; line < size; line++)\
			{\
				* (unsigned char*)((s64)buf + line) = ~*(unsigned char*)((s64)buf + line); \
			}\
		}\

static char* hackStr;
static bool m_memalign = false;

static char g_gamePath[1024] = "D:/";
static char* g_filePath;

namespace zar
{
	class CZAR;
	class CKey;
	class CKeyVec : public std::vector<CKey*> {};
	class CKeyRing : public std::list<CKey*> {};

	struct HEAD
	{
		s32 flags;
		s32 key_count;
		s32 stable_size;
		s32 stable_ofs;
		s32 padding;
		s32 reserved[16];
		s32 offset;
		s32 crc;
		s32 appversion;
		s32 version;
	};
	
	struct TAIL
	{
		s32 flags;
		s32 key_count;
		s32 stable_size;
		s32 stable_ofs;
		s32 reserved[16];
		s32 offset;
		s32 crc;
		s32 appversion;
		s32 version;
	};

	class CKey : public CKeyRing
	{
		friend class CZAR;
		friend class CZAREditor;
	public:
		CKey();
		CKey(char* name);
		~CKey();

		static void fixupKey(CSTable* table, CKey* key);

		CKey* InsertKey(CKey* key);
		CKey* FindKey(const char* name);

		bool Read(CZAR* file, CBufferIO* io, s64 offset);
		bool Write(CZAR* archive);
		bool Write(CZAR* archive, FILE* file);
		
		char* GetName() const
		{
			return m_name;
		}

		s32 GetSize() const
		{
			return m_size;
		}

		s32 GetOffset()
		{
			return m_offset;
		}
	private:
		char* m_name;
		s32 m_size;
		s32 m_offset;
	};

	class CZAR
	{
		friend class CKey;
		friend class CRdrArchive;
	public:
		CZAR(const char* name = NULL, CIO* io = NULL);
		~CZAR();

		/// <summary>
		/// Opens a ZAR file for reading into main memory.
		/// </summary>
		/// <param name="name"> - The name of the archive.</param>
		/// <param name="version"> - The version of the archive.</param>
		/// <param name="mode"> - The read mode for opening the file.</param>
		/// <param name="padded_size"> - The amount of padding bytes labelled "P" that exist in the file.</param>
		/// <returns>Whether or not the operation was successful.</returns>
		bool Open(const char* name, int version, unsigned int mode, size_t padded_size);
		
		/// <summary>
		/// Closes the ZAR file descriptor, and frees the resources associated with it.
		/// </summary>
		void Close();

		/// <summary>
		/// Closes the ZAR file descriptor, and frees the resources associated with it.
		/// </summary>
		/// <param name="clearBuffer"> - If the buffer object should be cleared out. </param>
		void Close(bool clearBuffer);

		/// <summary>
		/// Closes the ZAR file descriptor, but keeps the directory entries in memory for later use.
		/// </summary>
		void CloseKeepDir();

		/// <summary>
		/// Re-opens a previously closed ZAR file.
		/// </summary>
		/// <param name="count"> - The size of the archive.</param>
		/// <param name="mode"> - The read mode.</param>
		/// <returns>Whether or not the operation was successful.</returns>
		bool ReOpen(s32 appver, s32 mode);

		CKey* CreateKey(const char* name);

		/// <summary>
		/// Creates a new key and adds it to the buffer.
		/// </summary>
		/// <param name="name"> - The name of the key to create.</param>
		/// <returns>The key added to the buffer.</returns>
		CKey* NewKey(const char* name);

		/// <summary>
		/// Opens a key for reading into memory.
		/// </summary>
		/// <param name="name"> - The name of the key to find and open.</param>
		/// <returns>The opened key.</returns>
		CKey* OpenKey(const char* name);

		/// <summary>
		/// Opens a key for reading into memory.
		/// </summary>
		/// <param name="key">The reference of the key to open.</param>
		/// <returns>The opened key.</returns>
		CKey* OpenKey(CKey* key);

		/// <summary>
		/// Finds a key in the key buffer.
		/// </summary>
		/// <param name="name"> - The name of the key to find.</param>
		/// <returns>The key found in the buffer.</returns>
		CKey* FindKey(const char* name);

		/// <summary>
		/// Closes a key from the key ring, and frees its resources.
		/// </summary>
		/// <param name="key"> - The key to close.</param>
		void CloseKey(CKey* key);

		bool Insert(CKey* key, void* buf, size_t size);
		CKey* Insert(const char* name, void* buf, size_t size);
		CKey* Insert(const char* name, u32 value);
		CKey* Insert(const char* name, s32 value);

		/// <summary>
		/// Reads all keys and strings into memory.
		/// </summary>
		/// <param name="appver"> - The internal "FTS" version.</param>
		/// <param name="mode"> - The file mode represented by a number.</param>
		/// <returns>Whether or not the reading was successful.</returns>
		bool ReadDirectory(int appver, u32 mode);

		/// <summary>
		/// Reads all keys and strings into memory. Only works on release S1 and demos of S2.
		/// </summary>
		/// <param name="appver"> - The internal "FTS" version.</param>
		/// <param name="mode"> - The file mode represented by a number.</param>
		/// <returns>Whether or not the reading was successful.</returns>
		bool ReadDirectory_V2(s32 appver, u32 mode);
		
		bool WriteDirectory();
		bool WriteDirectory(FILE* file);

		void SetFilename(const char* name);
		size_t GetSize(const char* key);

		/// <summary>
		/// Fetches a resource of an arbitrary size.
		/// </summary>
		/// <param name="key"> - The key that points to a resource.</param>
		/// <param name="buf"> - The buffer that stores the bytes of the resource.</param>
		/// <param name="size"> - The size of the resource.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(CKey* key, void* buf, size_t size);

		/// <summary>
		/// Fetches a resource of arbitrary size, and fixes up the key so it can be added.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="callback"> - The fixup function pointer to call.</param>
		/// <param name="buf"> - The buffer that will store the resource post-fixup.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, s32(*callback)(CZAR*, s32, void*), void* buf);

		/// <summary>
		/// Fetches a resource of an arbitrary size.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the bytes of the resource.</param>
		/// <param name="size"> - The size of the resource.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, void* buf, size_t size);

		/// <summary>
		/// Fetches a string.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the string.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, char** buf);

		/// <summary>
		/// Fetches a float.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the float.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, f32* buf);

		/// <summary>
		/// Fetches an unsigned integer.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the unsigned integer.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, u32* buf);

		/// <summary>
		/// Fetches an integer.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the integer.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, s32* buf);

		/// <summary>
		/// Fetches a boolean.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the boolean.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, bool* buf);

		bool FetchAll(s32(*callback)(CZAR*, char*, void*, s32, void*), void* buf);

		/// Fetches a list of pointers.
		/// @param key The key to fetch the list of pointers.
		/// @param buf The list of pointers.
		/// @return Whether or not the fetch was successful.
		bool FetchLIP(CKey* key, void** buf);

		size_t FetchString(const char* name, char* buf, size_t length);

		CKey* GetOpenKey() const;

		void* ReleaseDataBuffer();

		void Securify(void* buf, size_t size);
		void Unsecurify(void* buf, size_t size);

		char* m_filename;
		CFileIO* m_pFileAlloc;
		CBufferIO* m_pFile;

		CKeyRing m_keys;

		void* m_databuffer;
		size_t m_databuffer_size;

		bool m_modified;
		bool m_data_padded;

		s32 m_rootOffset;
		
		HEAD m_head;
		TAIL m_tail;

		CKey* m_root;
		CSTable* m_stable;

		CKeyVec m_key_buffer;

		bool m_bCompress;
		bool m_bSecure;
	};
}