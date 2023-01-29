#include "address.h"
#include "import.h"

namespace pkodev {

    import::CItemCommand__AddHint__Ptr import::CItemCommand__AddHint = reinterpret_cast<import::CItemCommand__AddHint__Ptr>(address::MOD_EXE_VERSION::CItemCommand__AddHint);
    import::CCommandObj__PushHint__Ptr import::CCommandObj__PushHint = reinterpret_cast<import::CCommandObj__PushHint__Ptr>(address::MOD_EXE_VERSION::CCommandObj__PushHint);
    import::CCommandObj__AddHintHeight__Ptr import::CCommandObj__AddHintHeight = reinterpret_cast<import::CCommandObj__AddHintHeight__Ptr>(address::MOD_EXE_VERSION::CCommandObj__AddHintHeight);
    import::GetChaRecordInfo__Ptr import::GetChaRecordInfo = reinterpret_cast<import::GetChaRecordInfo__Ptr>(address::MOD_EXE_VERSION::GetChaRecordInfo);
    import::CLanguageRecord__GetString__Ptr import::CLanguageRecord__GetString = reinterpret_cast<import::CLanguageRecord__GetString__Ptr>(address::MOD_EXE_VERSION::CLanguageRecord__GetString);
    void* import::g_oLangRec = reinterpret_cast<void*>(address::MOD_EXE_VERSION::CLanguageRecord);
    void* import::CCommandObj = reinterpret_cast<void*>(address::MOD_EXE_VERSION::CCommandObj);

}