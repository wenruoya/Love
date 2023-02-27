#include <stdio.h>
#include <graphics.h>  //图形库easyx
#include <math.h>
#include <time.h>

#define R 100
struct love
{
	int height; // 宽度
	double angle;  // 弧度
	double  r;  // 半径
	double curR; // 离心尖的距离
	int x;  // x坐标
	int y;  // y坐标
};

struct love mylove[20*20]; //心数量的池子

// 当字体设置为webdings时  键盘按键对应特殊字符



//int test(void) {
//	initgraph(1000, 600);
//
//	//数学  心形公式
//	for (double a = 0; a <= 3.14 * 2; a = a + 0.1)
//	{
//		double r = sin(a)* sqrt(fabs(cos(a))) / (sin(a) + 1.4142) - 2 * sin(a) + 2;
//		
//		int x = R * r * cos(a) + 400;
//		int y = -R * r * sin(a) + 100;
//		//画一个点
//		char str[8];
//		setbkmode(TRANSPARENT); // 输出文字  背景为心形
//		//sprintf_s(str, sizeof(str), "%.1f", a);
//		//outtextxy(x, y, str);  // 修改为多字节字符集
//		
//		settextcolor(RED); //设置字体颜色
//		settextstyle(40, 0, "webdings");//设置输出字体  大小
//		outtextxy(x, y, "Y");
//	}
//	system("pause");
//	return 0;
//}


void init(void) {
	initgraph(700, 600);
	//整个数组全部设置为0
	memset(mylove, 0, sizeof(struct love)*400);
	srand(time(NULL));
}

// 随机角度
void getRandAngles(int buf[], int count) {
	
	for (int i = 0; i < count; i++)
	{
		int  M = 314 * 2 * 2;
		// 判断是否有重复的随机数
		int tmp = 0;
		int j = 0;
		while (1) {
			tmp = rand() % M; // 配置随机种子
			for (j = 0; j < i && buf[j] != tmp; j++);
			if(j >= i) break;
		}
		buf[i] = tmp;
	}
}
//增加新的心形
void addNewHeart() {
	// 在爱心池中找到没有使用的
	int k = 0;
	for (k = 0; k < 400 && mylove[k].curR>0; k++);
	// 循环结束后  k指向第一个没有使用过的心

    //需要准备20个随机的角度
	
	for (int i = k; i < k+20; i++)
	{
		int angles[20];
		getRandAngles(angles, 20);
		mylove[i].angle = angles[i - k] * 0.01;
		mylove[i].r = (sin(mylove[i].angle) * sqrt(fabs(cos(mylove[i].angle)))) / (sin(mylove[i].angle) + 1.4142)
			- 2 * sin(mylove[i].angle) + 2;
		mylove[i].curR = R;
		mylove[i].height = 0;
		mylove[i].x = mylove[i].curR * mylove[i].r * mylove[i].angle + 360;
		mylove[i].y = -mylove[i].curR * mylove[i].r * mylove[i].angle + 170;
	}
}

//刷新窗口
void updateWindow() {
	BeginBatchDraw();
	cleardevice();   //清除当前窗口

	settextcolor(RED);
	for (int i = 0; i < 400; i++)
	{
		if (mylove[i].curR == 0) continue;
		settextstyle(mylove[i].height + 20, 0, "Webdings");
		setbkmode(TRANSPARENT);  //字符背景透明
		outtextxy(mylove[i].x + 10, mylove[i].y - 80, "Y");   //movelove[i].x加10和 movelove[i].y减80
		//是为了控制输出在窗口的中间
	}

	EndBatchDraw();
}

//修改心形
void reviseHeart() {
	for (int i = 0; i < 400; i++)
	{
		if (mylove[i].curR == 0) continue;
		mylove[i].curR++;  //字符位置往外移

		//一次随机创20颗爱心，创建20次，movelove[i].cuR初始值为100，当它大于120，让它回归最初状态
		if (mylove[i].curR > 120)
		{
			memset(&mylove[i], 0, sizeof(struct love));
		}
		mylove[i].height++;   //字符变大
		mylove[i].x = mylove[i].curR * mylove[i].r * cos(mylove[i].angle) + 360;
		mylove[i].y = -mylove[i].curR * mylove[i].r * sin(mylove[i].angle) + 170;

	}
}

int main(void) {
	init();
	while(1){
		addNewHeart();
		updateWindow();
		reviseHeart();

		Sleep(30);
	}
}
