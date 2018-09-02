/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
extern ofstream myfile;


/*
    this function copies file
*/
void copy(string from, string to){
    int fd_from, fd_to;
    char buffer[1024];
    long long size;

    if(((fd_from = open(from.c_str(), O_RDONLY)) == -1) ||
     ((fd_to=open(to.c_str(),O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1)){
        commands(true);
    }

    while((size=read(fd_from, buffer, 1024)) > 0){
        if(write(fd_to, buffer, size) != size){
            commands(true);
        }
    }

    struct stat sb;
    stat(from.c_str(), &sb);
    chown(to.c_str(), sb.st_uid, sb.st_gid);
    chmod(to.c_str(), sb.st_mode);

    close(fd_from);
    close(fd_to);
}


/*
    this function copies directories recursivey
*/
void copyDirectory(string from, string to){
    DIR *DIR;
    struct dirent *entry;
    struct stat stat_dir, stat_entry;
    string frompath,topath;

    stat(from.c_str(), &stat_dir);
    if(S_ISDIR(stat_dir.st_mode) == 0){
        return;
    }

    if( DIR = opendir(from.c_str()) ){
        while(entry = readdir(DIR)){
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
                continue;

            frompath=from;
            frompath.append("/").append(entry->d_name);

            struct stat buf;
            stat(frompath.c_str(), &buf);
            if(S_ISDIR(buf.st_mode)!=0){
                topath=to;
                topath.append("/").append(entry->d_name);
                myfile<<"making directory: "<<topath<<endl;
                mkdir(topath.c_str(),0755);
                copyDirectory(frompath, topath);
            }
            else{
                topath=to;
                topath.append("/").append(entry->d_name);
                myfile<<"copying from "<<frompath<<" to "<<topath<<endl;
                copy(frompath, topath);
            }
        }
        closedir(DIR);
    }
}


/*
    this function is a driver function to get arguments,
    generate paths and call functions appropriately
*/
void copyContent(vector<string> arguments){
    string destination=arguments[arguments.size()-1];
    arguments.erase(arguments.begin()+0);
    arguments.erase(arguments.begin()+arguments.size()-1);

    destination=getWholePath(destination);
    for(int i=0;i<arguments.size();i++){
        string path=getWholePath(arguments[i]);
        struct stat buf;
        stat(path.c_str(), &buf);
        if(S_ISDIR(buf.st_mode)==0){
            string tofile=destination+"/"+arguments[i];
            copy(path, tofile);
        }
        else{
            copyDirectory(path,destination);
        }
    }

}
