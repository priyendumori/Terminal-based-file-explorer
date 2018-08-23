using namespace std;

#define esc 27

#define cls printf("%c[2J",esc)
#define cls1 printf("%c[3J%c[1;1H",esc,esc)
#define pos(row,col) printf("%c[%d;%dH",esc,row,col)

#define up printf("%c[%dA",esc,1);
#define down printf("%c[%dB",esc,1);

#define scroll printf("%c[r",esc);

int listContent(const char*);
void displayContent(const char *);
void handleCommands();
string getPath(string name);
string getpwd();
