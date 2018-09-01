/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
extern ofstream myfile;

/*
    this function changes name of file or directory
*/
void changeName(string oldname, string newname){
    string old=getWholePath(oldname);
    string newn=getWholePath(newname);
    if(rename(old.c_str(), newn.c_str()) != 0) commands(true);
}
