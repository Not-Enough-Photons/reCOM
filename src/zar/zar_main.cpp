#include "zar_main.h"

namespace zar
{
	zar::CZAR::CZAR(const char* name, char* param_2)
	{
		m_Name = "";
		m_Flags = 0x20002;
		m_StringTable = new zdb::CSTable("ROOT");

		if (param_2 == nullptr || param_2 == "ROOT")
		{
			m_Name = "ROOT";
		}

		m_Stream = new zdb::CFileIO();
		m_StreamShallowCopy = m_Stream;

		m_PaddingMaybe = 16;
	}

	void zar::CZAR::SetName(std::string name)
	{
		m_Name = name;
	}

	std::string zar::CZAR::GetName() const
	{
		return m_Name;
	}

	void zar::CZAR::SetStream(zdb::CFileIO* stream)
	{
		m_Stream = stream;
		m_StreamShallowCopy = m_Stream;
	}

	zdb::CFileIO zar::CZAR::GetStream() const
	{
		return *m_StreamShallowCopy;
	}

	zdb::CSTable zar::CZAR::GetStringTable() const
	{
		return *m_StringTable;
	}

	static void zar::ZARMain(zar::CZAR* archive, char* resourcePath, void* param_3, void* param_4)
	{
		if (resourcePath == '\0')
		{

		}

		zdb::CFileIO* stream = &archive->GetStream();

		if (stream == nullptr)
		{
			stream = new zdb::CFileIO();
			archive->SetStream(stream);
		}

		// char cVar1 = stream->UnknownFunction(stream, resourcePath, param_4)
		// if (cVar1 == '\0')
		// {
		//		if (param_6 != 0 && resourcePath != '\0')
		//		{
		//			if (archive->GetField0x18 == 0)
		//			{
		//				zdb::CFileIO* secondStream = new zdb::CFileIO();
		//				archive->SetSecondStream(secondStream);
		//			}
		//		}
		//		
		//		strcpy(firstBuffer, resourcePath);
		//		char* pcVar2 = FUN_00322080(0, '.');
		//		strcpy(secondBuffer, pcVar2)
		//		FUN_003202d8(secondBuffer, "_tmp");
		//		pcVar2 = FUN_00322080(0, '.');
		//		cVar1 = archive->UnknownFunction2(archive->GetField0x18(), secondBuffer, 60);
		//		return;
		// }
		/*else*/ if (archive->GetName() != resourcePath)
		{
			// zdb::Profiler::ProfilerAlloc(archive->GetName(), "zar_main.cpp", 102);
			archive->SetName("");
		}

		if (resourcePath == '\0' /* || resourcePath == puGpffff8188 */)
		{
			// archive->SetName(*(char*)(puGpffff8188));
		}
		else
		{
			// char* name = zdb::ZMemoryAllocator::AllocateString(resourcePath, 72, 109);
			// archive->SetName(name);
		}
	}
}