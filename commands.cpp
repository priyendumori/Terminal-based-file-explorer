#include "header.h"
#include "macro.h"

extern ofstream myfile;
extern string currentPath,home;

vector<string> split;
struct winsize w;

void commands(){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    pos(w.ws_row,0);
    clearline;
    cout<<":";
    char ch;
    string command="";
    while(ch=cin.get()){
        if(ch=='\n'){
            //cout<<"\b"<<command;
            runCommand(command);
            command="";
        }
        else{
            if(ch==27){
                pos(w.ws_row,0);
                cout<<"Normal mode";
                pos(0,0);
                listContent(currentPath);
                handleCommands();
            }
            cout<<ch;
            command+=ch;
        }
    }
}


void runCommand(string command){
    //myfile<<"command line: "<<command<<endl<<endl;
    split.clear();
    char *c=strcpy(new char[command.length()+1], command.c_str() );
    char *token = strtok(c, " ");
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        split.push_back(token);
        token = strtok(NULL, " ");
    }

    string commandName=split[0];
    if(commandName.compare("copy")==0){

    }
    else if(commandName.compare("move")==0){

    }
    else if(commandName.compare("rename")==0){
        changeName(split[1], split[2]);
        pos(w.ws_row,0);
        clearline;
        cout<<":";
    }
    else if(commandName.compare("create_dir")==0){
        //myfile<<"sending "<<split[1]<<" "<<split[2]<<endl;
        createDirectory(split[1], split[2]);
        pos(w.ws_row,0);
        clearline;
        cout<<":";
    }
    else if(commandName.compare("create_file")==0){
        createFile(split[1], split[2]);
        pos(w.ws_row,0);
        clearline;
        cout<<":";
    }
    else if(commandName.compare("delete_file")==0){
        deleteFile(split[1], split[2]);
        pos(w.ws_row,0);
        clearline;
        cout<<":";
    }
    else if(commandName.compare("delete_dir")==0){
        deleteDirectory(split[1], split[2]);
        pos(w.ws_row,0);
        clearline;
        cout<<":";
    }
    else if(commandName.compare("goto")==0){
        gotoDirectory(split[1]);
    }
    else if(commandName.compare("search")==0){

    }
    else if(commandName.compare("snapshot")==0){

    }
}

string createPath(string path, string name){
    string fullpath=home;
    if(path.compare(".")==0){
        //myfile<<"in ."<<endl;
        fullpath=currentPath;
    }else if(path[0]=='~'){
        //myfile<<"in ~"<<endl;
        fullpath.append(path.substr(1,path.length()-1));
    }
    else if(path[0]=='/'){
        //myfile<<"in /"<<endl;
        fullpath.append(path);
    }
    else{
        //myfile<<"in else"<<endl;
        fullpath=currentPath;
        fullpath.append("/"+path);
    }
    fullpath.append("/"+name);

    return fullpath;
}
