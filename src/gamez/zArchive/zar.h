#pragma once
#include <string>
#include <list>

#include "gamez/zReader/zrdr_main.h"
#include "gamez/zUtil/util_stable.h"
#include "gamez/zUtil/util_systemio.h"

namespace zar
{
	class CKey;
	class CKeyVec : std::vector<CKey> {};
	class CKeyRing : std::list<CKey> {};

	const char* DEFAULT_ZAR_NAME = "ROOT";

	struct TAIL
	{
		int flags;
		int key_count;
		size_t stable_size;
		int stable_ofs;
		int reserved[16];
		int offset;
		int crc;
		int appversion;
		int version;
	};

	class CKey
	{
	public:
		CKey();
		CKey(const char* name);
		~CKey();

		CKey* InsertKey(CKey* key);
		CKey* FindKey(const char* key);
	private:
		CKeyRing CKeyRing;
		const char* m_name;
		int m_size;
		int m_offset;
	};

	class CZAR
	{
	public:
		CZAR(const char* name, CIO* io);
		~CZAR();
	public:
		void Open(char* name, int version, OpenFlags mode, int count);
		void Close();
		void CloseKeepDir();

		CKey* CreateKey();
		CKey* NewKey(const char* name);
		bool ReOpen(int count, int mode);

		CKey* OpenKey(const char* name);
		CKey* FindKey(const char* name);
		void CloseKey(CKey* key);

		bool Insert(CKey* key, void* buf, int size);

		void* ReadDirectory();
		void SetFileName();
		size_t GetSize(const char* key);

		bool Fetch(CKey* key, void* buf, int count, unsigned int flags);
		bool Fetch(const char* key, int(*callback)(CZAR*, int, void*), void* buf);
		bool Fetch(const char* key, void* buf, int count);
		bool Fetch(const char* key, const char** buf);
		bool Fetch(const char* key, float* value);
		bool Fetch(const char* key, unsigned int* value);
		bool Fetch(const char* key, int* value);
		bool Fetch(const char* key, bool* value);
		bool FetchAll(int(*callback)(CZAR*, char*, void*, int, void*), void* buf);
		bool FetchLIP(CKey* key, void** buf);
		int FetchString(const char* key, const char* str, int length);

		CKey* GetOpenKey();

		void* ReleaseDataBuffer();

		void Securify(void* buf, size_t size);
		void Unsecurify(void* buf, size_t size);
	private:
		CKeyRing m_keys;

		void* m_pFileAlloc;
		void* m_pFile;

		void* m_databuffer;
		size_t m_databuffer_size;

		bool m_modified;
		bool m_data_padded;

		TAIL m_tail;

		CKey* m_root;
		CSTable* m_stable;
		const char* m_filename;

		CKeyVec m_key_buffer;

		bool m_bCompress;
		bool m_bSecure;
	};
}