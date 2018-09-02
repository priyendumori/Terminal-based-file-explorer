/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

/*
    this file contains macro and function definitions
*/

using namespace std;

#define esc 27
#define cls printf("%c[2J",esc)
#define cls1 printf("%c[3J%c[1;1H",esc,esc)
#define pos(row,col) printf("%c[%d;%dH",esc,row,col)

#define up printf("%c[%dA",esc,1);
#define down printf("%c[%dB",esc,1);
#define clearline printf("%c[%dK",esc,2);
#define clearlineaftercursor printf("%c[K",esc);
#define scroll(start,end) printf("%c[%d;%dr",esc,start,end);
#define scrollup printf("%c[%dT",esc,1);
#define scrolldown printf("%c[%dS",esc,1);

int listContent(string);
void displayContent(const char *);
void handleCommands(bool);
string getPath(string);
string getpwd();
void commands(bool);
void runCommand(string);
void changeName(string, string);
void createDirectory(string, string);
string createPath(string , string);
void createFile(string, string);
void gotoDirectory(string);
void deleteFile(string);
void deleteDirectory(string);
void getSnapshot(string, string);
void copyContent(vector<string>);
void moveContent(vector<string>);
void deleteHelper(string);
string getWholePath(string );
void search(string, string);
void displaySearchResults();
