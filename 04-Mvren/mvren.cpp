// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefile

#include <cstdlib>
#include <iostream>
#include "Windows.h"

using namespace std;

/* 
MoveFile Function

    BOOL MoveFile(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName
    );
*/

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        LPCSTR oldFile = argv[1];
        LPCSTR newFile = argv[2];
        if(MoveFile(oldFile, newFile))
        {
            cout << "Moved the file \"" << oldFile << "\" to \"" << newFile << "\"" << endl;
        }
        else
        {
            cout << "Moving the file failed with error code: " << GetLastError() << endl;
        }
    }
    else
    {
        cout << "Usage: mvr <file/dir_name> <file/dir_name>" << endl;
    }

    return 0;
}