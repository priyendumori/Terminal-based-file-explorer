/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
vector<string> results, printresults;
extern string home;
extern struct winsize w;

/*
    this function searches for a file or directory from current directory
    recursively in a DFS manner and stores it
*/
void search(string path, string pattern){
    string fullpath;
    DIR *dir;
    struct stat stat_dir, stat_entry;
    struct dirent *entry;

    stat(path.c_str(), &stat_dir);
    if (S_ISDIR(stat_dir.st_mode) == 0) {
        commands(true);
    }

    if ((dir = opendir(path.c_str())) == NULL) {
        commands(true);
    }
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        fullpath=path;
        fullpath.append("/").append(entry->d_name);
        if(entry->d_name == pattern){
            results.push_back(fullpath);
            string temp=fullpath;
            temp.replace( temp.find( home ), home.size(), "" );
            printresults.push_back(temp);
        }

        stat(fullpath.c_str(), &stat_entry);
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            search(fullpath, pattern);
            continue;
        }
    }
    closedir(dir);
}

/*
    this function displays the results of the search
*/
void displaySearchResults(){
    for(auto i:printresults){
        cout<<i<<endl;
    }
    pos(w.ws_row,0);
    cout<<"Normal mode";
    pos(0,0);
}
