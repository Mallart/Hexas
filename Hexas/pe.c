#include "formats.h"
//#include <windows.h>

// If you're looking at this file and wondering, yes. All that not to include <windows.h> so
// my IDE is cross-platform. Yes it has been a hard time. Yes I now fear Mach-O.
// And no, I still don't have an idea on how I'll implement ELF.
// Thank Microsoft for having a free and public doc on these things.

#define _IMAGE_DOS_SIGNATURE 0x5A4D
#define _IMAGE_NT_SIGNATURE 0x00004550
#define PE32 0x10b
// equivalent to PE32+
#define PE64 0x20b
#define IMAGE_SIZEOF_FILE_HEADER 20

#pragma pack(push, 1)

typedef enum
{
	CHARACTERISTICS_RELOCS_STRIPPED         = 0x0001,  // Relocation info stripped from file.
	CHARACTERISTICS_EXECUTABLE_IMAGE        = 0x0002,  // File is executable  (i.e. no unresolved external references).
	CHARACTERISTICS_LINE_NUMS_STRIPPED      = 0x0004,  // Line nunbers stripped from file.
	CHARACTERISTICS_LOCAL_SYMS_STRIPPED     = 0x0008,  // Local symbols stripped from file.
	CHARACTERISTICS_AGGRESIVE_WS_TRIM       = 0x0010,  // Aggressively trim working set
	CHARACTERISTICS_LARGE_ADDRESS_AWARE     = 0x0020,  // App can handle >2gb addresses
	CHARACTERISTICS_BYTES_REVERSED_LO       = 0x0080,  // Bytes of machine word are reversed.
	CHARACTERISTICS_32BIT_MACHINE           = 0x0100,  // 32 bit word machine.
	CHARACTERISTICS_DEBUG_STRIPPED          = 0x0200,  // Debugging info stripped from file in .DBG file
	CHARACTERISTICS_REMOVABLE_RUN_FROM_SWAP = 0x0400,  // If Image is on removable media, copy and run from the swap file.
	CHARACTERISTICS_NET_RUN_FROM_SWAP       = 0x0800,  // If Image is on Net, copy and run from the swap file.
	CHARACTERISTICS_SYSTEM                  = 0x1000,  // System File.
	CHARACTERISTICS_DLL                     = 0x2000,  // File is a DLL.
	CHARACTERISTICS_UP_SYSTEM_ONLY          = 0x4000,  // File should only be run on a UP machine
	CHARACTERISTICS_BYTES_REVERSED_HI       = 0x8000,  // Bytes of machine word are reversed.
	CHARACTERISTICS_UNKNOWN					= 0,
	CHARACTERISTICS_TARGET_HOST				= 0x0001,  // Useful for indicating we want to interact with the host and not a WoW guest.
	CHARACTERISTICS_I386					= 0x014c,  // Intel 386.
	CHARACTERISTICS_R3000					= 0x0162,  // MIPS little-endian, 0x160 big-endian
	CHARACTERISTICS_R4000					= 0x0166,  // MIPS little-endian
	CHARACTERISTICS_R10000					= 0x0168,  // MIPS little-endian
	CHARACTERISTICS_WCEMIPSV2				= 0x0169,  // MIPS little-endian WCE v2
	CHARACTERISTICS_ALPHA					= 0x0184,  // Alpha_AXP
	CHARACTERISTICS_SH3						= 0x01a2,  // SH3 little-endian
	CHARACTERISTICS_SH3DSP					= 0x01a3,
	CHARACTERISTICS_SH3E					= 0x01a4,  // SH3E little-endian
	CHARACTERISTICS_SH4						= 0x01a6,  // SH4 little-endian
	CHARACTERISTICS_SH5						= 0x01a8,  // SH5
	CHARACTERISTICS_ARM						= 0x01c0,  // ARM Little-Endian
	CHARACTERISTICS_THUMB					= 0x01c2,  // ARM Thumb/Thumb-2 Little-Endian
	CHARACTERISTICS_ARMNT					= 0x01c4,  // ARM Thumb-2 Little-Endian
	CHARACTERISTICS_AM33					= 0x01d3,
	CHARACTERISTICS_POWERPC					= 0x01F0,  // IBM PowerPC Little-Endian
	CHARACTERISTICS_POWERPCFP				= 0x01f1,
	CHARACTERISTICS_IA64					= 0x0200,  // Intel 64
	CHARACTERISTICS_MIPS16					= 0x0266,  // MIPS
	CHARACTERISTICS_ALPHA64					= 0x0284,  // ALPHA64
	CHARACTERISTICS_MIPSFPU					= 0x0366,  // MIPS
	CHARACTERISTICS_MIPSFPU16				= 0x0466,  // MIPS
	CHARACTERISTICS_AXP64					= CHARACTERISTICS_ALPHA64,
	CHARACTERISTICS_TRICORE					= 0x0520,  // Infineon
	CHARACTERISTICS_CEF						= 0x0CEF,
	CHARACTERISTICS_EBC						= 0x0EBC,  // EFI Byte Code
	CHARACTERISTICS_AMD64					= 0x8664,  // AMD64 (K8)
	CHARACTERISTICS_M32R					= 0x9041,  // M32R little-endian
	CHARACTERISTICS_ARM64					= 0xAA64,  // ARM64 Little-Endian
	CHARACTERISTICS_CEE						= 0xC0EE,
} PE_CHARACTERISTICS;

typedef enum
{
	PE_MACHINE_UNKNOWN = 0x0,			// The content of this field is assumed to be applicable to any machine type
	PE_MACHINE_ALPHA = 0x184,			// Alpha AXP, 32 - bit address space
	PE_MACHINE_ALPHA64 = 0x284,			// Alpha 64, 64 - bit address space
	PE_MACHINE_AM33 = 0x1d3,			// Matsushita AM33
	PE_MACHINE_AMD64 = 0x8664,			//x64
	PE_MACHINE_ARM = 0x1c0,				//ARM little endian
	PE_MACHINE_ARM64 = 0xaa64,			//ARM64 little endian
	PE_MACHINE_ARMNT = 0x1c4,			//ARM Thumb - 2 little endian
	PE_MACHINE_AXP64 = 0x284,			//AXP 64 (Same as Alpha 64)
	PE_MACHINE_EBC = 0xebc,				//EFI byte code
	PE_MACHINE_I386 = 0x14c,			//Intel 386 or later processors and compatible processors
	PE_MACHINE_IA64 = 0x200,			//Intel Itanium processor family
	PE_MACHINE_LOONGARCH32 = 0x6232,	//LoongArch 32 - bit processor family
	PE_MACHINE_LOONGARCH64 = 0x6264,	//LoongArch 64 - bit processor family
	PE_MACHINE_M32R = 0x9041,			//Mitsubishi M32R little endian
	PE_MACHINE_MIPS16 = 0x266,			//MIPS16
	PE_MACHINE_MIPSFPU = 0x366,			//MIPS with FPU
	PE_MACHINE_MIPSFPU16 = 0x466,		//MIPS16 with FPU
	PE_MACHINE_POWERPC = 0x1f0,			//Power PC little endian
	PE_MACHINE_POWERPCFP = 0x1f1,		//Power PC with floating point support
	PE_MACHINE_R4000 = 0x166,			//MIPS little endian
	PE_MACHINE_RISCV32 = 0x5032,		//RISC - V 32 - bit address space
	PE_MACHINE_RISCV64 = 0x5064,		//RISC - V 64 - bit address space
	PE_MACHINE_RISCV128 = 0x5128,		//RISC - V 128 - bit address space
	PE_MACHINE_SH3 = 0x1a2,				//Hitachi SH3
	PE_MACHINE_SH3DSP = 0x1a3,			//Hitachi SH3 DSP
	PE_MACHINE_SH4 = 0x1a6,				//Hitachi SH4
	PE_MACHINE_SH5 = 0x1a8,				//Hitachi SH5
	PE_MACHINE_THUMB = 0x1c2,			//Thumb
	PE_MACHINE_WCEMIPSV2 = 0x169,		//MIPS little - endian WCE v2
} PE_MACHINE;

typedef struct _IMAGE_DATA_DIRECTORY {
	DWORD   VirtualAddress;
	DWORD   Size;
} IMAGE_DATA_DIRECTORY, * PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
	WORD		e_magic;                     // Magic number
	WORD		e_cblp;                      // Bytes on last page of file
	WORD		e_cp;                        // Pages in file
	WORD		e_crlc;                      // Relocations
	WORD		e_cparhdr;                   // Size of header in paragraphs
	WORD		e_minalloc;                  // Minimum extra paragraphs needed
	WORD		e_maxalloc;                  // Maximum extra paragraphs needed
	WORD		e_ss;                        // Initial (relative) SS value
	WORD		e_sp;                        // Initial SP value
	WORD		e_csum;                      // Checksum
	WORD		e_ip;                        // Initial IP value
	WORD		e_cs;                        // Initial (relative) CS value
	WORD		e_lfarlc;                    // File address of relocation table
	WORD		e_ovno;                      // Overlay number
	WORD		e_res[4];                    // Reserved words
	WORD		e_oemid;                     // OEM identifier (for e_oeminfo)
	WORD		e_oeminfo;                   // OEM information; e_oemid specific
	WORD		e_res2[10];                  // Reserved words
	uint32		e_lfanew;                    // File address of new exe header
} IMAGE_DOS_HEADER, * PIMAGE_DOS_HEADER;



typedef struct _IMAGE_OPTIONAL_HEADER {
	//
	// Standard fields.
	//

	WORD    Magic;
	BYTE    MajorLinkerVersion;
	BYTE    MinorLinkerVersion;
	DWORD   SizeOfCode;
	DWORD   SizeOfInitializedData;
	DWORD   SizeOfUninitializedData;
	DWORD   AddressOfEntryPoint;
	DWORD   BaseOfCode;
	DWORD   BaseOfData;

	//
	// NT additional fields.
	//

	DWORD   ImageBase;
	DWORD   SectionAlignment;
	DWORD   FileAlignment;
	WORD    MajorOperatingSystemVersion;
	WORD    MinorOperatingSystemVersion;
	WORD    MajorImageVersion;
	WORD    MinorImageVersion;
	WORD    MajorSubsystemVersion;
	WORD    MinorSubsystemVersion;
	DWORD   Win32VersionValue;
	DWORD   SizeOfImage;
	DWORD   SizeOfHeaders;
	DWORD   CheckSum;
	WORD    Subsystem;
	WORD    DllCharacteristics;
	DWORD   SizeOfStackReserve;
	DWORD   SizeOfStackCommit;
	DWORD   SizeOfHeapReserve;
	DWORD   SizeOfHeapCommit;
	DWORD   LoaderFlags;
	DWORD   NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[16];
} IMAGE_OPTIONAL_HEADER32, * PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
	WORD        Magic;
	BYTE        MajorLinkerVersion;
	BYTE        MinorLinkerVersion;
	DWORD       SizeOfCode;
	DWORD       SizeOfInitializedData;
	DWORD       SizeOfUninitializedData;
	DWORD       AddressOfEntryPoint;
	DWORD       BaseOfCode;
	uint64		ImageBase;
	DWORD       SectionAlignment;
	DWORD       FileAlignment;
	WORD        MajorOperatingSystemVersion;
	WORD        MinorOperatingSystemVersion;
	WORD        MajorImageVersion;
	WORD        MinorImageVersion;
	WORD        MajorSubsystemVersion;
	WORD        MinorSubsystemVersion;
	DWORD       Win32VersionValue;
	DWORD       SizeOfImage;
	DWORD       SizeOfHeaders;
	DWORD       CheckSum;
	WORD        Subsystem;
	WORD        DllCharacteristics;
	uint64		SizeOfStackReserve;
	uint64		SizeOfStackCommit;
	uint64		SizeOfHeapReserve;
	uint64		SizeOfHeapCommit;
	DWORD       LoaderFlags;
	DWORD       NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[16];
} IMAGE_OPTIONAL_HEADER64, * PIMAGE_OPTIONAL_HEADER64;


typedef struct _IMAGE_FILE_HEADER {
	WORD    Machine;
	WORD    NumberOfSections;
	DWORD   TimeDateStamp;
	DWORD   PointerToSymbolTable;
	DWORD   NumberOfSymbols;
	WORD    SizeOfOptionalHeader;
	WORD    Characteristics;
} IMAGE_FILE_HEADER, * PIMAGE_FILE_HEADER;

typedef struct _IMAGE_NT_HEADERS64 {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, * PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_NT_HEADERS {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} IMAGE_NT_HEADERS32, * PIMAGE_NT_HEADERS32;


#pragma pack(pop)

IMAGE_DOS_HEADER dos_header_new()
{
	return (IMAGE_DOS_HEADER)
	{
		.e_magic = 0x5A4D, // "MZ"
			.e_lfanew = sizeof(IMAGE_DOS_HEADER) + 0x40
	};
}

IMAGE_FILE_HEADER img_header_new(PE_MACHINE machine)
{
	return (IMAGE_FILE_HEADER)
	{
		.Machine = machine

	};
}


#define nt_header_new() pe32_header_new()
IMAGE_NT_HEADERS32 pe32_header_new()
{
	return (IMAGE_NT_HEADERS32)
	{
		.Signature = 0x00004550, // "PE\0\0"
			.FileHeader = 0,
			.OptionalHeader = 0,
	};
}

#define nt64_header_new() pe64_header_new()
IMAGE_NT_HEADERS64 pe64_header_new()
{
	return (IMAGE_NT_HEADERS64)
	{
		.Signature = 0x00004550, // "PE\0\0"
			.FileHeader = 0,
			.OptionalHeader = 0,
	};
}

IMAGE_OPTIONAL_HEADER32 opt32_header_new()
{
	return (IMAGE_OPTIONAL_HEADER32)
	{
		.Magic = PE32,
	};
}

IMAGE_OPTIONAL_HEADER64 opt64_header_new()
{
	return (IMAGE_OPTIONAL_HEADER64)
	{
		.Magic = PE64,
	};
}