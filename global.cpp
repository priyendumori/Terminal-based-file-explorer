#include "header.h"
#include "macro.h"

vector<string> filelist;
string home;
string currentPath;
stack<string> pathstack,backstack,frontstack;

ofstream myfile;
