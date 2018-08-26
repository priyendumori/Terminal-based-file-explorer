#include "header.h"
#include "macro.h"

int lineno=0;

extern vector<string> filelist;

void handleCommands(){

    /*struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
*/

        pos(0,0);
        struct termios initialrsettings, newrsettings;
        char ch;

        tcgetattr(fileno(stdin), &initialrsettings);

        newrsettings = initialrsettings;
        newrsettings.c_lflag &= ~ICANON;
        newrsettings.c_lflag &= ~ECHO;
        //printf("Enter Key: ");

        if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
            fprintf(stderr,"Could not set attributes\n");
        }
        else {

            //pos(0,0);
            while(ch=cin.get()){


                if(ch==27){
                	ch=cin.get();
                	ch=cin.get();
                	if(ch=='A'){
                        lineno--;
                        up;
                        cout<<lineno;
                        //\033[6n
                	}
                	else if(ch=='B'){
                        lineno++;
                        down;
                        cout<<lineno;
                	}
                	else if(ch=='C')
                		cout<<"Right";
                	else if(ch=='D')
                		cout<<"Left";
                	else{
                		cout<<"ESC";
                    }
                }
                else if(ch==104 || ch==72){
                	cout<<"home";
                }
                else if(ch==127)
                	cout<<"Back";
                else if(ch=='\n'){
                    string file=filelist[lineno];
                    struct stat sb;
                    stat(file.c_str(), &sb);
                    bool isDirectory=S_ISDIR(sb.st_mode);

                    if(isDirectory){

                        extern string currentPath;
                        //currentPath.append("/");
                        //currentPath.append(filelist[lineno].second);
                        //cout<<file<<endl;

                        //if(filelist.empty()) filelist.clear();
                        listContent(file);
                        lineno=0;
                        pos(0,0);
                    }
                    else{

                    }/*
                    if(filelist[lineno].first=='f'){
                        //if(execl("/usr/bin/xdg-open", "xdg-open", filelist[lineno].second, (char *)0) !=0 );
                        //cout<<lineno;
                        //cout<<"ffffffffffffff"<<endl;
                    }
                    else{
                        //cout<<"ddddddddddddd"<<endl;

                        string file=filelist[lineno].second;
                        extern string currentPath;
                        //currentPath.append("/");
                        //currentPath.append(filelist[lineno].second);
                        //cout<<file<<endl;

                        //if(filelist.empty()) filelist.clear();
                        listContent(file);
                        lineno=0;
                        pos(0,0);
                    }*/
                    //cout<<lineno<<endl;
                }
                else{
                    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
                    printf("\033[?1049l"); //out of alternate buffer
                    exit(1);
                	cout<<ch;
                }
            }

    }


    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}
