//https://www.bilibili.com/video/BV1GY4y1p78Z/?spm_id_from=333.337.search-card.all.click&vd_source=0c68653124dc72626a2126b5382d1eb6
//
//map[y][x]  y��һ�� x��һ��


#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#include <print>
#pragma comment(lib,"winmm.lib")

#define  MAX_GRID 4 //������
#define GRID_WIDTH 100 //���ӿ��
#define INTERVAL 15 //���Ӽ��

//����ö������ ������¼������ɫ
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
//������һ��Color���͵�����arr�����ڴ洢��Щ��ɫֵ
Color arr[13] = { zero,twoto1 ,twoto2,twoto3,twoto4,twoto5,twoto6,twoto7,twoto8,twoto9,twoto10,twoto11,back };

int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];//�������ֵ
bool flag = false;


POINT POS[MAX_GRID][MAX_GRID];//������ӵ�����
int torf() {//��ʼ������ֵ���������ֵ
	if (rand() % 10 == 1) {
		return 4;
	}
	else
	{
		return 2;
	}
}
void whereumber() {//��ʼ�� �����
	while (true)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0) {  //�ҵ�Ϊ0�ĸ���
			map[x][y] = torf();
			break;
		}
		
	}
}

void gameinit() {   //׼������ ��ʼ��
	srand(GetTickCount());//׼���������������

	for (int i = 0; i < MAX_GRID; i++) {//��ø�������

		for (int j = 0; j < MAX_GRID; j++) {

			POS[i][j].x = j * GRID_WIDTH + INTERVAL * (j + 1);  //������*����+�����*����
			POS[i][j].y = i * GRID_WIDTH + INTERVAL * (i + 1);  //ͬ��
			
		}
	}
	//��ʼ������ֵ���������4��ֵ 
	whereumber();
	whereumber();
}

//map[y][x]  y��һ�� x��һ��

//�����ƶ�
void up() {
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0; //��ʼ������Ϊ0  
		for (int j = 1; j < MAX_GRID; j++) {
			if (map[j][i] != 0) {  //����0ʱ temp���� map[temp][i]��map[j][i]��ǰ��
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
//�����ƶ�
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
//�����ƶ�
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
//�����ƶ�
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
				flag = true; //�����ж��Ƿ��кϲ�
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
				MessageBox(NULL, TEXT("���ʤ��"), TEXT("����"), MB_OK);
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
		MessageBox(NULL, TEXT("��Ϸʧ��"), TEXT("����"), MB_OK);
	}

	for (int i = 0; i < MAX_GRID; i++) {
		for (int j = 0; j < MAX_GRID; j++) {
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
	printf("");
}

void ifflag() {//���кϲ�ʱ��Ϊ��������µ���������ж�ֵ��Ϊ��
	if (flag) {
		whereumber();
		flag = false;
		
	}
	
}


//�����ƶ�
void remove() {
	char key = _getch();//��ȡ�������������Ϣ
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


void GAMEB() {//����ͼ��
	for (int i = 0; i < MAX_GRID; i++) {
		for (int j = 0; j < MAX_GRID; j++) {
			for (int q = 0; q < 12; q++) {
				if (map[i][j] == num[q]) { //��������Ӧ����ȡ�±�
					setfillcolor(arr[q]); //�����±��ȡ��ɫ
					solidrectangle(POS[i][j].x, POS[i][j].y, POS[i][j].x + GRID_WIDTH, POS[i][j].y + GRID_WIDTH); 
					//�滭���ӵı߿� �������� x ���꣬���ζ��� y ���꣬�����Ҳ� x ���꣬���εײ� y ���꣩
					if (map[i][j] != 0) {
						char number[5] = " ";//���ֶ���
						settextstyle(50, 0, "����"); //������ʽ
						setbkmode(TRANSPARENT); //���ֱ���͸��
						sprintf(number, "%d", num[q]);//�������룬�����±��ȡֵ
						int temp_x = textwidth(number);//������
						int temp_y = textheight(number);//����߶�
						temp_x = GRID_WIDTH / 2 - temp_x / 2;//��ȡ�����ڸ����ڵ���߽� ���ӵĿ�ȵ�һ���ȥ�����ȵ�һ��
						temp_y = GRID_WIDTH / 2 - temp_y / 2; // ��ȡ�����ڸ����ڵ��ϱ߽� ���ӵĸ߶ȣ��Ϳ��һ������һ���ȥ�����ȵ�һ��
						outtextxy(POS[i][j].x+ temp_x, POS[i][j].y+ temp_y, number);//ָ��λ������ַ�������߽磬�ϱ߽磬���ݣ�
					}
				}
			}
			//fillrectangle(j* GRID_WIDTH+ (j+1)*INTERVAL,i* GRID_WIDTH +(i+1)* INTERVAL,j* GRID_WIDTH +(j+1)* INTERVAL + GRID_WIDTH,i* GRID_WIDTH +(i+1)* INTERVAL + GRID_WIDTH);
			//���ƾ���
		}
	}
}
void music() {
	mciSendString("open 1.mp3 alias bgm", NULL, NULL, NULL); //mp3 wav ��ʽ �򿪸���
	mciSendString("play bgm", NULL, NULL, NULL);//���Ÿ���
}


int main() {
	music();
	initgraph(MAX_GRID * GRID_WIDTH +5* INTERVAL, MAX_GRID * GRID_WIDTH +5* INTERVAL);//���ƽ���
	//184, 175, 160  ����
	//205, 193, 183  ����
	setbkcolor(RGB(184, 175, 160));//����������ɫ
	cleardevice();//ʹ�õ�ǰ����ɫ��ջ�ͼ�豸
	gameinit();//��ʼ��׼������
	while (1)//����ѭ��
	{
		
		GAMEB();//����ͼ��
		remove();//��ֵ�ƶ�
		ifflag();//��������
		win();//
	}
	

	//getchar();//�����û��Ӽ��������һ���ַ�
	closegraph();
	return 0;
}



