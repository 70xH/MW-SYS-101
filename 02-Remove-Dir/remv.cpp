// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-removedirectorya

#include <Windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        LPCSTR lpcstr = argv[1]; // Conver the char* to LPCSTR
        if(RemoveDirectoryA(lpcstr))
        {
            cout << "Succesful removal of the directory: " << argv[1] << endl;
        }
        else
        {
            if(GetLastError() == ERROR_FILE_NOT_FOUND)
            {
                cout << "Directory \"" << argv[1] << "\" not found" << endl;
            }
            else
            {
                cout << "Deleting the directory \"" << argv[1] << "\" failed with error code: " << GetLastError() << endl;
            }
        }
    }
    else
    {
        cout << "Usage: remvdir <path/dir_name>" << endl;
    }

    return 0;
}