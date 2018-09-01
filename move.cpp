/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"

/*
    this function moves files and directories
    using copy and delete commands implementation
*/
void moveContent(vector<string> arguments){

    copyContent(arguments);

    string destination=arguments[arguments.size()-1];
    arguments.erase(arguments.begin()+0);
    arguments.erase(arguments.begin()+arguments.size()-1);

    destination=getWholePath(destination);

    for(int i=0;i<arguments.size();i++){
        string path=getWholePath(arguments[i]);
        struct stat stat_dir, stat_entry;
        stat(path.c_str(), &stat_dir);
        if (S_ISDIR(stat_dir.st_mode) == 0) {
            remove(path.c_str());
        }
        else{
            deleteHelper(path);
        }
    }
}
