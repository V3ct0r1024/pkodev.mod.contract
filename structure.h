#pragma once

namespace pkodev { namespace structure {

	struct CItemRecord final {
		char nop0[0x08];
		char szName[0x48];
		char nop1[0xE4];
		short int sType;
		char nop2[0x0122];
		char szDescriptor[0x0101];
	};

	struct CChaRecord final {
		char nop0[0x08];
		char szName[0x28];
	};

} }