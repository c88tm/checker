#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;
void read(); // 讀檔
void end();
void save_p();
void find_p(); // 找到要跳的座標
int distance(struct place a); // 計算距離
void output(); // 輸出
int color; // 玩家顏色
const int N = 17;
int b[N][N]; // 儲存每個座標的值 (eg. 空地、玩家棋子)
int k = 0, kk = 0;
int index, direction, score, end_index; // 棋子編號
int fin_index;
int fin_end_index;
int fin_dir;
int fin_score = -100;
int dir_x[6] = {0, 1, 1, 0, -1, -1};
int dir_y[6] = {-1, -1, 0, 1, 1, 0};
struct place // (x,y)
{
	int x;
	int y;
};
struct place find_pos; // 找到可能可以跳的座標
struct place pos[15]; // 原始座標
struct place new_pos; // 可以走到的座標
struct place fin_pos; // 經過比較之後，確定要走的
struct place target; // 終點
struct place targets[15];
int main(int argc, char *argv[])
{

	color = *argv[1] - '0'; // 給予顏色代號
    read();
    end();
    save_p();
	find_p();
	output();
    // cout << "find_pos.x = " << find_pos.x << endl;
    // cout << "find_pos.y = " << find_pos.y << endl;    
	// system("pause");
}

void read()
{
	ifstream board;
	board.open("board.txt");
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			board >> b[i][j];
		}
	}
	board.close();
}

void save_p()
{
	for (int i = 0; i < N; i++){ // 儲存每一個自己棋子的座標
		for (int j = 0; j < N; j++){
			if (b[i][j] == color){ //如果該座標是自己的棋子就儲存到pos[]
				pos[k].x = i;
				pos[k].y = j;
				k++; // 給棋子編號
                // cout << pos[k].x << " " << pos[k].y << endl;
			}
		}
	}
}
void end(){
    
    int end_p[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 4, 4, 4, 4, 1, 1, 1, 3, 3, 3, 3, 3},
        {0, 0, 0, 0, 4, 4, 4, 4, 1, 1, 1, 1, 3, 3, 3, 3, 0},
        {0, 0, 0, 0, 4, 4, 4, 1, 1, 1, 1, 1, 3, 3, 3, 0, 0},
        {0, 0, 0, 0, 4, 4, 1, 1, 1, 1, 1, 1, 3, 3, 0, 0, 0},
        {0, 0, 0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
	for (int i = 0; i < N; i++){ // 儲存每一個自己棋子的終點座標
		for (int j = 0; j < N; j++){
			if (end_p[i][j] == color && b[i][j] != color){ //如果該終點座標是自己的棋子就儲存到targets[]
				targets[kk].x = i;
				targets[kk].y = j;
				kk++; // 給棋子編號
			}
		}
	}

}
void find_p()
{
	auto start = std::chrono::system_clock::now();
	while(true){
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(elapsed_seconds.count() > 20) break;//跑個20秒鐘 就出去
		srand(time(NULL));
		index = rand() % 15;
        end_index = rand() % kk;
        target = targets[end_index];
		direction = rand() % 6;
		find_pos.x = (pos[index].x + dir_x[direction]);
		find_pos.y = (pos[index].y + dir_y[direction]);
		if(find_pos.x >= 0 && find_pos.x < 17 && find_pos.y >= 0 && find_pos.y < 17 ){
			if(b[find_pos.x][find_pos.y] == 1){ // score 用來紀錄走法的好壞，每一次都要比遠始位置更靠近終點
				score = distance(pos[index]) - distance(find_pos);
				if(score > fin_score){
					fin_index = index;
					fin_dir = direction;
					fin_score = score;
                    fin_end_index = end_index;
				}
			}
		}
        // cout << "fin_index = " << fin_index << endl;
        // cout << "fin_dir = " << fin_dir << endl;
        // cout << "fin_score = " << fin_score << endl;     
	}
}

int distance(struct place a){
	int d;
	d = ((a.x - target.x)*(a.x - target.x)) + ((a.y - target.y)*(a.y - target.y));
	// cout << "d = " << d << endl;
    return d;
}

void output()
{
	ofstream step;
	step.open("a.txt");
	step << "1" << endl;
	step << pos[fin_index].x << " " << pos[fin_index].y << endl;
	find_pos.x = (pos[fin_index].x + dir_x[fin_dir]);
	find_pos.y = (pos[fin_index].y + dir_y[fin_dir]);
	step << find_pos.x << " " << find_pos.y << endl;
	step.close();
}
