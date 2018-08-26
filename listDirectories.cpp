#include "header.h"
#include "macro.h"

extern vector<string> filelist;
extern string currentPath;
extern ofstream myfile;

int listContent(string name){
    myfile<<"for file "<<name<<endl;
    for(auto i:filelist){
        myfile<<i<<endl;
    }
    myfile<<"clearing filelist "<<endl;
    filelist.clear();
    myfile<<"after clearing "<<endl;
    for(auto i:filelist){
        myfile<<i<<endl;
    }
    myfile<<"Screen cleared "<<endl;
    cls;
    myfile<<"pos set to 0 "<<endl;
    pos(0,0);

    //cout<<name<<"*********************"<<endl;
    string s=name;
    if(s.compare(".") != 0) currentPath=name;
    //cout<<name<<endl;
    //printf("\033[3J\033[1;1H");
    //cls1;
    DIR *dir;
    struct dirent *ent;
    const char *dirname=name.c_str();
    if ((dir = opendir (dirname)) != NULL) {
        /* print all the files and directories within directory */

        while ((ent = readdir (dir)) != NULL) {
                myfile<<"going to display content for "<<(ent->d_name)<<endl;
                displayContent(ent->d_name);
        }
        printf("\n");
        /*cout<<currentPath<<endl;
*/

        //for(int i=0;i<5;i++){ cout<<filelist[i].first<<" "<<filelist[i].second<<endl;        }
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
    //myfile<<"inside display content for "<<dname<<endl;
    struct stat sb;

    stat(dname, &sb);
    //myfile<<"printing uid gid "<<endl;
    printf("%ld : %ld \t", (long) sb.st_uid, (long) sb.st_gid);
    //myfile<<"printing size "<<endl;
    printf("%lld bytes \t", (long long) sb.st_size);
    //myfile<<"printing permission "<<endl;
    printf("%lo \t", (unsigned long) sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    //myfile<<"printing time "<<endl;
    string time = ctime(&sb.st_mtime);
    string trimtime = time.substr(0, time.size()-1);
    cout<< trimtime <<"\t";
    //myfile<<"printing name "<<endl;
    printf ("%s \n", dname);

    //myfile<<"setting type "<<endl;
    char type='f';
    if(S_ISDIR(sb.st_mode)){
        //cout<<dname<<" is directory"<<endl;
        type='d';
    }else{
        //cout<<dname<<" is not directory"<<endl;
    }
    //myfile<<" getting path "<<endl;
    string path=getPath(dname);
    //cout<<dname<<endl<<path<<endl;
    myfile<<"pushing "<<type<<" "<<path<<endl;
    filelist.push_back(path);

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
