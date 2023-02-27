#include <stdio.h>
#include <graphics.h>  //ͼ�ο�easyx
#include <math.h>
#include <time.h>

#define R 100
struct love
{
	int height; // ���
	double angle;  // ����
	double  r;  // �뾶
	double curR; // ���ļ�ľ���
	int x;  // x����
	int y;  // y����
};

struct love mylove[20*20]; //�������ĳ���

// ����������Ϊwebdingsʱ  ���̰�����Ӧ�����ַ�



//int test(void) {
//	initgraph(1000, 600);
//
//	//��ѧ  ���ι�ʽ
//	for (double a = 0; a <= 3.14 * 2; a = a + 0.1)
//	{
//		double r = sin(a)* sqrt(fabs(cos(a))) / (sin(a) + 1.4142) - 2 * sin(a) + 2;
//		
//		int x = R * r * cos(a) + 400;
//		int y = -R * r * sin(a) + 100;
//		//��һ����
//		char str[8];
//		setbkmode(TRANSPARENT); // �������  ����Ϊ����
//		//sprintf_s(str, sizeof(str), "%.1f", a);
//		//outtextxy(x, y, str);  // �޸�Ϊ���ֽ��ַ���
//		
//		settextcolor(RED); //����������ɫ
//		settextstyle(40, 0, "webdings");//�����������  ��С
//		outtextxy(x, y, "Y");
//	}
//	system("pause");
//	return 0;
//}


void init(void) {
	initgraph(700, 600);
	//��������ȫ������Ϊ0
	memset(mylove, 0, sizeof(struct love)*400);
	srand(time(NULL));
}

// ����Ƕ�
void getRandAngles(int buf[], int count) {
	
	for (int i = 0; i < count; i++)
	{
		int  M = 314 * 2 * 2;
		// �ж��Ƿ����ظ��������
		int tmp = 0;
		int j = 0;
		while (1) {
			tmp = rand() % M; // �����������
			for (j = 0; j < i && buf[j] != tmp; j++);
			if(j >= i) break;
		}
		buf[i] = tmp;
	}
}
//�����µ�����
void addNewHeart() {
	// �ڰ��ĳ����ҵ�û��ʹ�õ�
	int k = 0;
	for (k = 0; k < 400 && mylove[k].curR>0; k++);
	// ѭ��������  kָ���һ��û��ʹ�ù�����

    //��Ҫ׼��20������ĽǶ�
	
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

//ˢ�´���
void updateWindow() {
	BeginBatchDraw();
	cleardevice();   //�����ǰ����

	settextcolor(RED);
	for (int i = 0; i < 400; i++)
	{
		if (mylove[i].curR == 0) continue;
		settextstyle(mylove[i].height + 20, 0, "Webdings");
		setbkmode(TRANSPARENT);  //�ַ�����͸��
		outtextxy(mylove[i].x + 10, mylove[i].y - 80, "Y");   //movelove[i].x��10�� movelove[i].y��80
		//��Ϊ�˿�������ڴ��ڵ��м�
	}

	EndBatchDraw();
}

//�޸�����
void reviseHeart() {
	for (int i = 0; i < 400; i++)
	{
		if (mylove[i].curR == 0) continue;
		mylove[i].curR++;  //�ַ�λ��������

		//һ�������20�Ű��ģ�����20�Σ�movelove[i].cuR��ʼֵΪ100����������120�������ع����״̬
		if (mylove[i].curR > 120)
		{
			memset(&mylove[i], 0, sizeof(struct love));
		}
		mylove[i].height++;   //�ַ����
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
