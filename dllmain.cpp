#include <Windows.h>
#include <detours.h>

#include <cstdio>

#include "loader.h"

namespace pkodev
{
    namespace address
    {
        // Game.exe 0 (1222073761)
        namespace GAME_13X_0
        {
            // void CItemCommand::AddHint(int x, int y)
            const unsigned int CItemCommand__AddHint = 0x0048B830;

            // class CCommandObj
            const unsigned int CCommandObj = 0x00669920;

            // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            const unsigned int CCommandObj__PushHint = 0x00410310;

            // void CCommandObj::AddHintHeight( int height )
            const unsigned int CCommandObj__AddHintHeight = 0x00487D60;

            // void CCommandObj::SetHintIsCenter( bool v ) 
            const unsigned int CCommandObj__SetHintIsCenter__Byte = 0x00669938;

            // inline CChaRecord* GetChaRecordInfo( int nTypeID )
            const unsigned int GetChaRecordInfo = 0x0040CE40;
        }

        // Game.exe 1 (1243412597)
        namespace GAME_13X_1
        {
            // void CItemCommand::AddHint(int x, int y)
            const unsigned int CItemCommand__AddHint = 0x0048B8F0;

            // class CCommandObj
            const unsigned int CCommandObj = 0x00669920;

            // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            const unsigned int CCommandObj__PushHint = 0x00410310;

            // void CCommandObj::AddHintHeight( int height )
            const unsigned int CCommandObj__AddHintHeight = 0x00487E20;

            // void CCommandObj::SetHintIsCenter( bool v ) 
            const unsigned int CCommandObj__SetHintIsCenter__Byte = 0x00669938;

            // inline CChaRecord* GetChaRecordInfo( int nTypeID )
            const unsigned int GetChaRecordInfo = 0x0040CE40;
        }

        // Game.exe 2 (1252912474)
        namespace GAME_13X_2
        {
            // void CItemCommand::AddHint(int x, int y)
            const unsigned int CItemCommand__AddHint = 0x0048B990;

            // class CCommandObj
            const unsigned int CCommandObj = 0x00669920;

            // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            const unsigned int CCommandObj__PushHint = 0x00410310;

            // void CCommandObj::AddHintHeight( int height )
            const unsigned int CCommandObj__AddHintHeight = 0x00487EC0;

            // void CCommandObj::SetHintIsCenter( bool v ) 
            const unsigned int CCommandObj__SetHintIsCenter__Byte = 0x00669938;

            // inline CChaRecord* GetChaRecordInfo( int nTypeID )
            const unsigned int GetChaRecordInfo = 0x0040CE40;
        }

        // Game.exe 3 (1244511158)
        namespace GAME_13X_3
        {
            // void CItemCommand::AddHint(int x, int y)
            const unsigned int CItemCommand__AddHint = 0x0048B980;

            // class CCommandObj
            const unsigned int CCommandObj = 0x00669920;

            // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            const unsigned int CCommandObj__PushHint = 0x00410310;

            // void CCommandObj::AddHintHeight( int height )
            const unsigned int CCommandObj__AddHintHeight = 0x00487EB0;

            // void CCommandObj::SetHintIsCenter( bool v ) 
            const unsigned int CCommandObj__SetHintIsCenter__Byte = 0x00669938;

            // inline CChaRecord* GetChaRecordInfo( int nTypeID )
            const unsigned int GetChaRecordInfo = 0x0040CE40;
        }

        // Game.exe 4 (1585009030)
        namespace GAME_13X_4
        {
            // void CItemCommand::AddHint(int x, int y)
            const unsigned int CItemCommand__AddHint = 0x0048BB80;

            // class CCommandObj
            const unsigned int CCommandObj = 0x00669938;

            // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            const unsigned int CCommandObj__PushHint = 0x00410410;

            // void CCommandObj::AddHintHeight( int height )
            const unsigned int CCommandObj__AddHintHeight = 0x00488030;

            // void CCommandObj::SetHintIsCenter( bool v ) 
            const unsigned int CCommandObj__SetHintIsCenter__Byte = 0x00669950;

            // inline CChaRecord* GetChaRecordInfo( int nTypeID )
            const unsigned int GetChaRecordInfo = 0x0040CF40;
        }

        // Game.exe 5 (1207214236)
        namespace GAME_13X_5
        {
            // void CItemCommand::AddHint(int x, int y)
            const unsigned int CItemCommand__AddHint = 0x0048B500;

            // class CCommandObj
            const unsigned int CCommandObj = 0x00669928;

            // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
            const unsigned int CCommandObj__PushHint = 0x00410300;

            // void CCommandObj::AddHintHeight( int height )
            const unsigned int CCommandObj__AddHintHeight = 0x00487A30;

            // void CCommandObj::SetHintIsCenter( bool v ) 
            const unsigned int CCommandObj__SetHintIsCenter__Byte = 0x00669940;

            // inline CChaRecord* GetChaRecordInfo( int nTypeID )
            const unsigned int GetChaRecordInfo = 0x0040CE30;
        }
    }

    namespace pointer
    {
        // void CItemCommand::AddHint(int x, int y)
        typedef void (__thiscall* CItemCommand__AddHint__Ptr)(void*, int, int);
        CItemCommand__AddHint__Ptr CItemCommand__AddHint = (CItemCommand__AddHint__Ptr)(void*)(address::MOD_EXE_VERSION::CItemCommand__AddHint);

        // void PushHint(const char* str, DWORD color = COLOR_WHITE, int height = 5, int font = 0, int index = -1)
        typedef void(__thiscall* CCommandObj__PushHint__Ptr)(void*, const char*, unsigned int, int, int);
        CCommandObj__PushHint__Ptr CCommandObj__PushHint = (CCommandObj__PushHint__Ptr)(void*)(address::MOD_EXE_VERSION::CCommandObj__PushHint);

        // void CCommandObj::AddHintHeight( int height )
        typedef void(__thiscall* CCommandObj__AddHintHeight__Ptr)(void*, int);
        CCommandObj__AddHintHeight__Ptr CCommandObj__AddHintHeight = (CCommandObj__AddHintHeight__Ptr)(void*)(address::MOD_EXE_VERSION::CCommandObj__AddHintHeight);

        // inline CChaRecord* GetChaRecordInfo( int nTypeID )
        typedef void* (__cdecl* GetChaRecordInfo__Ptr)(int);
        GetChaRecordInfo__Ptr GetChaRecordInfo = (GetChaRecordInfo__Ptr)(void*)(address::MOD_EXE_VERSION::GetChaRecordInfo);
    }

    namespace hook
    {
        // void CItemCommand::AddHint(int x, int y)
        void __fastcall CItemCommand__AddHint(void* This, void* NotUsed, int x, int y);
    }
}

// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CItemCommand__AddHint, pkodev::hook::CItemCommand__AddHint);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CItemCommand__AddHint, pkodev::hook::CItemCommand__AddHint);
    DetourTransactionCommit();
}

// void CItemCommand::AddHint(int x, int y)
void __fastcall pkodev::hook::CItemCommand__AddHint(void* This, void* NotUsed,
    int x, int y)
{
    // Read unsigned short int from memory
    auto read_uint16 = [](void* from, unsigned int offset) -> unsigned short int
    {
        return *reinterpret_cast<unsigned short int*>(reinterpret_cast<unsigned int>(from) + offset);
    };

    // Read unsigned int from memory
    auto read_uint32 = [](void* from, unsigned int offset) -> unsigned int
    {
        return *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(from) + offset);
    };

    // Check that there is the only one item in the slot
    if (read_uint16(This, 0x3E) == 1)
    {
        // Get pointer to the data of the item which hint is rendering at the moment (from ItemInfo.txt)
        void* item_record = reinterpret_cast<void*>( read_uint32(This, 0x38) );

        // Check the item type
        if (read_uint32(item_record, 0x0134) == 99)
        {
            // Search for the monster data (from CharacterInfo.txt)
            void* cha_record = pkodev::pointer::GetChaRecordInfo( read_uint16(This, 0x54) );

            // Check that monster is found
            if (cha_record != nullptr)
            {
                // Buffer for strings
                static char buf[128]{ 0x00 };

                // Read the contract data
                unsigned short int max = read_uint16(This, 0x58);
                unsigned short int cur = read_uint16(This, 0x5C);

                // Read pointer to the CCommandObj object
                void* command_obj_ptr = reinterpret_cast<void*>( pkodev::address::MOD_EXE_VERSION::CCommandObj  );

                // Set center alignment
                *reinterpret_cast<unsigned char*>(
                    pkodev::address::MOD_EXE_VERSION::CCommandObj__SetHintIsCenter__Byte
                ) = 0x01;

                // Get the monster name
                const char* cha_name = reinterpret_cast<const char*>(
                    reinterpret_cast<unsigned int>(cha_record) + 0x08 
                );

                // Get the item name
                const char* item_name = reinterpret_cast<const char*>( 
                    reinterpret_cast<unsigned int>(item_record) + 0x08 
                );

                // Get the item description
                const char* item_desc = reinterpret_cast<const char*>( 
                    reinterpret_cast<unsigned int>(item_record) + 0x0258 
                );

                // Print the contract name
                pkodev::pointer::CCommandObj__PushHint(command_obj_ptr, item_name, 0xFFFFFFFF, 5, 1);
                pkodev::pointer::CCommandObj__AddHintHeight(command_obj_ptr, 6);

                // Print the contract status
                {
                    // Check that the contract is completed
                    if (cur >= max)
                    {
                        // Completed
                        pkodev::pointer::CCommandObj__PushHint(command_obj_ptr, "(Completed)", 0xFF00FF00, 5, 1);
                    }
                    else
                    {
                        // Still active
                        pkodev::pointer::CCommandObj__PushHint(command_obj_ptr, "(Active)", 0xFFFFA500, 5, 1);
                    }

                    // Add height
                    pkodev::pointer::CCommandObj__AddHintHeight(command_obj_ptr, 6);
                }

                // Print the monster name
                sprintf_s(buf, sizeof(buf), "Hunt: '%s' x %d", cha_name, max);
                pkodev::pointer::CCommandObj__PushHint(command_obj_ptr, buf, 0xFFFFFFFF, 5, 1);
                pkodev::pointer::CCommandObj__AddHintHeight(command_obj_ptr, 6);

                // Print progress
                sprintf_s(buf, sizeof(buf), "Progress: %d / %d", cur, max);
                pkodev::pointer::CCommandObj__PushHint(command_obj_ptr, buf, 0xFFFFFFFF, 5, 1);
                pkodev::pointer::CCommandObj__AddHintHeight(command_obj_ptr, 6);

                // Print description
                pkodev::pointer::CCommandObj__PushHint(command_obj_ptr, item_desc, 0xFFFFFFFF, 5, 1);

                // Exit from the hook
                return;
            }
        }
    }

    // Call the original method void CItemCommand::AddHint(int x, int y)
    pkodev::pointer::CItemCommand__AddHint(This, x, y);
}