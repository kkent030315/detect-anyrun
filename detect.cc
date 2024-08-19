
#include <windows.h>
#include <iostream>

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

int main()
{
    if (detect_anyrun())
        wprintf(L"AnyRun detected\n");
    else
        wprintf(L"You're good to go\n");

    return 0;
}
