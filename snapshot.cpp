#include "header.h"
#include "macro.h"
ofstream dump;
queue<string> q;
extern string currentPath,home;

void snapshotHelper(string path){
    string fullpath;

    DIR *dir;
    struct stat stat_dir, stat_entry;
    struct dirent *entry;

    stat(path.c_str(), &stat_dir);

    if (S_ISDIR(stat_dir.st_mode) != 0) {
        dump<<endl<<path<<": "<<endl;
        //exit(-1);
    }

    if ((dir = opendir(path.c_str())) == NULL) {
        fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
        //exit(-1);
    }


    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        dump<<"\t"<<(entry->d_name)<<"\t";
        fullpath=path;
        fullpath.append("/").append(entry->d_name);

        stat(fullpath.c_str(), &stat_entry);

    }
    dump<<endl;
    closedir(dir);

    if ((dir = opendir(path.c_str())) == NULL) {
        fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
        //exit(-1);
    }

    while ((entry = readdir(dir)) != NULL) {
        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        fullpath=path;
        fullpath.append("/").append(entry->d_name);

        // stat for the entry
        stat(fullpath.c_str(), &stat_entry);

        if (S_ISDIR(stat_entry.st_mode) != 0) {
            snapshotHelper(fullpath);
        }

    }
    closedir(dir);
}

void getSnapshot(string dir, string dumpfile){

    dump.open(dumpfile+".txt");

    string fullpath=home;
    if(dir.compare(".")==0){
        fullpath=currentPath;
    }else if(dir[0]=='~'){
        fullpath.append(dir.substr(1,dir.length()-1));
    }
    else if(dir[0]=='/'){
        fullpath.append(dir);
    }
    else{
        fullpath=currentPath;
        fullpath.append("/"+dir);
    }

    snapshotHelper(fullpath);
}
