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

string ai_cmd[2];

int call_pl(int i);//calling player
void cls(HANDLE hConsole);

int board_2[17][17] = {
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
};

class Point{
    public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point operator+( const Point& p){
        Point tmp;
        tmp.x = this->x + p.x;
        tmp.y = this->y + p.y;
        return tmp;
    }
    Point& operator=( const Point& p){
        this->x = p.x;
        this->y = p.y;
        return *this;
    }
    friend ostream & operator << (ostream &out, const Point &p)
    {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};

class Move{
    public:
    Point start;
    Point path[MAX_PATH_LENGTH];
    int steps;
    Move(Point start, Point *path, int steps) : start(start), steps(steps){
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
    friend ostream & operator << (ostream &out, const Move &m)
    {
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

class Board{
    public:
    int board[17][17];
    Board(){
        for(int i = 0; i < 17; i++)
        for(int j = 0; j < 17; j++)
            this->board[i][j] = board_2[i][j];
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

    int isMoveable(pair<int, int> p, pair<int, int>dest){
        if(p.first < 0 || p.first >= 17 || p.second < 0 || p.second >= 17 || dest.first < 0 || dest.first >= 17 || dest.second < 0 || dest.second >= 17)return 0;
        if(board[p.first][p.second] <= 1 || board[dest.first][dest.second] != 1)return 0;
        int x = p.first - dest.first;
        int y = p.second - dest.second;
        if(abs(x) <= 1 && abs(y) <= 1 && abs(x+y) != 2)return 1;
        return 0;
    }

    int isHoppable(pair<int, int> p, pair<int, int>dest){
        if(p.first < 0 || p.first >= 17 || p.second < 0 || p.second >= 17 || dest.first < 0 || dest.first >= 17 || dest.second < 0 || dest.second >= 17)return 0;
        if(board[p.first][p.second] <= 1 || board[dest.first][dest.second] != 1)return 0;
        int x = p.first - dest.first;
        int y = p.second - dest.second;
        if(x != 0 && x != 2 && x != -2) return 0;
        if(y != 0 && y != 2 && y != -2) return 0;
        if(abs(x+y) != 4 && board[(p.first + dest.first) / 2][(p.second + dest.second) / 2] > 1 )return 1;
        return 0;
    }

    int Move(pair<int, int> p, pair<int, int> dest[], int moves){
        pair<int, int> cur = p;
        int check = 1;
        if (moves == 1){
            if(isMoveable(p, dest[0])){
                board[dest[0].first][dest[0].second] = board[p.first][p.second];
                board[p.first][p.second] = 1;
                return 1;
            }
        }
        for(int i = 0; i < moves; i++){
            if(isHoppable(cur, dest[i])){
                cur = dest[i];
            }else{
                check = 0;
                break;
            }
        }
        if(check){
            board[dest[moves-1].first][dest[moves-1].second] = board[p.first][p.second];
            board[p.first][p.second] = 1;
        }
        return 0;
    }
};

Point dir[6] = {{0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}};

int main(int argc, char *argv[]){

    //Setup proc relative stuff.

    string path, filename;
    string::size_type pos = string(argv[0]).find_last_of( "\\/" );
    filename = string(argv[0]).substr(pos + 1);
    path = string(argv[0]).substr(0, pos);

    if(argc != 3){
        printf("\nUsage: .\\%s <AI1> <AI2>\n", filename.c_str());
        printf("Both AI.exes should be kept within the same folder\n");
        printf("Server will call <AI#>.exe with \".\\<AI#>.exe <player_num>\"\n");
        printf("Where <player_num> is the number that indicates the player on chess board\n");
        printf("In each round, player should read inputs from board.txt and outputs to <AI#>.txt\n");
        return 0;
    }
    for(int i = 0; i < 2; i++){
        ai_cmd[i] = path + "\\" + argv[i + 1] + " " + to_string(i+2);
    }

    //Setup of printing
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    COORD coordScreen = {0, 0};
    SetConsoleCursorPosition(h, coordScreen);    

    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    // Board
    Board board = Board();
    //Round
    int round = 0, winner = -1;
    for(;winner == -1;round++){
        cls(h);
        board.writeToFile("board.txt");
        board.print();
        printf("Round %d, calling player %d",round, round % 2 + 2);
        int ret = call_pl(round % 2);
        if(ret != 0){
            printf("error occur or player timeout, skip this move.");
            continue;
        }
        // Move move = Move.readMoveFromFile(to_string(i+2) + ".txt");//TODO
        // if(!board.Move(move)){//TODO
        //     printf("Move illegal!\n");
        //     winner = !(round%2);
        // }
        // winner = board.winner();//TODO
    }
    
    return 0;
}

int call_pl(int i){
    int ret;
    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION pi;
    LPSTR s = const_cast<LPSTR>(ai_cmd[0].c_str());
    if (CreateProcess(NULL, s, NULL, NULL, TRUE, 0, NULL, NULL, &info, &pi))
    {
        ret = WaitForSingleObject(pi.hProcess, 3000);
        if(ret == 0){
            printf("player returned a move.\n");
        }else if(ret == 0x102){
            printf("player timed out.\n");
        }else{
            printf("something went wrong. server closing\n");
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