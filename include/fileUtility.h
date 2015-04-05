/* 
 * File:   fileUtility.h
 * Author: collinm
 *
 * Created on 5 avril 2015, 12:44
 */

#ifndef FILEUTILITY_H
#define	FILEUTILITY_H
#include "ff.h"
#include <string>
#include <map>

using namespace std;

class FileUtility {
public:
    FileUtility(const char *fileName, BYTE mode);
    map<std::string, string> readAllFile();
    void writeAllProperties(map <string, string> fileMapConfig);
    virtual ~FileUtility();
private:
    FIL f;
};

#endif	/* FILEUTILITY_H */

