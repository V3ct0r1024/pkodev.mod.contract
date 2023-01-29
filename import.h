#pragma once
#include "structure.h"

namespace pkodev {

	class import final
	{
        public:
            // void CItemCommand::AddHint(int x, int y)
            typedef void(__thiscall* CItemCommand__AddHint__Ptr)(void*, int, int);
            static CItemCommand__AddHint__Ptr CItemCommand__AddHint;

            // void CCommandObj::PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            typedef void(__thiscall* CCommandObj__PushHint__Ptr)(void*, const char*, unsigned int, int, int);
            static CCommandObj__PushHint__Ptr CCommandObj__PushHint;

            // void CCommandObj::AddHintHeight(int height)
            typedef void(__thiscall* CCommandObj__AddHintHeight__Ptr)(void*, int);
            static CCommandObj__AddHintHeight__Ptr CCommandObj__AddHintHeight;

            // inline CChaRecord* GetChaRecordInfo(int nTypeID)
            typedef structure::CChaRecord* (__cdecl* GetChaRecordInfo__Ptr)(int);
            static GetChaRecordInfo__Ptr GetChaRecordInfo;

			// const char* CLanguageRecord::GetString(int nID)
            typedef const char* (__thiscall* CLanguageRecord__GetString__Ptr)(void*, int);
            static CLanguageRecord__GetString__Ptr CLanguageRecord__GetString;

			// CLanguageRecord g_oLangRec;
            static void* g_oLangRec;

			// CCommandObj
            static void* CCommandObj;

	};

}


