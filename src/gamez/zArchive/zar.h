#pragma once
#include <string>
#include <list>

#include "gamez/zReader/zrdr.h"
#include "gamez/zUtil/util_stable.h"
#include "gamez/zUtil/util_systemio.h"

char* hackStr;
bool m_memalign = false;

namespace zar
{
	class CZAR;
	class CKey;
	class CKeyVec : public std::vector<CKey*> {};
	class CKeyRing : public std::list<CKey*> {};

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

	class CKey : public CKeyRing
	{
		friend class CZAR;
	public:
		CKey();
		CKey(char* name);

		CKey* InsertKey(CKey* key);
		CKey* FindKey(const char* name);

		bool Read(CZAR* file, CIO* fileBuffer, int offset);
		bool Write(CZAR* file);
	private:
		char* m_name;
		int m_size;
		int m_offset;
	};

	class CZAR
	{
		friend class CKey;
	public:
		CZAR(const char* name, CIO* io);
		~CZAR();
	public:
		bool Open(const char* name, int version, unsigned int mode, size_t padded_size);
		void Close();
		void Close(bool clearBuffer);
		void CloseKeepDir();

		CKey* CreateKey(const char* name);
		CKey* NewKey(const char* name);
		bool ReOpen(int count, int mode);

		CKey* OpenKey(const char* name);
		CKey* OpenKey(CKey* key);
		CKey* FindKey(const char* name);
		void CloseKey(CKey* key);

		bool Insert(CKey* key, void* buf, size_t size);
		CKey* Insert(const char* name, void* buf, size_t size);
		CKey* Insert(const char* name, unsigned int value);
		CKey* Insert(const char* name, int value);

		bool ReadDirectory(int appver, unsigned int mode);
		bool WriteDirectory();

		void SetFileName();
		size_t GetSize(const char* key);

		bool Fetch(CKey* key, void* buf, int size);
		bool Fetch(const char* name, int(*callback)(CZAR*, int, void*), void* buf);
		bool Fetch(const char* name, void* buf, int count);
		bool Fetch(const char* name, char** buf);
		bool Fetch(const char* name, float* buf);
		bool Fetch(const char* name, unsigned int* buf);
		bool Fetch(const char* name, int* buf);
		bool Fetch(const char* name, bool* buf);
		bool FetchAll(int(*callback)(CZAR*, char*, void*, int, void*), void* buf);
		bool FetchLIP(CKey* key, void** buf);
		int FetchString(const char* name, const char* buf, int length);

		CKey* GetOpenKey();

		void* ReleaseDataBuffer();

		void Securify(void* buf, size_t size);
		void Unsecurify(void* buf, size_t size);
	public:
		CIO* m_pFile;
		CIO* m_pFileAlloc;

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