/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "macro.h"

extern ofstream myfile;
extern string currentPath,home;
extern vector<string> results, printresults;
extern stack<string> backstack;
vector<string> split;
extern struct winsize w;

/*
    this function handles writing of command
    in the command mode
*/
void commands(bool fail){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    string command="";
    pos(w.ws_row,0);
    clearline;
    if(fail){
        cout<<":error";
        command="error";
    }
    else cout<<":";
    char ch;

    while(ch=cin.get()){
        if(ch=='\n'){
            //cout<<"\b"<<command;
            runCommand(command);
            command="";
        }
        else if(ch==127){
            if(command.length()>0){
                command.pop_back();
                clearline;
                pos(w.ws_row,0);
                cout<<":"<<command;
            }
        }
        else{
            if(ch==27){
                pos(w.ws_row,0);
                cout<<"Normal mode";
                pos(0,0);
                listContent(currentPath);
                handleCommands(false);
            }
            cout<<ch;
            command+=ch;
        }
    }
}

/*
    this function calls the respective command
    function to execute from their respective files
*/
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
        if(split.size()<=1){
            commands(true);
        }
        else{
            copyContent(split);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else if(commandName.compare("move")==0){
        if(split.size()<=1){
            commands(true);
        }
        else moveContent(split);
        pos(w.ws_row,0);
        clearline;
        cout<<":";
    }
    else if(commandName.compare("rename")==0){
        if(split.size()<=2){
            commands(true);
        }
        else{
            changeName(split[1], split[2]);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else if(commandName.compare("create_dir")==0){
        //myfile<<"sending "<<split[1]<<" "<<split[2]<<endl;
        if(split.size()<=2){
            commands(true);
        }
        else{
            createDirectory(split[1], split[2]);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else if(commandName.compare("create_file")==0){
        if(split.size()<=2){
            commands(true);
        }
        else{
            createFile(split[1], split[2]);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else if(commandName.compare("delete_file")==0){
        if(split.size()<=1){
            commands(true);
        }
        else{
            deleteFile(split[1]);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else if(commandName.compare("delete_dir")==0){
        if(split.size()<=1){
            commands(true);
        }
        else{
            deleteDirectory(split[1]);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else if(commandName.compare("goto")==0){
        if(split.size()<=1){
            commands(true);
        }
        else{
            gotoDirectory(split[1]);
        }
    }
    else if(commandName.compare("search")==0){
        if(split.size()>1){
            results.clear();
            printresults.clear();
            search(currentPath, split[1]);
            cls;
            backstack.push(currentPath);
            pos(0,0);
            displaySearchResults();
            pos(0,0);
            handleCommands(true);
        }
        else commands(true);
    }
    else if(commandName.compare("snapshot")==0){
        if(split.size()<=2){
            commands(true);
        }
        else{
            getSnapshot(split[1], split[2]);
            pos(w.ws_row,0);
            clearline;
            cout<<":";
        }
    }
    else{
        commands(true);
    }
}

/*
    this function is used to generate
    fullpath from given path and name
*/
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

/*
    this function generates absolute
    path from given path
*/
string getWholePath(string name){
    string fullpath=home;
    if(name.compare(".")==0){
        fullpath=currentPath;
    }else if(name[0]=='~'){
        fullpath.append(name.substr(1,name.length()-1));
    }
    else if(name[0]=='/'){
        fullpath.append(name);
    }
    else{
        fullpath=currentPath;
        fullpath.append("/"+name);
    }
    return fullpath;
}
