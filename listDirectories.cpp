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

    string path=getPath(dname);
    stat(path.c_str(), &sb);

    myfile<<"file "<<path<<endl;

    printf((S_ISDIR(sb.st_mode))  ? "d" : "-");
    printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    printf((sb.st_mode & S_IRGRP) ? "r" : "-");
    printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    printf((sb.st_mode & S_IROTH) ? "r" : "-");
    printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    printf((sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t");

    struct passwd *pwd = getpwuid(sb.st_uid);
    struct group  *grp = getgrgid(sb.st_gid);
    const char *username=pwd->pw_name;
    const char *groupname=grp->gr_name;
    printf("%s %s \t", username, groupname);

    long long size=sb.st_size;
    char unit='B';
    if(size>1024){
        size/=1024;
        unit='K';
    }
    if(size>1024){
        size/=1024;
        unit='M';
    }if(size>1024){
        size/=1024;
        unit='G';
    }
    printf("%lld %c \t", size, unit);

    string time = ctime(&sb.st_mtime);
    string trimtime = time.substr(0, time.size()-1);
    cout<< trimtime <<"\t";
    printf ("%s \n", dname);


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
