#include "header.h"
#include "macro.h"

extern vector<pair<char,string>> list;
extern string currentPath;

int listContent(const char* name){

    cls;
    pos(0,0);
    //cout<<name<<"*********************"<<endl;

    //printf("\033[3J\033[1;1H");
    //cls1;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (name)) != NULL) {
        /* print all the files and directories within directory */
        list.clear();
        while ((ent = readdir (dir)) != NULL) {

                displayContent(ent->d_name);
        }
        printf("\n");
        /*cout<<currentPath<<endl;
*/
        for(int i=0;i<2;i++){ cout<<list[i].second<<endl;        }
        closedir (dir);
    }
    else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    return 1;
}

void displayContent(const char *dname){

    struct stat sb;

    stat(dname, &sb);

    printf ("%s ", dname);

    printf("%ld : %ld ", (long) sb.st_uid, (long) sb.st_gid);

    printf("%lld bytes ", (long long) sb.st_size);

    printf("%lo ", (unsigned long) sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    printf("%s", ctime(&sb.st_mtime));

    char type='f';
    if(S_ISDIR(sb.st_mode)){
        type='d';
    }

    string path=getPath(dname);
    //cout<<dname<<endl<<path<<endl;
    list.push_back(make_pair(type, path));

}

string getPath(string name){

    string path=currentPath;
    path.append("/");
    path.append(name);
    //cout<<"appended "<<name<<" to "<<path<<endl;
    return path;
}

string getpwd(){
    char buff[FILENAME_MAX];
    getcwd( buff, FILENAME_MAX );
    string pwd(buff);
    return pwd;
}
