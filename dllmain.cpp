#include <Windows.h>
#include <detours.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set>

#include "loader.h"
#include "address.h"
#include "import.h"
#include "hook.h"
#include "structure.h"
#include "utils.h"

using namespace pkodev;

/*

	File: pkodev.mod.contract.json
	
	{
		"itemType" : 99,
		"colorActive": "0xFFFFA500",
		"colorCompleted" : "0xFF00FF00",
		"stringSet" : {
			"STRING_001" : 1000,
			"STRING_002" : 1001,
			"STRING_003" : 1002,
			"STRING_004" : 1003
		}
	}

	File: Client\scripts\table\StringSet.txt
	
	[1000]	"(Completed)"
	[1001]	"(Active)"
	[1002]	"Hunt: '{0}' x {1}"
	[1003]	"Progress: {0} / {1}"

*/

struct Settings final {
    unsigned short int itemType{ 99 };
    unsigned int colorActive{ 0xFFFFA500 };
    unsigned int colorCompleted{ 0xFF00FF00 };
    using i10n = std::unordered_map<std::string, int>;
    i10n language{ {"STRING_001", 1000}, {"STRING_002", 1001},
        {"STRING_003", 1002}, {"STRING_004", 1003} };
    Settings() = default;
};

void from_json(const nlohmann::json& j, Settings& settings);
bool LoadSettings(const std::filesystem::path& path, Settings& settings);
std::ostream& Log(std::ostream& os);

Settings g_Settings;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    return TRUE;
}

void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

void Start(const char* path)
{
    const auto settingsFilePath = std::filesystem::path(path)
		/ std::string(TOSTRING(MOD_NAME)).append(".json");

    if (LoadSettings(settingsFilePath, g_Settings) == false) {
        g_Settings = Settings();
        Log(std::cerr) << "Failed to load settings from the file "
            << settingsFilePath.string() << "!\n";
        Log(std::cerr) << "Default settings has been set.\n";
    }
    else {
        Log(std::clog) << "Settings successfully loaded from the file "
            << settingsFilePath.string() << "!\n";
    }

    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(reinterpret_cast<PVOID*>(&import::CItemCommand__AddHint), reinterpret_cast<PVOID>(&hook::CItemCommand__AddHint));
    DetourTransactionCommit();
}

void Stop()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(reinterpret_cast<PVOID*>(&import::CItemCommand__AddHint), reinterpret_cast<PVOID>(&hook::CItemCommand__AddHint));
    DetourTransactionCommit();
}

void from_json(const nlohmann::json& j, Settings& settings)
{
    std::string colorActive, colorCompleted;

    j.at("itemType").get_to(settings.itemType);
    j.at("colorActive").get_to(colorActive);
    j.at("colorCompleted").get_to(colorCompleted);
    j.at("stringSet").get_to(settings.language);

    settings.colorActive = std::stoul(colorActive, nullptr, 16);
    settings.colorCompleted = std::stoul(colorCompleted, nullptr, 16);
}

bool LoadSettings(const std::filesystem::path& path, Settings& settings)
{
    std::ifstream file(path, std::ios::in);
    if (file.is_open() == false) {
        Log(std::cerr) << "Failed to open the file " << path.string() << "!\n";
        return false;
    }

    try {
        const auto jsonData = nlohmann::json::parse(file);
        settings = jsonData.get<Settings>();
        for (const auto& str : { "STRING_001", "STRING_002", "STRING_003", "STRING_004" }) {
            if (settings.language.count(str) != 1) {
                Log(std::cerr) << "StringSet ID for string '" << str << "' not found in the settings file!\n";
                return false;
            }
        }
        return true;
    }
    catch (const nlohmann::json::exception& e)  {
        Log(std::cerr) << "JSON error: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        Log(std::cerr) << "Error: " << e.what() << '\n';
    }

    return false;
}

std::ostream& Log(std::ostream& os)
{
    return (os << '[' << TOSTRING(MOD_NAME) << "] ");
}

void __fastcall hook::CItemCommand__AddHint(void* This, void*, int x, int y)
{
    // This + 0x3E = number of items in the current slot
    if (utils::get<unsigned short int, 0x3E>(This) != 1) {
        import::CItemCommand__AddHint(This, x, y);
        return;
    }

    // This + 0x38 = CItemRecord class object
    const structure::CItemRecord* itemRecord = utils::get<structure::CItemRecord*, 0x38>(This);
    if ( (itemRecord == nullptr) || (itemRecord->sType != g_Settings.itemType) ) {
        import::CItemCommand__AddHint(This, x, y);
        return;
    }

    // This + 0x54 = ITEMATTR_VAL_STR (Monster ID)
    const structure::CChaRecord* chaRecord = import::GetChaRecordInfo(utils::get<unsigned short int, 0x54>(This));
    if (chaRecord == nullptr) {
        import::CItemCommand__AddHint(This, x, y);
        return; 
    }

    auto GetString = [](const std::string& id) -> std::string {
        return import::CLanguageRecord__GetString(import::g_oLangRec, g_Settings.language[id]);
    };

    auto PushHint = [](const std::string& str, unsigned int color = 0xFFFFFFFF) -> void {
        import::CCommandObj__PushHint(import::CCommandObj, str.c_str(), color, 5, 1);
        import::CCommandObj__AddHintHeight(import::CCommandObj, 6);
    };

    const auto amount = utils::get<unsigned short int, 0x58>(This); // This + 0x58 = ITEMATTR_VAL_AGI (monsters amount)
    const auto progress = utils::get<unsigned short int, 0x5C>(This); // This + 0x5C = ITEMATTR_VAL_DEX (current progress)
    const auto statusDesc = ( (progress >= amount) ? GetString("STRING_001") : GetString("STRING_002") );
    const auto statusColor = ( (progress >= amount) ? g_Settings.colorCompleted : g_Settings.colorActive );

    utils::set<bool>(address::MOD_EXE_VERSION::CCommandObj__SetHintIsCenter__Byte, true);

    PushHint(itemRecord->szName);
    PushHint(statusDesc, statusColor);
    PushHint(utils::safe_format(GetString("STRING_003"), chaRecord->szName, amount));
    PushHint(utils::safe_format(GetString("STRING_004"), progress, amount));
    PushHint(itemRecord->szDescriptor);
}