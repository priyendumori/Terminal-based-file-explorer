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
    //myfile<<"starting with path: "<<path<<endl;
    DIR *dir;
    struct stat stat_dir, stat_entry;
    struct dirent *entry;

    stat(path.c_str(), &stat_dir);
    //myfile<<"strting to read entries of "<<path<<endl;


    // if path does not exists or is not dir - exit with status -1
    if (S_ISDIR(stat_dir.st_mode) == 0) {
        //fprintf(stderr, "%s: %s\n", "Is not directory", path);
        //exit(-1);

    }

    // if not possible to read the directory for this user
    if ((dir = opendir(path.c_str())) == NULL) {
        //fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
        //exit(-1);
        commands(true);
    }


    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        // determinate a full path of an entry
        //fullpath=createPath(path,entry->d_name);
        fullpath=path;
        fullpath.append("/").append(entry->d_name);
        //myfile<<"fullpath for entry: "<<fullpath<<endl;

        // stat for the entry
        stat(fullpath.c_str(), &stat_entry);

        // recursively remove a nested directory
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            //myfile<<"calling recursive for: "<<fullpath<<endl;
            deleteHelper(fullpath);
            continue;
        }

        //myfile<<"removing the file: "<<fullpath<<endl;
        // remove a file object
        if (unlink(fullpath.c_str()) != 0) commands(true);/*
            myfile<<"Removed a file: "<<fullpath<<endl;
        else
            myfile<<"Can`t remove a file: "<<fullpath<<endl;*/
    }

    //myfile<<"removing the directory: "<<path<<endl;
    // remove the devastated directory and close the object of it
    if (rmdir(path.c_str()) != 0) commands(true);/*
        myfile<<"Removed a directory: "<<path<<endl;
    else
        myfile<<"Can`t remove a directory: "<<path<<endl;*/

    closedir(dir);
}

/*
    this function deletes directory recursively
    using deleteHelper
*/
void deleteDirectory(string path){

    /*if(path.compare(".") || path.compare("~") || path.compare("/"))
        path=createPath(path, dirname);
    else path=path.append("/"+dirname);*/
    //myfile<<"calling helper with "<<path<<endl;
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
