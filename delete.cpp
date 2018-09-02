/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
extern ofstream myfile;


/*
    this is a helper function that deletes
    files and directories recursively
*/
void deleteHelper(string path){
    string fullpath;
    DIR *dir;
    struct stat stat_dir, stat_entry;
    struct dirent *entry;

    stat(path.c_str(), &stat_dir);
    if ((dir = opendir(path.c_str())) == NULL) {
        commands(true);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        fullpath=path;
        fullpath.append("/").append(entry->d_name);
        stat(fullpath.c_str(), &stat_entry);

        if (S_ISDIR(stat_entry.st_mode) != 0) {
            deleteHelper(fullpath);
            continue;
        }
        if (unlink(fullpath.c_str()) != 0) commands(true);
    }
    if (rmdir(path.c_str()) != 0) commands(true);
    closedir(dir);
}


/*
    this function deletes directory recursively
    using deleteHelper
*/
void deleteDirectory(string path){
    string fullpath=getWholePath(path);
    deleteHelper(fullpath);
}


/*
    this function deletes a file
*/
void deleteFile(string filename){
    string fullpath=getWholePath(filename);
    if (unlink(fullpath.c_str()) != 0) commands(true);
}
