#include "header.h"
#include "macro.h"

int lineno=0;

extern vector<string> filelist, results;
extern stack<string> backstack,frontstack;
extern string currentPath;
extern ofstream myfile;
extern string home;

void handleCommands(bool isSearchResult){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    //pos(0,0);
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
                        //scrollup;
                    }
                    //\033[6n
            	}
            	else if(ch=='B'){
                    if(lineno<filelist.size()-1){
                        lineno++;
                        down;
                        //scrolldown;
                    }
            	}
            	else if(ch=='C'){
            		//cout<<"Right";
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
            		//cout<<"Left";
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
            		//cout<<"ESC";

                }
            }
            else if(ch==104 || ch==72){
                backstack.push(home);
                while(!frontstack.empty()) frontstack.pop();
                listContent(home);
                pos(0,0);
                lineno=0;
                //cout<<"home";
            }
            else if(ch==127){
            	//cout<<"Back";
                //string s1("../somepath/somemorepath/somefile.ext");
                //myfile << s1.substr(0, s1.find_last_of("\\/")) << endl;
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
                myfile<<endl<<file<<endl;
                struct stat sb;
                stat(file.c_str(), &sb);
                bool isDirectory=S_ISDIR(sb.st_mode);

                if(isDirectory){

                    string currentFile=file.substr(file.find_last_of("\\/")+1,file.length());
                    myfile<<"opening "<<file<<endl;
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


                    stack<string> temp=backstack;
                    myfile<<endl<<"backstack "<<endl;
                    while(!temp.empty()){
                        myfile << temp.top()<<endl;
                        temp.pop();
                    }

                    stack<string> temp1=frontstack;
                    myfile<<endl<<"frontstack "<<endl;
                    while(!temp1.empty()){
                        myfile << temp1.top()<<endl;
                        temp1.pop();
                    }

                }
                else{

                    /*string run="bash -c 'xdg-open "; run.append(file); run.append("' 2 > /dev/null");
                    string run1="bash -c 'xdg-open "+file+"' 2>/dev/null";
                    system(run1.c_str());*/
                    int pid = fork();

                    if (pid == 0) {
                        close(2);
                        myfile<<"opening file "<<file<<endl;
                        execlp("/usr/bin/xdg-open", "xdg-open", file.c_str(), NULL);
                        myfile<<"opened "<<endl;
                        exit(1);
                  }
                }
            }
            else if(ch==':'){
                commands();

            }
            else if(ch=='q'){
                printf("\033[?1049l"); //out of alternate buffer
                tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
                exit(1);
            }
            else{
                //tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
                //printf("\033[?1049l"); //out of alternate buffer
                //exit(1);
            	//cout<<ch;
            }
        }

    }


    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}
