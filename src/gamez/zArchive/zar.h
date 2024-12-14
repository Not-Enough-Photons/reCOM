#pragma once
#include <list>
#include <vector>

#include "gamez/zutil/util_stable.h"
#include "gamez/zutil/util_systemio.h"

#define ZAR_SECURE(secure, buf, size)\
	int line = 0; \
	if (secure && 0 < size)\
	{\
		if (8 < size)\
		{\
			do\
			{\
				unsigned char* byte = (unsigned char*)((int)buf + line);\
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
				* (unsigned char*)((int)buf + line) = ~*(unsigned char*)((int)buf + line); \
			}\
		}\

static char* hackStr;
static bool m_memalign = false;

namespace zar
{
	class CZAR;
	class CKey;
	class CKeyVec : public std::vector<CKey*> {};
	class CKeyRing : public std::list<CKey*> {};

	struct TAIL
	{
		int flags;
		int key_count;
		int stable_size;
		int stable_ofs;
		int reserved[16];
		int offset;
		int crc;
		int appversion;
		int version;
	};

	class CKey : public CKeyRing
	{
		friend class CZAR;
		friend class CZAREditor;
	public:
		CKey();
		CKey(char* name);
		~CKey();

		CKey* InsertKey(CKey* key);
		CKey* FindKey(const char* name);

		bool Read(CZAR* file, CBufferIO* io, unsigned int offset);
		bool Write(CZAR* file);

		char* GetName() const
		{
			return m_name;
		}

		int GetSize() const
		{
			return m_size;
		}

		int GetOffset()
		{
			return m_offset;
		}
	private:
		char* m_name;
		int m_size;
		int m_offset;
	};

	class CZAR
	{
		friend class CKey;
		friend class CZAREditor;
	public:
		CZAR(const char* name, CIO* io);
		~CZAR();
	public:
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
		bool ReOpen(int count, int mode) { return false; }

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
		CKey* Insert(const char* name, unsigned int value);
		CKey* Insert(const char* name, int value);

		bool ReadDirectory(int appver, unsigned int mode);
		bool WriteDirectory() { return false; }

		void SetFileName();
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
		bool Fetch(const char* name, int(*callback)(CZAR*, int, void*), void* buf);

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
		bool Fetch(const char* name, float* buf);

		/// <summary>
		/// Fetches an unsigned integer.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the unsigned integer.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, unsigned int* buf);

		/// <summary>
		/// Fetches an integer.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the integer.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, int* buf);

		/// <summary>
		/// Fetches a boolean.
		/// </summary>
		/// <param name="name"> - The name of the key to search and open.</param>
		/// <param name="buf"> - The buffer that stores the boolean.</param>
		/// <returns>Whether or not the fetch was successful.</returns>
		bool Fetch(const char* name, bool* buf);

		bool FetchAll(int(*callback)(CZAR*, char*, void*, int, void*), void* buf);

		bool FetchLIP(CKey* key, void** buf);

		size_t FetchString(const char* name, char* buf, size_t length);

		CKey* GetOpenKey() const;

		void* ReleaseDataBuffer();

		void Securify(void* buf, size_t size);
		void Unsecurify(void* buf, size_t size);
	private:
		CFileIO* m_pFileAlloc;
		CBufferIO* m_pFile;

		CKeyRing m_keys;

		void* m_databuffer;
		size_t m_databuffer_size;

		bool m_modified;
		bool m_data_padded;

		TAIL m_tail;

		CKey* m_root;
		CSTable* m_stable;
		char* m_filename;

		CKeyVec m_key_buffer;

		bool m_bCompress;
		bool m_bSecure;
	};
}