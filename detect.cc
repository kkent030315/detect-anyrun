
#define PHNT_VERSION PHNT_WIN11
#include <phnt_windows.h>
#include <phnt.h>

#include <iostream>

#pragma comment(lib, "ntdll.lib")

#define ANYRUN_DRIVER_DEVICE_NAME "\\\\?\\\\A3E64E55_fl"

static bool detect_anyrun()
{
    HANDLE hFile;
    
    hFile = CreateFile(
        /*lpFileName*/TEXT(ANYRUN_DRIVER_DEVICE_NAME),
        /*dwDesiredAccess*/GENERIC_READ,
        /*dwShareMode*/0,
        /*lpSecurityAttributes*/NULL,
        /*dwCreationDisposition*/OPEN_EXISTING,
        /*dwFlagsAndAttributes*/0,
        /*hTemplateFile*/NULL
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    CloseHandle(hFile);

    return true;
}

static int detect_anyrun2()
{
    NTSTATUS status;

    UNICODE_STRING name;
    RtlInitUnicodeString(&name, L"\\??\\C:\\Program Files\\KernelLogger");

    HANDLE hFile;
    IO_STATUS_BLOCK iosb = { 0 };
    OBJECT_ATTRIBUTES attrs;
    InitializeObjectAttributes(&attrs, &name, 0, NULL, NULL);

    status = NtCreateFile(
        /*FileHandle*/&hFile,
        /*DesiredAccess*/GENERIC_READ | SYNCHRONIZE,
        /*ObjectAttributes*/&attrs,
        /*IoStatusBlock*/&iosb,
        /*AllocationSize*/NULL,
        /*FileAttributes*/FILE_ATTRIBUTE_DIRECTORY,
        /*ShareAccess*/FILE_SHARE_READ,
        /*CreateDisposition*/FILE_OPEN,
        /*CreateOptions*/FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
        /*EaBuffer*/NULL,
        /*EaLength*/0
    );

    // ANY.RUN minifilter returns non-standard status code, STATUS_NO_SUCH_FILE
    // If this status code is returned, it means that the directory is protected
    // by the ANY.RUN minifilter driver.
    // To patch this detection, I would recommend returning STATUS_OBJECT_NAME_NOT_FOUND
    // that is a standard status code for this situation.
    if (status == STATUS_NO_SUCH_FILE)
        return true;

    // Not actually the case, maybe conflict with other software installation.
    if (NT_SUCCESS(status))
        NtClose(hFile);

    return false;
}

int main()
{
    if (detect_anyrun() || detect_anyrun2())
        wprintf(L"AnyRun detected\n");
    else
        wprintf(L"You're good to go\n");

    return 0;
}
