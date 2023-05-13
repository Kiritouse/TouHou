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
	int isExist;//判断子弹是否需要删除
	BulletNode* pnext;
};
//补充一下，链表实际上就相当于一个二维数组
//一维指针相当于指向某一个节点，二维指针就相当于指向某一节点中的某一个数据
void update_Bullet(EnemyNode** pp_Enemy_List_Head, BulletNode** pp_Player_Bullet_List_Head, int command, int frameBuffer, int vx, int vy, int hitpoint);
void Bullet_listPushBack(BulletNode** pp_Player_Bullet_List_Node_Head, BulletNode* newNode);
BulletNode* creatPlayerBullet(int vx, int vy, int hitpoint);
BulletNode* creatPlayerBullet(int x, int y, int vx, int vy, int hitpoint);
void update_BulletImage(BulletNode** pp_Player_Bullet_List);
extern int cntBullet;//统计场上有多少颗子弹