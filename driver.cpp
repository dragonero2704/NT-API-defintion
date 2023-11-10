#include <stdio.h>
#include "ntfuncs.h"
#include "macros.h"
#include <string.h>
uintptr_t HdnGetProcAddress(void *hModule, const wchar_t *wAPIName)
{
#if defined(_WIN32)
    unsigned char *lpBase = reinterpret_cast<unsigned char *>(hModule);
    IMAGE_DOS_HEADER *idhDosHeader = reinterpret_cast<IMAGE_DOS_HEADER *>(lpBase);
    if (idhDosHeader->e_magic == 0x5A4D)
    {
#if defined(_M_IX86)
        IMAGE_NT_HEADERS32 *inhNtHeader = reinterpret_cast<IMAGE_NT_HEADERS32 *>(lpBase + idhDosHeader->e_lfanew);
#elif defined(_M_AMD64)
        IMAGE_NT_HEADERS64 *inhNtHeader = reinterpret_cast<IMAGE_NT_HEADERS64 *>(lpBase + idhDosHeader->e_lfanew);
#endif
        if (inhNtHeader->Signature == 0x4550)
        {
            IMAGE_EXPORT_DIRECTORY *iedExportDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY *>(lpBase + inhNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
            for (unsigned int uiIter = 0; uiIter < iedExportDirectory->NumberOfNames; ++uiIter)
            {
                wchar_t *szNames = reinterpret_cast<wchar_t *>(lpBase + reinterpret_cast<unsigned long *>(lpBase + iedExportDirectory->AddressOfNames)[uiIter]);
                if (!wcscmp(szNames, wAPIName))
                {
                    unsigned short usOrdinal = reinterpret_cast<unsigned short *>(lpBase + iedExportDirectory->AddressOfNameOrdinals)[uiIter];
                    return reinterpret_cast<uintptr_t>(lpBase + reinterpret_cast<unsigned long *>(lpBase + iedExportDirectory->AddressOfFunctions)[usOrdinal]);
                }
            }
        }
    }
#endif
    return 0;
}

void *HdnGetModuleBase(const wchar_t *wModuleName)
{
#if defined(_WIN64)
#define PEBOffset 0x60
#define LdrOffset 0x18
#define ListOffset 0x10
    unsigned long long pPeb = __readgsqword(PEBOffset);
#elif defined(_WIN32)
#define PEBOffset 0x30
#define LdrOffset 0x0C
#define ListOffset 0x0C
    unsigned long pPeb = __readfsdword(PEBOffset);
#endif
    pPeb = *reinterpret_cast<decltype(pPeb) *>(pPeb + LdrOffset);
    PLDR_DATA_TABLE_ENTRY pModuleList = *reinterpret_cast<PLDR_DATA_TABLE_ENTRY *>(pPeb + ListOffset);
    while (pModuleList->DllBase)
    {
        if (!wcscmp(pModuleList->FullDllName.Buffer, wModuleName))
            return pModuleList->DllBase;
        pModuleList = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(pModuleList->InMemoryOrderLinks.Flink);
    }
    return nullptr;
}

int main()
{
    // get a a handle to ntdll.dll
    // FILE *out, *in;
    // out = fopen("output.txt", "w");
    // in = fopen("input.txt", "r");
    // if (out == NULL)
    // {
    //     // out error
    //     printf("[-]Error opening output.txt");
    //     out = stdout;
    // }
    // if (in == NULL)
    // {
    //     // in error
    //     printf("[-]Error opening input.txt");
    //     in = stdin;
    // }

    info("Getting handle to ntdll.dll");
    HMODULE ntdll = LoadLibraryW(L"ntdll.dll");

    NtOpenProcess myOpen = (NtOpenProcess)GetProcAddress(ntdll, "NtOpenProcess");
    NtCreateProcess myCreate = (NtCreateProcess)GetProcAddress(ntdll, "NtCreateProcess");

    HANDLE hNotepad;

    myCreate(
        &hNotepad,
        PROCESS_ALL_ACCESS,
        NULL,
        NULL,
        0, NULL, NULL, NULL
    );

    ok("success!");

    FreeConsole();
    return EXIT_SUCCESS;
}