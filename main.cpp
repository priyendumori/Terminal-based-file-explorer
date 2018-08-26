#include "header.h"
#include "macro.h"

int main(int argc, char *argv[]){

    printf("\033[?1049h\033[H");    //alternate buffer

    extern string home,currentPath;
    extern ofstream myfile;
    myfile.open ("debug.txt");
    if(argc==1){
        home=getpwd();
        currentPath=home;
        listContent(".");
        handleCommands();
    }
    else{
        home=argv[1];
        currentPath=argv[1];
        listContent(argv[1]);
        handleCommands();
    }
    return 0;
}
