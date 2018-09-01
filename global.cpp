/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

/*
    this file stores all the global variables
*/
#include "header.h"
#include "macro.h"

vector<string> filelist;
string home;
string currentPath;
stack<string> pathstack,backstack,frontstack;
struct winsize w;

ofstream myfile;
