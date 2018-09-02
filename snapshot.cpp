/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
ofstream dump;
extern string currentPath,home;
extern ofstream myfile;
extern struct winsize w;


/*
    this is a helper function for taking snapshot from a
    directory in DFS manner and store it in a dumpfile
*/
void snapshotHelper(string path){
    string fullpath;
    DIR *dir;
    struct stat stat_dir, stat_entry;
    struct dirent *entry;

    stat(path.c_str(), &stat_dir);
    if (S_ISDIR(stat_dir.st_mode) != 0) {
        dump<<endl<<path<<": "<<endl;
    }

    if ((dir = opendir(path.c_str())) == NULL) {
        commands(true);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        dump<<"\t"<<(entry->d_name)<<"\t";
    }
    dump<<endl;
    closedir(dir);

    if ((dir = opendir(path.c_str())) == NULL) {
        commands(true);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        fullpath=path;
        fullpath.append("/").append(entry->d_name);

        stat(fullpath.c_str(), &stat_entry);
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            snapshotHelper(fullpath);
        }
    }
    closedir(dir);
}


/*
    this function dumps DFS snapshot of a
    directory(dir) to file(dumpfile)
*/
void getSnapshot(string dir, string dumpfile){
    dump.open(dumpfile+".txt");
    string fullpath=getWholePath(dir);
    snapshotHelper(fullpath);
    dump.close();
}
