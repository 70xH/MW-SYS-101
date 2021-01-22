// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea

#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include "Windows.h"

using namespace std;

/*
CreateFile Function

    HANDLE WINAPI CreateFile(
        LPCSTR lpfilename,                              path and the file name
        DWORD dwDesiredAccess,                          creating the file in a specific mode - GENERIC_READ, GENERIC_WRITE, GENERIC_READ | GENERIC_WRITE
        DWORD dwShareMode,                              specific value according - permissions for file sharing
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,     using NULL will go with default values
        DWORD dwCreationDispostion,                     what action to take if the file exist - default OPEN_EXISTING
        DWORD dwFlagsAndAttributes,                     flags or attributes for the file - default FILE_ATTRIBUTE_NORMAL
        HANDLE hTemplateFile
    );
*/

/*
CloseHandle Function

    BOOL WINAPI CloseHandle(
        HANDLE hObject;
        );
*/

void help()
{
    cout << "Usage: touch [OPTIONS] <file_name>\n" << endl;
    cout << "Options: \n" << endl;
    cout << "default          -   Creates a file with default attributes" << endl;
    cout << "-h               -   Shows this again" << endl;
    cout << "-r <file_name>   -   Creates a read-only file" << endl;
    cout << "-w <file_name>   -   Creates a write-only file" << endl;
}

int main( int argc, char** argv )
{
    int option;

    if ( argc >= 2 )
    {
        int readAccess           = 0;
        int writeAccess          = 0;
        int noShareAccess        = 0;
        int deleteShareAccess    = 0;
        int peekShareAccess      = 0;
        int writeShareAccess     = 0;
        HANDLE handler;
        LPCSTR filePathName;
        while( (option = getopt(argc, argv, "hrwndps")) != -1 )
        {
            filePathName = argv[argc-1];
            switch ( option )
            {
                case 'h':
                    help();
                    break;
                case 'r':
                    readAccess = 1;
                    break;
                case 'w':
                    writeAccess = 1;
                    break;
                case 'n':
                    noShareAccess = 1;
                    break
                case 'd':
                    deleteShareAccess = 1;
                    break
                case 'p':
                    peekShareAccess = 1;
                    break
                case 's':
                    writeShareAccess = 1;
                    break
                default:
                    handler = CreateFile(
                        filePathName,
                        GENERIC_READ,
                        FILE_SHARE_WRITE,
                        NULL,
                        CREATE_NEW,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                    );
                    break;
            }
        }

        if ( (readAccess == 1) && (writeAccess == 0) )
        {
            handler = CreateFile(
                filePathName,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
        }
        else if ( (readAccess == 0) && (writeAccess == 1) )
        {
            handler = CreateFile(
                filePathName,
                GENERIC_WRITE,
                FILE_SHARE_WRITE,
                NULL,
                CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
        }
        else if ( (readAccess == 1) && (writeAccess == 1) )
        {
            handler = CreateFile(
                filePathName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE,
                NULL,
                CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
        }

        if (handler == INVALID_HANDLE_VALUE)
        {
            cout << "Failed to create the file. Exits with error code: " << GetLastError() << endl;
            return 1;
        }

        cout << "The file \"" << filePathName <<"\" is created." << endl;
        CloseHandle(
            handler
        );
    }
    else
    {
        help();
    }
}