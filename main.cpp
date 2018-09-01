/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"
extern struct winsize w;

/*
    main function that drives the entire application
*/
int main(int argc, char *argv[]){

    printf("\033[?1049h\033[H");    //alternate buffer

    extern string home,currentPath;
    extern ofstream myfile;
    extern stack<string> backstack;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    myfile.open ("debug.txt");
    if(argc==1){
        home=getpwd();
        backstack.push(home);
        currentPath=home;
        listContent(".");
        handleCommands(false);
    }
    else{
        home=argv[1];
        backstack.push(home);
        currentPath=argv[1];
        listContent(argv[1]);
        handleCommands(false);
    }
    return 0;
}
