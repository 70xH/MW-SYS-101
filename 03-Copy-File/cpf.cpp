// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfile

#include <Windows.h>
#include <iostream>
#include <cstring>

using namespace std;

/*
Function to copy a file

    BOOL CopyFile(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName,
    BOOL    bFailIfExists
    );
*/

void help()
{
    cout << "Usage: cpf [options] <old-file> <new-file>" << endl;
    cout << "Options:" << endl;
    cout << "-o - Overwrite the file" << endl;
}

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        LPCSTR oldFile = argv[1];
        LPCSTR newFile = argv[2];
        if(CopyFile(oldFile, newFile, TRUE)) // TRUE is to mention - if to disallow overwriting the existing files
        {
            cout << "Copied \"" << argv[1] << "\" to \"" << argv[2] << "\"." << endl;
        }
        else
        {
            cout << "Copying failed with error code: " << GetLastError() << endl;
        }
    }
    else if(argc == 4)
    {
        if(strcmp(argv[1], "-o") == 0)
        {
            LPCSTR oldFile = argv[2];
            LPCSTR newFile = argv[3];
            if(CopyFile(oldFile, newFile, FALSE)) // FALSE is to mention - if to allow overwriting the existing files
            {
                cout << "Copied \"" << argv[2] << "\" to \"" << argv[3] << "\"." << endl;
            }
            else
            {
                cout << "Copying failed with error code: " << GetLastError() << endl;
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