#include "header.h"
#include "macro.h"
extern ofstream myfile;

void createFile(string filename, string path){
    string fullpath=createPath(path, filename);
    int fd=open(fullpath.c_str(), O_WRONLY | O_CREAT, 0644);

}

void createDirectory(string dirname, string path){
    //if(path.compare(".")==0) path=currentPath;
    string fullpath=createPath(path, dirname);
    //myfile<<fullpath<<endl;
    mkdir(fullpath.c_str(),0775);
}
