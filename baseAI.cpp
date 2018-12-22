#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;
#define b(x, y) (board[(x* 19 + y)])

typedef struct Pair{
    int x, y;
}P;

int board[361] = {0};
P p[15];
int dir_x[6] = {0, 1, 1, 0, -1, -1};
int dir_y[6] = {-1, -1, 0, 1, 1, 0};

int main(int argc, char *argv[]){
    // Setting up IO

    int player = 0;
    char buf[80];
    if(argc == 2){
        printf("this is player %s\n", argv[1]);
        player = argv[1][0] - '0';
    }else return 0;
    char pl_name[80];
    strcpy(pl_name, strrchr(argv[0], '\\') + 1);
    if(strrchr(pl_name, '.') != NULL) *strrchr(pl_name, '.') = '\0';
    sprintf(buf, "%s.txt", pl_name);

    FILE *in = fopen("board.txt", "r");
    FILE *out = fopen(buf, "w");
    // IO
    int count = 0;
    for(int i = 1; i <= 17; i++){
        for(int j = 1; j <= 17; j++){
            fscanf(in, "%d", &b(i, j));
            if(b(i, j) == player){
                p[count].x = i;
                p[count++].y = j;
            }
        }
    }
    //find all moves
    P move[90];
    int moves = 0;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 6; j++){
            P new_pos;
            new_pos.x = p[i].x + dir_x[j];
            new_pos.y = p[i].y + dir_y[j];
            if(b(new_pos.x, new_pos.y) == 1){
                move[moves].x = i;
                move[moves++].y = j;
            }
        }
    }
    //pick a move
    srand(time(NULL));
    int random = rand() % moves;
    //output
    P tmp;
    tmp.x = p[move[random].x].x - 1;
    tmp.y = p[move[random].x].y - 1;
    sprintf(buf, "%d\n%d %d\n", 1, tmp.x, tmp.y);
    tmp.x += dir_x[move[random].y];
    tmp.y += dir_y[move[random].y];
    sprintf(buf, "%s%d %d\n", buf, tmp.x, tmp.y);
    printf("%s", buf);
    fprintf(out, "%s", buf);
    fclose(in);
    fclose(out);
    return 0;
}