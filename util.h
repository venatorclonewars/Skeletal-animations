#pragma once
#include <string>   
#include <fstream> 

using namespace std;

bool readFile(const char* pFileName, string& outFile)
{
    ifstream f(pFileName);

    bool ret = false;

    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        ret = true;
    }
    else
    {
        fprintf(stderr, "FileError: Can't find file %s\n", pFileName);
    }

    return ret;
}