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
int k = 0; // 棋子編號
const int N = 17;
int b[N][N]; // 儲存每個座標的值 (eg. 空地、玩家棋子)
int index; // 棋子編號
struct place // (y,x)
{
	int y;
	int x;
};
struct place find_pos[4]; // 找到可能可以跳的座標
struct place pos[15]; // 原始座標
struct place new_pos; // 可以走到的座標
struct place fin_pos; // 經過比較之後，確定要走的
struct place target; // 終點
int main(int argc, char *argv[])
{
	color = *argv[1] - '0'; // 給予顏色代號
	if (color == 2) // 根據不同顏色給予不同終點
	{
		target = { 4,16 }; //y,x
	}
	else if (color == 3) {
		target = { 16,4 };
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
				pos[k].x = i;
				pos[k].y = j;
				k++; // 給棋子編號
			}
		}
	}
}

void find_p()
{
	int min = 600;
	do
	{
		srand(time(NULL));
		index = rand() % 15; // 從0~14號棋子隨機選一顆
		// cout << index << endl;
		// cout << "(" << pos[index].x << "," << pos[index].y << ")" << endl;
		find_pos[0].x = (pos[index].x ); // 往旁邊找或許能走的位置
		find_pos[0].y = (pos[index].y - 1);
		find_pos[1].x = (pos[index].x);
		find_pos[1].y = (pos[index].y + 1);
		find_pos[2].x = (pos[index].x + 1);
		find_pos[2].y = (pos[index].y - 1);
		find_pos[3].x = (pos[index].x + 1);
		find_pos[3].y = (pos[index].y );
	}while((b[find_pos[0].y][find_pos[0].x] != 1 && b[find_pos[1].y][find_pos[1].x] != 1 && b[find_pos[2].y][find_pos[2].x] != 1 && b[find_pos[3].y][find_pos[3].x] != 1));
	
	for(int i = 0; i<4; i++){
		if(find_pos[i].x >= 0 && find_pos[i].y >= 0 && find_pos[i].x < 17 && find_pos[i].y < 17) {
			if(b[find_pos[i].y][find_pos[i].x] == 1){
				new_pos.x = find_pos[i].x;
				new_pos.y = find_pos[i].y;
				int n = distance();
				if (min > distance())
				{
					min = n;
					fin_pos.x = new_pos.x;
					fin_pos.y = new_pos.y;
				}

			}
			else{


			}

		}
	}
}

int distance(){
	int d;
	d = ((new_pos.x - target.x)*(new_pos.x - target.x)) + ((new_pos.y - target.y)*(new_pos.y - target.y));
	return d;
}

void output()
{
	ofstream s1072026;
	s1072026.open("s1072026.txt");
	s1072026 << 1 << endl;
	s1072026 << pos[index].x << " " << pos[index].y << endl;
	s1072026 << fin_pos.x << " " << fin_pos.y << endl;
	s1072026.close();
}
