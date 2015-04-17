/* 
 * File:   fileUtility.cpp
 * Author: collinm
 * 
 * Created on 5 avril 2015, 12:44
 */

#include "fileUtility.h"
#include "ff.h"

#include <string>
#include <diag/Trace.h>
#include <map>

using namespace std;

FileUtility::FileUtility(const char *fileName) {
    this->fileName=fileName;
}

void FileUtility::fileOpen(BYTE mode) {
    FRESULT fres;
    fres = f_open(&f, fileName, mode);
    if (fres) {
        trace_printf("error, file don't exist");
    }
}

map<std::string, string> FileUtility::readAllFile() {
    
    fileOpen(FA_READ);
    
    char line[80];

    map <string, string> fileMapConfig;

    while (f_gets(line, sizeof line, &f)) {

        string s, key, value;

        s = string(line);

        string::size_type begin = s.find_first_not_of(" \f\t\v");

        string::size_type end = s.find('=', begin);
        key = s.substr(begin, end - begin);

        // (No leading or trailing whitespace allowed)
        key.erase(key.find_last_not_of(" \f\t\v") + 1);

        // No blank keys allowed
        if (key.empty()) continue;

        // Extract the value (no leading or trailing whitespace allowed)
        begin = s.find_first_not_of(" \f\n\r\t\v", end + 1);
        end = s.find_last_not_of(" \f\n\r\t\v") + 1;

        value = s.substr(begin, end - begin);

        fileMapConfig[key] = value;

        trace_printf("Line: %s - %s \n", key.c_str(), value.c_str());
    }

    f_close(&f);

    return fileMapConfig;
}

void FileUtility::writeAllProperties(map <string, string> fileMapConfig) {

    fileOpen(FA_WRITE);
    
    for (auto it = fileMapConfig.begin(); it != fileMapConfig.end(); ++it) {
        string line = it->first + "=" + it->second;
        f_puts(line.c_str(), &f);
    }

     f_close(&f);

}

FileUtility::~FileUtility() {
}

