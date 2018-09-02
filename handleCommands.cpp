/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"

int lineno=0;
extern vector<string> filelist, results;
extern stack<string> backstack,frontstack;
extern string currentPath;
extern ofstream myfile;
extern string home;
extern struct winsize w;


/*
    this function handles all the key functions like
    arrow, backspace, h, etc, maintains the cursor
    position and opens file or directory on pressing
    enter appropriately
*/
void handleCommands(bool isSearchResult){

    struct termios initialrsettings, newrsettings;
    char ch;

    tcgetattr(fileno(stdin), &initialrsettings);
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ICANON;
    newrsettings.c_lflag &= ~ECHO;

    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
        fprintf(stderr,"Could not set attributes\n");
    }
    else {
        while(ch=cin.get()){
            if(ch==27){
            	ch=cin.get();
            	ch=cin.get();
            	if(ch=='A'){
                    if(lineno>0){
                        lineno--;
                        up;
                    }
            	}
            	else if(ch=='B'){
                    if(lineno<filelist.size()-1){
                        lineno++;
                        down;
                    }
            	}
            	else if(ch=='C'){
                    if(!frontstack.empty()){
                        string file=frontstack.top();
                        frontstack.pop();
                        backstack.push(file);
                        listContent(file);
                        pos(0,0);
                        lineno=0;
                    }
                }
            	else if(ch=='D'){
                    if(backstack.size()>1){
                        string file=backstack.top();
                        backstack.pop();
                        frontstack.push(file);
                        file=backstack.top();
                        listContent(file);
                        pos(0,0);
                        lineno=0;
                    }
                }
            	else{

                }
            }
            else if(ch==104 || ch==72){
                backstack.push(home);
                while(!frontstack.empty()) frontstack.pop();
                listContent(home);
                pos(0,0);
                lineno=0;
            }
            else if(ch==127){
                if(currentPath != home){
                    while(!frontstack.empty()) frontstack.pop();
                    currentPath=currentPath.substr(0, currentPath.find_last_of("\\/"));
                    listContent(currentPath);
                    pos(0,0);
                    lineno=0;
                }
            }
            else if(ch=='\n'){
                string file;
                if(isSearchResult){
                    file=results[lineno];
                    isSearchResult=false;
                }
                else{
                    file=filelist[lineno];
                }

                struct stat sb;
                stat(file.c_str(), &sb);
                bool isDirectory=S_ISDIR(sb.st_mode);

                if(isDirectory){
                    string currentFile=file.substr(file.find_last_of("\\/")+1,file.length());
                    if(currentFile.compare(".")==0){
                        listContent(currentPath);
                        pos(0,0);
                        lineno=0;
                    }
                    else if(currentFile.compare("..")==0){
                        currentPath=currentPath.substr(0, currentPath.find_last_of("\\/"));
                        backstack.push(currentPath);
                        listContent(currentPath);
                        pos(0,0);
                        lineno=0;
                    }
                    else{
                        backstack.push(file);
                        listContent(file);
                        lineno=0;
                        pos(0,0);
                    }
                }
                else{
                    int pid = fork();
                    if (pid == 0) {
                        close(2);
                        execlp("/usr/bin/xdg-open", "xdg-open", file.c_str(), NULL);
                        exit(1);
                    }
                }
            }
            else if(ch==':'){
                commands(false);
            }
            else if(ch=='q'){
                printf("\033[?1049l"); //out of alternate buffer
                tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
                exit(1);
            }
            else{

            }
        }
    }
    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
}
