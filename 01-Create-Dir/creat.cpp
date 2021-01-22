// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createdirectorya

#include <Windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {

        LPCSTR lstr = argv[1]; // To convert char* to LPCSTR
        if(CreateDirectoryA(lstr, NULL))
        {
            cout << "Directory: " << argv[1] << " created" << endl;
        }
        else
        {
            if(GetLastError() == ERROR_ALREADY_EXISTS)
            {
                cout << "The directory: " << argv[1] << " already exists" << endl;
            }
            else if(GetLastError() == ERROR_PATH_NOT_FOUND)
            {
                cout << "Path: " << argv[1] << " not found" << endl;
            }
            else
            {
                cout << "Creating directory: " << argv[1] << " failed" << endl;
            }
        }
    }
    else
    {
        cout << "Usage: creat <path/file_name>";
    }

    return 0;
}