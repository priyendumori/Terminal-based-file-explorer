/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
extern ofstream myfile;


/*
    this function creates a file with
    given filename at location path
*/
void createFile(string filename, string path){
    string fullpath=createPath(path, filename);
    int fd=open(fullpath.c_str(), O_WRONLY | O_CREAT, 0644);
    if(fd==-1) commands(true);
}


/*
    this function creates a directory
    with name dirname at location path
*/
void createDirectory(string dirname, string path){
    string fullpath=createPath(path, dirname);
    if(mkdir(fullpath.c_str(),0775)!=0) commands(true);
}
