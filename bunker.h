#pragma once
//����ұ����е�ʱ��Ż����
#define WIDTH_BUNKER 59
#define HEIGHT_BUNKER 60
struct  Bunker
{
	//��ײ��ı߽�
	int xl, xr;
	int yu, yd;
	int isExist;
	int f_create;//���ܳ����˶���֡
	int cnt;//�ܳ�������
	Bunker(int xl, int xr, int yu, int yd, int f_create, int isExist, int cnt);
};
void update_CrashBunker();
void drawBunker();
extern Bunker* Struct_bunker;
