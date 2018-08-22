#include "header.h"

#define esc 27

#define cls printf("%c[2J",esc)

#define pos(row,col) printf("%c[%d;%dH",esc,row,col)

#define up printf("%c[%dA",esc,1);
#define down printf("%c[%dB",esc,1);

using namespace std;

int listContent(const char* name){
    //cls;
    printf("\033[2J\033[1;1H");
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (name)) != NULL) {
        /* print all the files and directories within directory */
        struct stat sb;

        while ((ent = readdir (dir)) != NULL) {
            if (stat(ent->d_name, &sb) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
            }

            printf ("%s ", ent->d_name);

            printf("%ld : %ld ", (long) sb.st_uid, (long) sb.st_gid);

            printf("%lld bytes ", (long long) sb.st_size);

            printf("%lo ", (unsigned long) sb.st_mode);

            printf("%s", ctime(&sb.st_mtime));
        }
        printf("\n");
        closedir (dir);
    }
    else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 1;
}

void handleInput(){


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
                		up;
                	}
                	else if(ch=='B'){
                		down;
                	}
                	else if(ch=='C')
                		cout<<"Right";
                	else if(ch=='D')
                		cout<<"Left";
                	else
                		cout<<"ESC";
                }
                else if(ch==104 || ch==72){
                	cout<<"home";
                }
                else if(ch==127)
                	cout<<"Back";
                else if(ch=='\n'){
                    //listContent("/home/priyendu/Desktop");
                	cout<<"new line";
                }
                else
                	cout<<ch;
            }

    }


    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);

}

int main(){

    listContent(".");
    handleInput();

    return 0;
}
