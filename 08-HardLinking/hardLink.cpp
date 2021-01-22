// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createhardlinka

#include <cstdlib>
#include <iostream>
#include "Windows.h"

using namespace std;

/*
HardLink Function

    BOOL WINAPI CreateHardLink(
        LPCSTR newFile,
        LPCSTR oldFile,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
*/

int main ( int argc, char* argv[] )
{
    if ( argc == 3 )
    {
        LPCSTR newFile = argv[1];
        LPCSTR oldFile = argv[2];

        bool hardLink = CreateHardLink(
            newFile,
            oldFile,
            NULL
        );

        if ( hardLink )
        {
            cout << "Hard Link of \"" << oldFile << "\" and \"" << newFile << "\" has been created" << endl;
        }

        else
        {
            cout << "Failed to hardlink the files and exited with error code: " << GetLastError() << endl;
        }
    }

    else
    {
        cout << "Usage: ln <new_file> <old_file>" << endl;
    }

    return 0;
}