// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile

#include <cstdlib>
#include <iostream>
#include "Windows.h"

using namespace std;

/*
ReadFile Fuction

    BOOL WINAPI ReadFile(
        HANDLE handler,
        LPVOID buffer,
        DWORD nNumberOfBytesToRead,
        LPDWORD lpNumberOfBytesRead,
        LPOVERLAPPED lpOverlapped
    );
*/

int main(int argc, char* argv[])
{
    if ( argc == 2 )
    {
        HANDLE handler;
        LPCSTR filePathName = argv[1];

        handler = CreateFile(
            filePathName,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if ( handler == INVALID_HANDLE_VALUE )
        {
            cout << "Failed to open the file and exited with error code: " << GetLastError() << endl;
            return -1;
        }

        cout << "Access the file \"" << filePathName << "\"" << endl;

        char buffer[256];
        DWORD numberOfBytes = sizeof(buffer);

        bool readFile = ReadFile(
            handler,
            buffer,
            numberOfBytes,
            NULL,
            NULL
        );

        if ( readFile )
        {
            cout << buffer << endl;
        }

        else
        {
            cout << "Failed to read the file and exited with error code: " << GetLastError() << endl;
        }

        CloseHandle(
            handler
        );
    }

    else
    {
        cout << "Usage: rdf <file_name>" << endl;
    }

    return 0;
}