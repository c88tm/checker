#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;
void read(); // 讀檔
void find_p(); // 找到要跳的座標
int distance(); // 計算距離
void output(); // 輸出
int color; // 玩家顏色
const int N = 17;
int b[N][N]; // 儲存每個座標的值 (eg. 空地、玩家棋子)
int index; // 棋子編號
int fin_index;
int fin_dir;
int fin_score = -100;
struct place // (x,y)
{
	int x;
	int y;
};
struct place find_pos[4]; // 找到可能可以跳的座標
struct place pos[15]; // 原始座標
struct place new_pos; // 可以走到的座標
struct place fin_pos; // 經過比較之後，確定要走的
struct place 
struct place target; // 終點
int main(int argc, char *argv[])
{
	color = *argv[1] - '0'; // 給予顏色代號
	if (color == 2) // 根據不同顏色給予不同終點
	{
		target = { 16,4 }; //y,x
	}
	else if (color == 3) {
		target = { 4,16 };
	}
	else if (color == 4) {
		target = { 4,4 };
	}
	read();
	find_p();
	output();
	// system("pause");
}

void read()
{
	ifstream board;
	board.open("board.txt");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board >> b[i][j];
		}
	}
	board.close();

	for (int i = 0; i < N; i++) { // 儲存每一個自己棋子的座標
		for (int j = 0; j < N; j++) {
			if (b[i][j] == color) { //如果該座標是自己的棋子就儲存到pos[]
				int k = 0;
				pos[k].x = i;
				pos[k].y = j;
				k++; // 給棋子編號
			}
		}
	}
}

void find_p()
{
	while(還有時間){
		srand(time(NULL));
		index = rand() % 15;
		direction = rand() % 6;
		int dir_x[6] = {0, 1, 1, 0, -1, -1};
		int dir_y[6] = {-1, -1, 0, 1, 1, 0};
		dir_x[direction]

		find_pos.x = (pos[index].x + dir_x[direction]);
		find_pos.y = (pos[index].y + dir_y[direction]);

		if(find_pos.x >= 0 && find_pos.x < 17 && find_pos.y >= 0 && find_pos.y < 17 ){
			if(b[find_pos.x][find_pos.y] == 1){ // score 用來紀錄走法的好壞，每一次都要比遠始位置更靠近終點
				score = distance(pos[index]) - distance(find_pos);
				if(score > fin_score){
					fin_index = index;
					fin_dir = direction;
					fin_score = score;
				}
			}
		}

		int distance(struct place a){
			int d;
			d = ((a.x - target.x)*(a.x - target.x)) + ((a.y - target.y)*(a.y - target.y));
			return d;
		}

	}

void output()
{
	ofstream s1072026;
	s1072026.open("s1072026.txt");
	s1072026 << "1" << endl;
	s1072026 << pos[index].x << " " << pos[index].y << endl;
	s1072026 << fin_pos.x << " " << fin_pos.y << endl;
	s1072026.close();
}
