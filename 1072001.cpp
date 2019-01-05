#include <Windows.h>
#include <iostream>
#include <fstream>
#include<cmath>
#define ezra40907
using namespace std;
void readboard(bool);	//讀取棋盤
void saveboard();		//儲存棋盤(輸出棋盤)
void colorclass(int);	//分類棋子
void searchjump();		//搜尋可走範圍
void searchjump(int, int, int, int, int);
void clearsearch();		//清除
double distance(int); //算距離分數
void clean();		//清除(cjnum)
void choice(int);	//選擇移動
int choice(int, int);
int score_cal();	//計算分數
int movement1(int, int);	//移動分數加乘
void output_step(int);		//輸出步驟
int endpos[3][2] = {
					{16,4},		//顏色2
					{4,16},		//顏色3
					{4,4}		//顏色4
};
int startpos[3][2] = {
					{0,12},		//顏色2
					{12,0},		//顏色3
					{12,12}		//顏色4
};
int color;			//顏色控制
const int N = 17;	//棋盤格數
int A[N][N];		//棋盤(內容數字為顏色)
HWND hwnd;
int cjnum = 0;	//可跳的記數
struct piece {
	int x;
	int y;
	int color;
};
struct canjump {
	int x;
	int y;
	double endscore;
	double startscore;
	double movescore;
	double sumscore;
	double movementscore;
	int last_x;
	int last_y;
	int orignal_x;
	int orignal_y;
	int num;
};
int M[17][2];
struct piece my_piece[15];
struct piece en1_piece[15];
struct piece en2_piece[15];
struct canjump can_jump[500];

int main(int argc, char* argv[])
{
	color = *argv[1] - ('1' - 1);
	bool raw = true;	//讀取原始棋盤的控制子
	bool run = false;	//是否結束遊戲的控制子
	int select;

	//do {
	int in;
	//cout << "請輸入您的棋色" << endl;
	//cin >> color;
	readboard(raw);
	colorclass(color);
	searchjump();
	in = score_cal();
	choice(in);
	//move(in);		//測試執行用
	clean();
	saveboard();
	raw = false;
	//cout << "是否繼續執行(bool)";
	//cin >> run;
//} while (run == true);	//如果run=0則跳出遊戲
	return 0;
}
void readboard(bool raw)	//讀檔
{
	ifstream file, rawfile;
	if (raw == true) {	//第一次讀取原棋盤
		rawfile.open("board.txt");
		int i, j;
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				//rawfile >> A[j][i];
				rawfile >> A[i][j];
		rawfile.close();
	}
	else if (raw == false) {	//讀存檔
		file.open("board.txt");
		int i, j;
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				//file >> A[j][i];
				file >> A[i][j];
		file.close();

	}
#ifdef __WPDEBUG__ 
	dumpboard();
#endif
}
void colorclass(int color)
{
	int mynum = 0;
	int en1num = 0;
	bool b = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] > 1) {
				if (A[i][j] == color && mynum < 15) {
					my_piece[mynum].x = i;
					my_piece[mynum].y = j;
					my_piece[mynum].color = color;
					mynum++;
				}
				else if (A[i][j] != color && en1num < 30) {
					en1_piece[en1num].x = i;
					en1_piece[en1num].y = j;
					en1_piece[en1num].color = A[i][j];
					en1num++;
				}
				else {
					cout << "錯誤" << endl;
					b = true;
					break;
				}
			}
		}
		if (b == true)break;
	}
}
void searchjump() {

	for (int num = 0; num < 15; num++) {
		int x = my_piece[num].x;
		int y = my_piece[num].y;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if ((x + i < 17 && y + j < 17) && !((i < 0 && j < 0) || (i > 0 && j > 0))) {
					if (A[x + i][y + j] == 1 || A[x + i][y + j] == 5) {
						//*canjump.old_x = x;
						//*canjump.old_y = y;
						(can_jump[cjnum]).x = x + i;
						(can_jump[cjnum]).y = y + j;
						cout << "第" << cjnum << "筆資料" << endl;
						(can_jump[cjnum]).orignal_x = x;
						(can_jump[cjnum]).orignal_y = y;
						(can_jump[cjnum]).last_x = x;
						(can_jump[cjnum]).last_y = y;
						can_jump[cjnum].num = num;
						can_jump[cjnum].movementscore = movement1(i, j);
						(can_jump[cjnum]).endscore = distance(cjnum);//之後算距離分數用
						cout << "上一個位置:(" << (can_jump[cjnum]).last_x << "," << (can_jump[cjnum]).last_y << ")" << endl;
						cout << "原本的位置:(" << x << "," << y << ")" << endl << endl;
						A[x + i][y + j] = 5;
						cjnum++;
					}
				}
			}
		}
		searchjump(x, y, x, y, num);
	}
}

void searchjump(int a, int b, int ox, int oy, int num) {
	can_jump[cjnum].num = num;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (!((i < 0 && j < 0) || (i > 0 && j > 0))) {
				if ((a + 2 * i < N&& b + 2 * j < N) && ((A[a + i][b + j] > 1 && (A[a + 2 * i][b + 2 * j] == 1 ||
					A[a + 2 * i][b + 2 * j] == 5) && (A[a + i][b + j] != 5)))) {
					bool last = (a + 2 * i) == ox && ((b + 2 * j) == oy) || ((a + 2 * i) == can_jump[cjnum].orignal_x && ((b + 2 * j) == can_jump[cjnum].orignal_y));//有問題
					for (int k = 0; k < 10; k++) {
						bool last1 = (can_jump[cjnum - k].num == can_jump[cjnum].num && (can_jump[cjnum - k].x == a + 2 * i && can_jump[cjnum - k].y == b + 2 * j));
						if (last1 == true)return;
					}

					if ((last) == false) {
						if (can_jump[cjnum].num == can_jump[cjnum - 1].num) {
							can_jump[cjnum].movementscore = can_jump[cjnum - 1].movementscore + (2 * (movement1(i, j)));
						}
						else
							can_jump[cjnum].movementscore = 2 * (movement1(i, j));
						(can_jump[cjnum]).x = a + 2 * i;
						(can_jump[cjnum]).y = b + 2 * j;
						(can_jump[cjnum]).orignal_x = my_piece[num].x;
						(can_jump[cjnum]).orignal_y = my_piece[num].y;
						can_jump[cjnum].last_x = a;
						can_jump[cjnum].last_y = b;
						(can_jump[cjnum]).endscore = distance(cjnum);
						cout << A[17][3];
						cout << "第" << cjnum << "筆資料" << endl;
						cout << "上一個位置:(" << can_jump[cjnum].last_x << "," << can_jump[cjnum].last_y << ")" << endl;
						cout << "原本的位置:(" << (can_jump[cjnum]).orignal_x << "," << (can_jump[cjnum]).orignal_y << ")" << endl << endl;
						A[a + (2 * i)][b + (2 * j)] = 5;
						cjnum++;
						searchjump(a + (2 * i), b + (2 * j), a, b, num);
					}
				}
			}
		}
	}
}
void judge() {

}
void playtest()			//遊戲進行(測試)
{
	int i = 0, j = 4, c = 1;
	cin >> i >> j >> c;
	if (c != 0);
}
void move(int select)	//移動
{
	int x0 = can_jump[select].orignal_x;
	int y0 = can_jump[select].orignal_y;
	int x1 = can_jump[select].x;
	int y1 = can_jump[select].y;
	A[x0][y0] = 1;
	A[x1][y1] = color;
	clearsearch();
}

void saveboard()		//存檔
{
	ofstream file, rawfile;
	rawfile.open("board.txt");
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			rawfile << A[i][j] << " ";
		rawfile << endl;
	}
	rawfile.close();
}
void dumpboard()
{
	ifstream file;
	file.open("board.txt");
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			file >> A[j][i];
			cout << A[j][i] << " ";
		}
		cout << endl;
	}
	file.close();
}
void clearsearch() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] == 5)
				A[i][j] = 1;
		}
	}
}
double distance(int num)
{
	int start_x = startpos[color - 2][0];
	int start_y = startpos[color - 2][1];
	int x1 = can_jump[num].x;
	int y1 = can_jump[num].y;
	int x0 = can_jump[num].orignal_x;
	int y0 = can_jump[num].orignal_y;
	int end_x = endpos[color - 2][0];
	int end_y = endpos[color - 2][1];
	int edx = x1 - end_x;
	int edy = y1 - end_y;
	int sdx = start_x - x0;
	int sdy = start_y - y0;
	int pdx = x0 - x1;
	int pdy = y0 - y1;
	double l = 1.;
	double dx = l * sin(60 * 3.14159 / 180.);
	double dy = l * cos(60 * 3.14159 / 180.);
	double dxx;
	double dyy;
	double score;
	if (!((sdx >= 0 && sdy >= 0) || (sdx <= 0 && sdy <= 0)))
	{
		score = sdy - (sdx + sdy);
	}
	else
	{
		score = abs(sdx + sdy);
	}
	can_jump[cjnum].startscore = score;

	if (!((pdx >= 0 && pdy >= 0) || (pdx <= 0 && pdy <= 0)))
	{
		score = pdy - (pdx + pdy);
	}
	else
	{
		score = abs(pdx + pdy);
	}
	can_jump[cjnum].movescore = score;
	cout << "(" << x1 << "," << y1 << ") 離(" << end_x << "," << end_y << ")";
	dxx = abs(end_x - x1)*dx;
	dyy = abs(12 - abs(0 - end_x)*dy - end_y) + abs(12 - abs(0 - x1)*dy - y1);
	score = sqrt(pow(dxx, 2) + pow(dyy, 2));
	cout << score << "個位置。	";
	return score;
}
void clean()
{
	cjnum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] == 5)A[i][j] = 1;
		}
	}
}

void choice(int piece) {
	int x = can_jump[piece].x;
	int y = can_jump[piece].y;
	int Lx = can_jump[piece].last_x;
	int Ly = can_jump[piece].last_y;
	int ox = can_jump[piece].orignal_x;
	int oy = can_jump[piece].orignal_y;
	int num = 1;
	int sum;

	for (int i = 0; i < 100; i++)
	{
		if ((can_jump[i].x == Lx && can_jump[i].y == Ly)
			&& (can_jump[i].orignal_x == ox && can_jump[i].orignal_y == oy))
		{
			sum = choice(i, num + 1);
			M[num][0] = x;
			M[num][1] = y;
			cout << "->(" << x << "," << y << ")" << endl << sum << endl;
			break;
		}
	}
	if (can_jump[piece].last_x == can_jump[piece].orignal_x &&
		can_jump[piece].last_y == can_jump[piece].orignal_y) {
		M[num + 1][0] = ox;
		M[num + 1][1] = oy;
		M[num][0] = x;
		M[num][1] = y;
		cout << "(" << M[num + 1][0] << "," << M[num + 1][1] << ")";
		cout << "->(" << M[num][0] << "," << M[num][1] << ")" << endl << num << endl;
		sum = num;
	}
	output_step(sum);
}
int choice(int piece, int num) {
	int x = can_jump[piece].x;
	int y = can_jump[piece].y;
	int Lx = can_jump[piece].last_x;
	int Ly = can_jump[piece].last_y;
	int ox = can_jump[piece].orignal_x;
	int oy = can_jump[piece].orignal_y;
	int sum;
	for (int i = 0; i < 100; i++)
	{
		if ((can_jump[i].x == Lx && can_jump[i].y == Ly)
			&& (can_jump[i].orignal_x == ox && can_jump[i].orignal_y == oy))
		{
			sum = choice(i, num + 1);
			M[num][0] = x;
			M[num][1] = y;
			cout << "->(" << x << "," << y << ")";
			return sum;
			break;
		}
	}
	if (can_jump[piece].last_x == can_jump[piece].orignal_x &&
		can_jump[piece].last_y == can_jump[piece].orignal_y) {
		M[num + 1][0] = ox;
		M[num + 1][1] = oy;
		cout << "(" << ox << "," << oy << ")";
		M[num][0] = x;
		M[num][1] = y;
		cout << "->(" << M[num][0] << "," << M[num][1] << ")";
		return num;
	}
}

int score_cal()
{
	double max = 0.0;
	int max_i = 0;
	for (int i = 0; i < cjnum; i++)
	{
		cout << can_jump[i].endscore << endl;
		can_jump[i].endscore = (((16 * sin(60 * 3.14159 / 180.)) - can_jump[i].endscore) / 16.);
		can_jump[i].movementscore /= 4;
		can_jump[i].startscore = ((16 - can_jump[i].startscore) / 16) * 3.5;
		can_jump[i].sumscore = (can_jump[i].endscore + can_jump[i].startscore)*can_jump[i].movementscore;
		if (can_jump[i].sumscore >= max) {
			max = can_jump[i].sumscore;
			max_i = i;
		}
	}
	return max_i;
}

int movement1(int i, int j)
{
	int score;
	if (color == 2) {
		if (((i == 1) && (j == -1)) || ((i == 1) && (j == 0))) {
			score = 1;
		}
		if (((i == 0) && (j == 1)) || ((i == 0) && (j == -1))) {
			score = 0;
		}
		if (((i == -1) && (j == 1)) || ((i == -1) && (j == 0))) {
			score = -1;
		}
	}
	if (color == 3) {
		if (((i == -1) && (j == 1)) || ((i == 0) && (j == 1))) {
			score = 1;
		}
		if (((i == -1) && (j == 0)) || ((i == 1) && (j == 0))) {
			score = 0;
		}
		if (((i == 0) && (j == -1)) || ((i == 1) && (j == -1))) {
			score = -1;
		}
	}
	if (color == 4) {
		if (((i == -1) && (j == 0)) || ((i == 0) && (j == -1))) {
			score = 1;
		}
		if (((i == -1) && (j == 1)) || ((i == 1) && (j == -1))) {
			score = 0;
		}
		if (((i == 1) && (j == 0)) || ((i == 0) && (j == 1))) {
			score = -1;
		}
	}

	return score;
}
void output_step(int sum)
{
	ofstream step;
	step.open("1072001.txt");
	step << sum << endl;
	for (int i = sum + 1; i > 0; i--) {
		step << M[i][0] << " " << M[i][1];
		step << endl;
	}
	step.close();
}
