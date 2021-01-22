// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createsymboliclinka

#include <cstdlib>
#include <iostream>
#include "Windows.h"

using namespace std;

/*
CreateSoftLink Function - Needs to higher privilege

    BOOL WINAPI CreateSymbolicLink(
        LPCSTR symLinkFile,
        LPCSTR targetFile,
        DWORD dwFlags               // 0 - file, SYMBOLIC_LINK_FLAG_DIRECTORY, SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE - for not evaluated stuff
    );
*/

void help()
{
    cout << "Usage: ln -s <target_file> <old_file>" << endl;
}

int main(int argc, char* argv[])
{
    if ( argc == 4 )
    {
        if ( strncmp (argv[1], "-s", sizeof("-s")) == 0 )
        {
            LPCSTR targetFile = argv[2];
            LPCSTR olFile = argv[3];

            bool symLink = CreateSymbolicLink(
                targetFile,
                olFile,
                0
            );

            if ( symLink )
            {
                cout << "Symbolic link of \"" << olFile << "\" is created as \"" << targetFile << "\"." << endl;
            }

            else
            {
                cout << "Failed to create a symbolic link and exited with error code: " << GetLastError() << endl;
            }
        }
        
        else
        {
            help();
        }
        
    }

    else
    {
        help();
    }

    return 0;
}