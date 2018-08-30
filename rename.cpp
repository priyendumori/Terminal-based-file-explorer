#include "header.h"
#include "macro.h"
extern ofstream myfile;

void changeName(string oldname, string newname){
    rename(oldname.c_str(), newname.c_str());
}
