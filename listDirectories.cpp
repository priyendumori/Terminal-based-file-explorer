#include "header.h"
#include "macro.h"

extern vector<string> filelist;
extern string currentPath,home;
extern ofstream myfile;

int listContent(string name){

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);


    filelist.clear();
    cls;
    pos(0,0);
    string s=name;
    if(s.compare(".") != 0) currentPath=name;

    //printf("\033[3J\033[1;1H");
    //cls1;
    DIR *dir;
    struct dirent *ent;
    const char *dirname=name.c_str();
    if ((dir = opendir (dirname)) != NULL) {
        /* print all the files and directories within directory */

        while ((ent = readdir (dir)) != NULL) {
            displayContent(ent->d_name);
        }
        printf("\n");
        closedir (dir);
        pos(w.ws_row,0);
        cout<<"Normal mode";
        //scroll(0,w.ws_row);
        pos(0,0);
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

    string dirname(dname);
    if(dirname.compare("..")==0 && currentPath==home)
        return;

    stat(dname, &sb);

    string permissions;
    switch (sb.st_mode & S_IFMT) {
        case S_IFDIR:  permissions.append("d");    break;
        case S_IFREG:  permissions.append("-");    break;
        default:       permissions.append("-");    break;
    }

    if (sb.st_mode & S_IRUSR)   permissions.append("r");
    else permissions.append("-");
    if (sb.st_mode & S_IWUSR)  permissions.append("w");
    else permissions.append("-");
    if (sb.st_mode & S_IXUSR)  permissions.append("x");
    else permissions.append("-");

    if (sb.st_mode & S_IRGRP)   permissions.append("r");
    else permissions.append("-");
    if (sb.st_mode & S_IWGRP)  permissions.append("w");
    else permissions.append("-");
    if (sb.st_mode & S_IXGRP)  permissions.append("x");
    else permissions.append("-");

    if (sb.st_mode & S_IROTH)   permissions.append("r");
    else permissions.append("-");
    if (sb.st_mode & S_IWOTH)  permissions.append("w");
    else permissions.append("-");
    if (sb.st_mode & S_IXOTH)  permissions.append("x");
    else permissions.append("-");


    cout<<permissions<<"\t";

    struct passwd *pws;
    pws = getpwuid(sb.st_uid);
    char *username=pws->pw_name;
    struct group *g;
    g = getgrgid(sb.st_gid);
    char *groupname=g->gr_name;

    printf("%s : %s \t", username , groupname );

    long long size=sb.st_size;
    char unit='B';
    if(size>1024){
        size/=1024;
        unit='K';
    }
    if(size>1024){
        size/=1024;
        unit='M';
    }
    cout<<size<<" "<<unit<<"\t";

    string time = ctime(&sb.st_mtime);
    string trimtime = time.substr(0, time.size()-1);
    cout<< trimtime <<"\t";
    printf ("%s \n", dname);

    string path=getPath(dname);
    filelist.push_back(path);

}

string getPath(string name){

    string path=currentPath;
    path.append("/");
    path.append(name);
    return path;
}

string getpwd(){
    char buff[FILENAME_MAX];
    getcwd( buff, FILENAME_MAX );
    string pwd(buff);
    return pwd;
}
