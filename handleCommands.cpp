#include "header.h"
#include "macro.h"

int lineno=0;

extern vector<pair<char,string>> list;

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
                    if(list[lineno].first=='f'){
                        //if(execl("/usr/bin/xdg-open", "xdg-open", list[lineno].second, (char *)0) !=0 );

                        //cout<<"ffffffffffffff"<<endl;
                    }
                    else{
                        //cout<<"ddddddddddddd"<<endl;

                        const char *file=list[lineno].second.c_str();
                        extern string currentPath;
                        //currentPath.append("/");
                        //currentPath.append(list[lineno].second);

                        listContent(file);
                        lineno=0;
                        pos(0,0);
                    }
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
