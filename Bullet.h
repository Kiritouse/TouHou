#pragma once
#include "Enemy.h"
#define NORMAL  0
#define UPDATE 1 
#define WIDTH_BULLET0 12
#define HEIGHT_BULLET0 44

struct BulletNode
{
	int x, y;
	int vx, vy;
	int hitpoint;
	int isExist;//�ж��ӵ��Ƿ���Ҫɾ��
	BulletNode* pnext;
};
//����һ�£�����ʵ���Ͼ��൱��һ����ά����
//һάָ���൱��ָ��ĳһ���ڵ㣬��άָ����൱��ָ��ĳһ�ڵ��е�ĳһ������
void update_Bullet(EnemyNode** pp_Enemy_List_Head, BulletNode** pp_Player_Bullet_List_Head, int command, int frameBuffer, int vx, int vy, int hitpoint);
void Bullet_listPushBack(BulletNode** pp_Player_Bullet_List_Node_Head, BulletNode* newNode);
BulletNode* creatPlayerBullet(int vx, int vy, int hitpoint);
BulletNode* creatPlayerBullet(int x, int y, int vx, int vy, int hitpoint);
void update_BulletImage(BulletNode** pp_Player_Bullet_List);
extern int cntBullet;//ͳ�Ƴ����ж��ٿ��ӵ�