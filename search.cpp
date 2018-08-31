#include "header.h"
#include "macro.h"
vector<string> results, printresults;
extern string home;
void search(string path, string pattern){
    string fullpath;
    DIR *dir;
    struct stat stat_dir, stat_entry;
    struct dirent *entry;

    stat(path.c_str(), &stat_dir);


    // if path does not exists or is not dir - exit with status -1
    if (S_ISDIR(stat_dir.st_mode) == 0) {
        fprintf(stderr, "%s: %s\n", "Is not directory", path);
        //exit(-1);
    }

    // if not possible to read the directory for this user
    if ((dir = opendir(path.c_str())) == NULL) {
        fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
        //exit(-1);
    }


    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;


        // determinate a full path of an entry
        //fullpath=createPath(path,entry->d_name);
        fullpath=path;
        fullpath.append("/").append(entry->d_name);
        if(entry->d_name == pattern){
            results.push_back(fullpath);
            string temp=fullpath;
            temp.replace( temp.find( home ), home.size(), "" );
            printresults.push_back(temp);
        }

        // stat for the entry
        stat(fullpath.c_str(), &stat_entry);

        // recursively remove a nested directory
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            search(fullpath, pattern);
            continue;
        }
    }

    closedir(dir);
}

void displaySearchResults(){
    for(auto i:printresults){
        cout<<i<<endl;
    }
}
