#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;
#define MAX_BUF 65535
#define MAX_PATH_LENGTH 200
#define EMPTY 1
#define WAIT_TIME 6000

string pl_cmd[3];
string pl_name[3];

int players;

int call_pl(int i);//calling player
void cls(HANDLE hConsole);


int board_init[2][17][17] = {
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}, {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0},
    {0, 0, 0, 3, 3, 1, 1, 1, 1, 1, 1, 4, 4, 0, 0, 0, 0},
    {0, 0, 3, 3, 3, 1, 1, 1, 1, 1, 4, 4, 4, 0, 0, 0, 0},
    {0, 3, 3, 3, 3, 1, 1, 1, 1, 4, 4, 4, 4, 0, 0, 0, 0},
    {3, 3, 3, 3, 3, 1, 1, 1, 4, 4, 4, 4, 4, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}};

class Point{
    public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point& operator=( const Point& p){
        this->x = p.x;
        this->y = p.y;
        return *this;
    }
    Point operator+( const Point& p){
        Point tmp;
        tmp.x = this->x + p.x;
        tmp.y = this->y + p.y;
        return tmp;
    }
    Point operator-( const Point& p){
        Point tmp;
        tmp.x = this->x - p.x;
        tmp.y = this->y - p.y;
        return tmp;
    }
    Point operator*( const int& c){
        Point tmp;
        tmp.x = this->x * c;
        tmp.y = this->y * c;
        return tmp;
    }
    friend bool operator==(const Point& lhs, const Point& rhs){
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
    friend ostream & operator << (ostream &out, const Point &p)
    {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};
Point dir[6] = {{0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}};

class Move{
    public:
    Point start;
    Point path[MAX_PATH_LENGTH];
    int steps;
    Move(Point start = Point(0, 0), Point *path = NULL, int steps = 0) : start(start), steps(steps){
        for(int i = 0; i < steps; i++){
            this->path[i] = path[i];
        }
    }
    Move& operator=( const Move& m){
        this->start = m.start;
        this->steps = m.steps;
        for(int i = 0; i < m.steps; i++){
            this->path[i] = m.path[i];
        }
        return *this;
    }
    friend ostream & operator << (ostream &out, const Move &m){
        out << "Start: " << m.start;
        for(int i = 0; i < m.steps; i++){
            out << " -> " << m.path[i];
        }
        return out;
    }
    void append(Point p){
        path[steps++] = p;
    }
    Point pop(){
        return path[--steps];
    }
};

Move readMoveFromFile(string filename){
    FILE *f = fopen(filename.c_str(),"r");
    Move ret = Move();
    fscanf(f, "%d", &ret.steps);
    int tmpx, tmpy;
    fscanf(f, "%d %d", &tmpx, &tmpy);
    ret.start = Point(tmpx, tmpy);
    for(int i = 0; i < ret.steps; i++){
        fscanf(f, "%d %d", &tmpx, &tmpy);
        ret.path[i] = Point(tmpx, tmpy);
    }
    fclose(f);
    return ret;
}

class Board{
    public:
    int board[17][17];
    Point goal[3][15];
    Board(int pl_num){
        int goal_num[3]={0};
        for(int i = 0; i < 17; i++)
        for(int j = 0; j < 17; j++){
            this->board[i][j] = board_init[pl_num - 2][i][j];
        }
        
    }

    void print(){
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD wOldColorAttrs;
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(h, &csbiInfo);
        wOldColorAttrs = csbiInfo.wAttributes;

        SetConsoleCursorPosition(h, {0,0});

        for (int i = 0; i < 17; i++){
            for (int j = 0; j < i; j++) cout << ' ';
            for (int j = 0; j < 17; j++){
                char c;
                if(board[i][j] > 1){
                    SetConsoleTextAttribute(h, board[i][j] - 1);
                    c = 'A';
                }else if(board[i][j] == 1){
                    SetConsoleTextAttribute(h, 15);
                    c = 'o';
                }else if(board[i][j] == -1){
                    SetConsoleTextAttribute(h, 14);
                    c = 'o';
                }else{
                    c = ' ';
                }
                cout << c << " \n"[j == 16];
                SetConsoleTextAttribute(h, wOldColorAttrs);
            }
        }
        SetConsoleTextAttribute(h, wOldColorAttrs);
    }

    void writeToFile(const char *filename){
        FILE *f = fopen(filename, "w");
        for(int i = 0; i < 17; i++){
            for(int j = 0; j < 17; j++){
                fprintf(f,"%d%c", board[i][j], " \n"[j==16]);
            }
        }
        fclose(f);
    }

    int inRange(Point p){
        if(p.x < 0 || p.x >= 17 || p.y < 0 || p.y >= 17 )return 0;
        return 1;
    }

    int isMoveable(Point p, Point dest){
        if(!inRange(p) || !inRange(dest))return 0;
        if(board[p.x][p.y] <= EMPTY || board[dest.x][dest.y] != EMPTY)return 0;
        Point diff = p - dest;
        for(int i = 0; i < 6; i++){
            if(diff == dir[i])return 1;
        }
        return 0;
    }

    int isHoppable(Point p, Point dest){
        if(!inRange(p) || !inRange(dest))return 0;
        if(board[p.x][p.y] <= EMPTY || board[dest.x][dest.y] != EMPTY)return 0;
        Point diff = p - dest;
        for(int i = 0; i < 6; i++){
            if(diff == dir[i] * 2)return 1;
        }
        return 0;
    }

    void moveChecker(Point p, Point dest){
        if(p == dest)return;
        board[dest.x][dest.y] = board[p.x][p.y];
        board[p.x][p.y] = 1;
        return;
    }

    int makeMove(Move m, int player){
        if(player != board[m.start.x][m.start.y])return 0;
        //If is Moving
        if (m.steps == 1 && isMoveable(m.start, m.path[0])){
            moveChecker(m.start, m.path[0]);
            return 1;
        }
        //If is Hopping
        Point cur_pos = m.start;
        for(int i = 0; i < m.steps; i++){
            if( isHoppable( cur_pos, m.path[i] ) ){
                moveChecker( cur_pos, m.path[i] );
                cur_pos = m.path[i];
            }else{
                moveChecker(cur_pos, m.start);
                return 0;
            }
        }
        return 1;
    }

    int isWinner(int player){
        for(int i = 0; i < 15; i++){
            Point g = goal[player - 2][i];
            if(board[g.x][g.y] != player)return -1;
        }
        return player;
    }
};


int main(int argc, char *argv[]){

    //Setup proc relative stuff.

    string path, filename;
    string::size_type pos = string(argv[0]).find_last_of( "\\/" );
    filename = string(argv[0]).substr(pos + 1);
    path = string(argv[0]).substr(0, pos);

    if(argc < 3 || argc > 4){
        printf("\nUsage: .\\%s <AI1> <AI2> [<AI3>]\n", filename.c_str());
        printf("All AI.exes should be kept within the same folder\n");
        printf("Server will call <AI#>.exe with \".\\<AI#>.exe <player_num>\"\n");
        printf("Where <player_num> is the number that indicates the player on chess board\n");
        printf("In each round, player should read inputs from board.txt and outputs to <AI#>.txt\n");
        return 0;
    }
    players = argc - 1;
    for(int i = 0; i < players; i++){
        pl_cmd[i] = path + "\\" + argv[i + 1] + " " + to_string(i+2);
        pl_name[i] = string(argv[i + 1]);
        cout << pl_cmd[i] << '\n';
    }

    //Setup of printing
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    COORD coordScreen = {0, 0};
    SetConsoleCursorPosition(h, coordScreen);    

    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    cls(h);
    // Board
    Board board = Board(players);
    //Round
    int round = 0, winner = -1, err = 0;
    cls(h);
    board.writeToFile("board.txt");
    for(;winner == -1;round++){
        int player = round % 3 + 2;//2 or 3
        cls(h);
        board.print();
        printf("Round %d, calling player %d\n======\n",round, player);
        int ret = call_pl(player - 2);
        if(ret != 0){
            printf("skip this move.\n");
            continue;
        }
        Move move = readMoveFromFile(pl_name[player - 2] + ".txt");
        cout << move << '\n';
        if(!board.makeMove(move, player)){
            printf("Move illegal!\n");
            winner = player;
            err = 1;
            break;
        }
        if((winner = board.isWinner(player)) != -1)break;
        board.writeToFile("board.txt");
        Sleep(500);
    }
    if(!err){
        cout << "Winner is " << pl_name[winner - 2]; 
    }
    return 0;
}

int call_pl(int i){
    int ret;
    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION pi;
    LPSTR s = const_cast<LPSTR>(pl_cmd[i].c_str());
    if (CreateProcess(NULL, s, NULL, NULL, TRUE, 0, NULL, NULL, &info, &pi))
    {
        ret = WaitForSingleObject(pi.hProcess, WAIT_TIME);
        printf("\n======\n");
        if(ret == 0){
            // printf("player returned a move.\n");
        }else if(ret == 0x102){
            printf("player timed out.\n");
        }else{
            printf("something went wrong.\n");
        }
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return ret;
}

void cls(HANDLE hConsole){
    COORD coordScreen = {0, 0}; // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.

    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.

    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.

    SetConsoleCursorPosition(hConsole, coordScreen);
}