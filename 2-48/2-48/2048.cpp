//https://www.bilibili.com/video/BV1GY4y1p78Z/?spm_id_from=333.337.search-card.all.click&vd_source=0c68653124dc72626a2126b5382d1eb6
//
//map[y][x]  y是一竖 x是一横


#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#include <print>
#pragma comment(lib,"winmm.lib")

#define  MAX_GRID 4 //格子数
#define GRID_WIDTH 100 //格子宽度
#define INTERVAL 15 //格子间隔

//定义枚举类型 用来收录格子颜色
enum Color {
	zero = RGB(105, 193, 180),
	twoto1 = RGB(238, 228, 218),
	twoto2 = RGB(237, 224, 200),
	twoto3 = RGB(242, 177, 121),
	twoto4 = RGB(245, 149, 99),
	twoto5 = RGB(246, 124, 95),
	twoto6 = RGB(246, 94, 59),
	twoto7 = RGB(242, 177, 121),
	twoto8 = RGB(237, 204, 97),
	twoto9 = RGB(255, 0, 128),
	twoto10 = RGB(145, 0, 72),
	twoto11 = RGB(242, 17, 158),
	back = RGB(187, 173, 160)
};
//定义了一个Color类型的数组arr，用于存储这些颜色值
Color arr[13] = { zero,twoto1 ,twoto2,twoto3,twoto4,twoto5,twoto6,twoto7,twoto8,twoto9,twoto10,twoto11,back };

int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];//定义格子值
bool flag = false;


POINT POS[MAX_GRID][MAX_GRID];//定义格子的坐标
int torf() {//初始化格子值，随机产生值
	if (rand() % 10 == 1) {
		return 4;
	}
	else
	{
		return 2;
	}
}
void whereumber() {//初始化 随机数
	while (true)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0) {  //找到为0的格子
			map[x][y] = torf();
			break;
		}
		
	}
}

void gameinit() {   //准备工作 初始化
	srand(GetTickCount());//准备设置随机数种子

	for (int i = 0; i < MAX_GRID; i++) {//获得格子坐标

		for (int j = 0; j < MAX_GRID; j++) {

			POS[i][j].x = j * GRID_WIDTH + INTERVAL * (j + 1);  //格子数*个数+间隔数*个数
			POS[i][j].y = i * GRID_WIDTH + INTERVAL * (i + 1);  //同理
			
		}
	}
	//初始化格子值，随机产生4个值 
	whereumber();
	whereumber();
}

//map[y][x]  y是一竖 x是一横

//向上移动
void up() {
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0; //初始化定义为0  
		for (int j = 1; j < MAX_GRID; j++) {
			if (map[j][i] != 0) {  //等于0时 temp不变 map[temp][i]在map[j][i]的前面
				if (map[temp][i] == 0) {
					map[temp][i] = map[j][i];
					map[j][i] = 0;
				}else if (map[temp][i] == map[j][i]) {
					map[temp][i] *= 2;
					map[j][i] = 0;
				}
				else {
					map[temp + 1][i] = map[j][i];
					if (temp+1!=j) {
						map[j][i] = 0;
					}
				}
				temp++;
				flag = true;
			 }
		}
	}
}

//      0     1       2      3
// 0 [0][0] [0][1] [0][2] [0][3]
// 1 [1][0] [1][1] [1][2] [1][3]
// 2 [2][0] [2][1] [2][2] [2][3]
// 3 [3][0] [3][1] [3][2] [3][3]
//向下移动
void down() {
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID-1;  //3
		for (int j = MAX_GRID-2; j >=0; j--) {
			if (map[j][i] != 0) {
				if (map[temp][i] == 0) {
					map[temp][i] = map[j][i];
					map[j][i] = 0;
				}
				else if (map[temp][i] == map[j][i]) {
					map[temp][i] *= 2;
					map[j][i] = 0;
				}
				else {
					map[temp - 1][i] = map[j][i];
					if (temp - 1 != j) {
						map[j][i] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
}

//      0     1       2      3
// 0 [0][0] [0][1] [0][2] [0][3]
// 1 [1][0] [1][1] [1][2] [1][3]
// 2 [2][0] [2][1] [2][2] [2][3]
// 3 [3][0] [3][1] [3][2] [3][3]
//向左移动
void lift() {
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int j = 1; j < MAX_GRID; j++) {
			if (map[i][j] != 0) {
				if (map[i][temp] == 0) {
					map[i][temp] = map[i][j];
					map[i][j] = 0;
				}
				else if (map[i][temp] == map[i][j]) {
					map[i][temp] *= 2;
					map[i][j] = 0;
				}
				else {
					map[i][temp+1] = map[i][j];
					if (temp + 1 != j) {
						map[i][j] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
}

//      0     1       2      3
// 0 [0][0] [0][1] [0][2] [0][3]
// 1 [1][0] [1][1] [1][2] [1][3]
// 2 [2][0] [2][1] [2][2] [2][3]
// 3 [3][0] [3][1] [3][2] [3][3]
//向右移动
void right() {
	for (int i = 0; i < MAX_GRID; i++) {
		int temp = MAX_GRID - 1; //3
		for (int j = MAX_GRID - 2; j >= 0; j--) {  //2
			if (map[i][j] != 0) {
				if (map[i][temp] == 0) {
					map[i][temp] = map[i][j];
					map[i][j] = 0;
				}
				else if (map[i][temp] == map[i][j]) {
					map[i][temp] *= 2;
					map[i][j] = 0;
				}
				else {
					
					map[i][temp - 1] = map[i][j];
					if (temp - 1 != j) {
						map[i][j] = 0;
					}
				}
				temp--;
				flag = true; //用于判断是否有合并
			}
		}
	}
}

void win() {
	int n = 0;
	for (int i = 0; i < MAX_GRID-1; i++) {
		for (int j = 0; j < MAX_GRID-1; j++) {
			
			
			if (map[i][j] == map[i + 1][j] ) {
				n = 1;
			}
			if (map[i][j] == map[i ][j+1]) {
				n = 1;
			}
			
		}
	}
//      0     1       2      3
// 0 [0][0] [0][1] [0][2] [0][3]
// 1 [1][0] [1][1] [1][2] [1][3]
// 2 [2][0] [2][1] [2][2] [2][3]
// 3 [3][0] [3][1] [3][2] [3][3]
	for (int i = 0; i < MAX_GRID ; i++) {
		for (int j = 0; j < MAX_GRID ; j++) {
			if (map[i][j] == 2048) {
				MessageBox(NULL, TEXT("获得胜利"), TEXT("弹窗"), MB_OK);
				exit(0);
			}
			if (i == 3) {
				if (map[i][j] == map[i][j + 1]) {
					n = 1;
				}
			}
			if (j == 3) {
				if (map[i][j] == map[i + 1][j]) {
					n = 1;
				}
			}
			if (map[i][j] == 0) {
				n = 1;
			}
		}
	}
	if (n == 0) {
		MessageBox(NULL, TEXT("游戏失败"), TEXT("弹窗"), MB_OK);
	}

	for (int i = 0; i < MAX_GRID; i++) {
		for (int j = 0; j < MAX_GRID; j++) {
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
	printf("");
}

void ifflag() {//当有合并时，为格子添加新的随机数，判断值改为假
	if (flag) {
		whereumber();
		flag = false;
		
	}
	
}


//格子移动
void remove() {
	char key = _getch();//获取键盘上输入的信息
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		up();
		break;

	case 's':
	case 'S':
	case 80:
		down();
		break;

	case 'd':
	case 'D':
	case 77:
		right();
		break;

	case 'a':
	case 'A':
	case 75:
		lift();
		break;
	
	}
}


void GAMEB() {//绘制图像
	for (int i = 0; i < MAX_GRID; i++) {
		for (int j = 0; j < MAX_GRID; j++) {
			for (int q = 0; q < 12; q++) {
				if (map[i][j] == num[q]) { //格子数对应，获取下标
					setfillcolor(arr[q]); //根据下标获取颜色
					solidrectangle(POS[i][j].x, POS[i][j].y, POS[i][j].x + GRID_WIDTH, POS[i][j].y + GRID_WIDTH); 
					//绘画格子的边框 （矩形左部 x 坐标，矩形顶部 y 坐标，矩形右部 x 坐标，矩形底部 y 坐标）
					if (map[i][j] != 0) {
						char number[5] = " ";//文字定义
						settextstyle(50, 0, "隶书"); //文字样式
						setbkmode(TRANSPARENT); //文字背景透明
						sprintf(number, "%d", num[q]);//文字输入，跟据下标获取值
						int temp_x = textwidth(number);//字体宽度
						int temp_y = textheight(number);//字体高度
						temp_x = GRID_WIDTH / 2 - temp_x / 2;//获取字体在格子内的左边界 格子的宽度的一半减去字体宽度的一半
						temp_y = GRID_WIDTH / 2 - temp_y / 2; // 获取字体在格子内的上边界 格子的高度（和宽度一样）的一半减去字体宽度的一半
						outtextxy(POS[i][j].x+ temp_x, POS[i][j].y+ temp_y, number);//指定位置输出字符串（左边界，上边界，内容）
					}
				}
			}
			//fillrectangle(j* GRID_WIDTH+ (j+1)*INTERVAL,i* GRID_WIDTH +(i+1)* INTERVAL,j* GRID_WIDTH +(j+1)* INTERVAL + GRID_WIDTH,i* GRID_WIDTH +(i+1)* INTERVAL + GRID_WIDTH);
			//绘制矩形
		}
	}
}
void music() {
	mciSendString("open 1.mp3 alias bgm", NULL, NULL, NULL); //mp3 wav 格式 打开歌曲
	mciSendString("play bgm", NULL, NULL, NULL);//播放歌曲
}


int main() {
	music();
	initgraph(MAX_GRID * GRID_WIDTH +5* INTERVAL, MAX_GRID * GRID_WIDTH +5* INTERVAL);//绘制界面
	//184, 175, 160  背景
	//205, 193, 183  格子
	setbkcolor(RGB(184, 175, 160));//制作背景颜色
	cleardevice();//使用当前背景色清空绘图设备
	gameinit();//初始化准备工作
	while (1)//无线循环
	{
		
		GAMEB();//绘制图像
		remove();//数值移动
		ifflag();//添加随机数
		win();//
	}
	

	//getchar();//接收用户从键盘输入的一个字符
	closegraph();
	return 0;
}



