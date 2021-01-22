// https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexa

#include "Windows.h"
#include <cstdlib>
#include <iostream>

/*
    RegCreateKeyExA Function -
    
    LSTATUS RegCreateKeyExA(
        HKEY                        hKey,
        LPCSTR                      lpSubKey,
        DWORD                       Reserved,
        LPSTR                       lpClass,
        DWORD                       dwOptions,
        REGSAM                      samDesired,
        const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        PHKEY                       phkResult,
        LPDWORD                     lpdwDisposition
    );
*/

/*
    RegSetKeyValueA Function -

    LSTATUS RegSetKeyValueA(
        HKEY    hKey,
        LPCSTR  lpSubKey,
        LPCSTR  lpValueName,
        DWORD   dwType,
        LPCVOID lpData,
        DWORD   cbData
    );
*/

int main(int argc, char *argv[])
{
    if(argc == 3)
    {
        LPCSTR lpSubKey = argv[1];
        HKEY hKey;
        long lstatus = RegCreateKeyExA(
            HKEY_LOCAL_MACHINE,
            lpSubKey,
            0,
            NULL,
            REG_OPTION_VOLATILE,
            KEY_ALL_ACCESS | KEY_WOW64_64KEY,
            NULL,
            &hKey,
            NULL
        );

        if(lstatus != ERROR_SUCCESS)
        {
            std::cout << "Creation failed and exited with error code: " << GetLastError() << std::endl;
        }
        else
        {
            std::cout << "Registry key created" << std::endl;
        }

        LPCSTR lpValueName = argv[2];
        DWORD dwData = 1234;

        lstatus = RegSetKeyValueA(
            hKey,
            NULL,
            lpValueName,
            REG_DWORD,
            (LPBYTE)&dwData,
            sizeof(dwData)
        );

        if(lstatus != ERROR_SUCCESS)
        {
            std::cout << "Setting failed and exited with error code: " << GetLastError() << std::endl;
        }
        else
        {
            std::cout << "Registry key is set" << std::endl;
        }

        RegCloseKey(hKey);
    }
    return 0;
}