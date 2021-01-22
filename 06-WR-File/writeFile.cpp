// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile

#include <cstdlib>
#include <iostream>
#include <string>
#include "Windows.h"

using namespace std;

/*
WriteFile Function

    BOOL WriteFile(
        HANDLE hFile,                       handle that is opened
        LPCVOID lpBuffer,                   the data that shoule be written
        DWORD nNumberOfBytesToWrite,        number of bytes to write
        LPDWORD lpNumberOfBytesWritten,     number of bytes that has been written
        LPOVERLAPPED lpOverlapped           requrid only if hFile is opened as Overlapped - default NULL
    )
*/

int main ( int argc, char* argv[] )
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
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );


        if ( handler == INVALID_HANDLE_VALUE )
        {
            cout << "Creating the file failed and exited with error code: " << GetLastError() << endl;
            return -1;
        }

        cout << "File \"" << filePathName << "\" created.\n" << "Enter Something" << endl;

        char buffer[256];
        DWORD numberOfBytes;
        LPDWORD numberOfBytesWritten = 0;

        fgets( buffer, sizeof(buffer), stdin );
        numberOfBytes = strlen(buffer);


        bool writeToFile = WriteFile(
            handler,
            buffer,
            numberOfBytes,
            numberOfBytesWritten,
            NULL
        );

        if ( writeToFile )
        {
            cout << "\nWritten to the file" << endl;
        }

        else
        {
            cout << "Failed to write to the file and exited with error code: " << GetLastError() << endl;
        }

        CloseHandle(
            handler
        );
    }

    else if ( argc == 3 )
    {
        HANDLE handler;
        LPCSTR filePathName = argv[2];

        if ( strncmp( argv[1], "-e", sizeof("-e") ) == 0 )
        {
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
                cout << "Opening the file failed and exited with error code: " << GetLastError() << endl;
                return -1;
            }

            cout << "Accessing the existing file \"" << filePathName << "\".\nEnter Something:" << endl;

            char buffer[256];
            DWORD numberOfBytes;

            fgets( buffer, sizeof(buffer), stdin );
            numberOfBytes = strlen(buffer);

            bool writeToFile = WriteFile(
                handler,
                buffer,
                numberOfBytes,
                NULL,
                NULL
            );

            if ( writeToFile )
            {
                cout << "Written to the file" << endl;
            }

            else
            {
                cout << "Failed to write to the file and exited with error code: " << GetLastError() << endl;
            }

            CloseHandle(
                handler
            );

        }
    }

    else
    {
        cout << "Usage: wire [-e] <file_name>" << endl;
    }
}