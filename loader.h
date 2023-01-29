#pragma once

// Destination executable files versions
const unsigned int EXE_UNKNOWN     = 0;   // 0
const unsigned int GAMESERVER_136  = 1;   // 1204708785
const unsigned int GAMESERVER_138  = 2;   // 1225867911
const unsigned int GAME_13X_0      = 3;   // 1222073761
const unsigned int GAME_13X_1      = 4;   // 1243412597
const unsigned int GAME_13X_2      = 5;   // 1252912474
const unsigned int GAME_13X_3      = 6;   // 1244511158
const unsigned int GAME_13X_4      = 7;   // 1585009030
const unsigned int GAME_13X_5      = 8;   // 1207214236
const unsigned int GATESERVER_138  = 101; // 1224838480
const unsigned int GROUPSERVER_138 = 201; // 1224838510

// Destination executable files linker build timestamps
const unsigned int TS_EXE_UNKNOWN     = 0;  
const unsigned int TS_GAMESERVER_136  = 1204708785;
const unsigned int TS_GAMESERVER_138  = 1225867911; 
const unsigned int TS_GAME_13X_0      = 1222073761;
const unsigned int TS_GAME_13X_1      = 1243412597;
const unsigned int TS_GAME_13X_2      = 1252912474;
const unsigned int TS_GAME_13X_3      = 1244511158; 
const unsigned int TS_GAME_13X_4      = 1585009030;
const unsigned int TS_GAME_13X_5      = 1207214236; 
const unsigned int TS_GATESERVER_138  = 1224838480;
const unsigned int TS_GROUPSERVER_138 = 1224838510;

// Mod information structure
struct mod_info
{
	// Name
	char name[128];

	// Version
	char version[64];

	// Author
	char author[64];

	// Destination .exe version
	unsigned int exe_version;
};

#ifndef PKODEVMODLOADER_EXPORTS

	#define STRINGIFY(x) #x
	#define TOSTRING(x) STRINGIFY(x)

	extern "C"
	{
		// Get mod information
		__declspec(dllexport) void __cdecl GetModInformation(mod_info& info);

		// Start the mod
		__declspec(dllexport) void __cdecl Start(const char* path);

		// Stop the mod
		__declspec(dllexport) void __cdecl Stop();
	}

#else

	// Functions pointers
	typedef void(*GetModInfo__Ptr)(mod_info& info); // Get mod information
	typedef void(*Start__Ptr)(const char* path);    // Start the mod
	typedef void(*Stop__Ptr)();                     // Stop the mod

#endif