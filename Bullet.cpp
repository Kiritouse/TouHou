#include "Bullet.h"
#include "Player.h"
#include "Map.h"
#include "Draw.h"
#include <conio.h>
#include "LoadResources.h"
#include <cstddef>
#include <graphics.h>
#include <Windows.h>
#include "Operation.h"
#include "ParticleManager.h"
#include "DataManager.h"
#include "Music.h"
int cntBullet = 0;
//创建玩家
BulletNode* creatPlayerBullet(int vx, int vy, int hitpoint) {
	BulletNode* p = new BulletNode;
	p->x = Struct_PlayerPosition.x + WIDTH_PLAYER / 2 - 8;//飞机头部的位置
	p->y = Struct_PlayerPosition.y;
	p->vx = vx;
	p->vy = vy;//速度
	p->hitpoint = hitpoint;
	p->isExist = 1;
	p->pnext = NULL;
	return p;
}
BulletNode* creatPlayerBullet(int x, int y, int vx, int vy, int hitpoint) {
	BulletNode* p = new BulletNode;
	p->x = x;
	p->y = y;
	p->vx = vx;
	p->vy = vy;//速度
	p->hitpoint = hitpoint;
	p->isExist = 1;
	p->pnext = NULL;
	return p;
}
void Bullet_listPushBack(BulletNode** pp_Player_Bullet_List_Node_Head, BulletNode* newNode) {
	if (*pp_Player_Bullet_List_Node_Head == NULL)//如果链表为空，那么新增的节点就是第一个
	{
		*pp_Player_Bullet_List_Node_Head = newNode;
		return;
	}
	BulletNode* cur = *pp_Player_Bullet_List_Node_Head;
	while (cur->pnext != NULL)//找到最后一个节点
	{
		cur = cur->pnext;
	}
	cur->pnext = newNode;//插入新的节点
}

void update_BulletPosition(BulletNode** pp_Player_Bullet_List_Node_Head, int command, int frameBuffer, int vx, int vy, int hitpoint)
{
	if (((command & CMD_FIRE) && ((frameBuffer & 1) == 0))) {
		Bullet_listPushBack(pp_Player_Bullet_List_Node_Head, creatPlayerBullet(vx, vy, hitpoint));
		cntBullet++;
		playsound(1, 0);

	}//处理射击操作

	if (*pp_Player_Bullet_List_Node_Head == NULL)//如果链表为空，那么新增的节点就是第一个
		return;
	BulletNode* cur = *pp_Player_Bullet_List_Node_Head;//curret指向第一个节点
	while (cur != NULL)//遍历链表
	{
		cur->x += cur->vx;
		cur->y += cur->vy;
		//判断子弹是否离开视野
		if ((cur->y < -20) || (cur->y > HEIGHT_MAP) || (cur->x > WIDTH_MAP) || (cur->x < -20)) {
			cur->isExist = 0;
			cntBullet--;
		}
		cur = cur->pnext;//指向下一个节点
	}
}
void listRemoveNode_Bullet(BulletNode** pp_Player_Bullet_List_Node_Head)
{
	if (*pp_Player_Bullet_List_Node_Head == NULL)//如果链表为空，就没有可删除的节点了
		return;
	BulletNode* curP = *pp_Player_Bullet_List_Node_Head;//curret先指向第一个节点
	BulletNode* prevP = NULL;  //previous指向上一个节点的指针
	while (curP != NULL)//遍历链表
	{
		if (curP->isExist == 0)
		{
			if (*pp_Player_Bullet_List_Node_Head == curP)
			{
				*pp_Player_Bullet_List_Node_Head = curP->pnext;
				free(curP);
				curP = *pp_Player_Bullet_List_Node_Head;
			}
			else
			{
				prevP->pnext = curP->pnext;
				free(curP);
				curP = prevP;
			}
		}
		else
		{
			prevP = curP;
			curP = curP->pnext;
		}
	}
}

void update_BulletImage(BulletNode** pp_Player_Bullet_List) {

	for (BulletNode* cur = *pp_Player_Bullet_List; cur != NULL; cur = cur->pnext)
	{

		transparentimage(NULL, cur->x, cur->y, WIDTH_BULLET0, HEIGHT_BULLET0,
			0, 0, WIDTH_BULLET0, HEIGHT_BULLET0, &normalBullets, 150);
	}
}
void bulletCrashEnemyCheck(EnemyNode** pp_Enemy_List_Head, BulletNode** pp_Player_Bullet_List_Head) {
	BulletNode* curBullet = *pp_Player_Bullet_List_Head;
	while (curBullet != NULL) {
		EnemyNode* curEnemy = *pp_Enemy_List_Head;
		while (curEnemy != NULL) {
			//如果子弹在敌人的图片中
			int WIDTH, HEIGHT;
			if (curEnemy->type_enemy0 == 1) {
				WIDTH = WIDTH_ENEMY0;
				HEIGHT = HEIGHT_ENEMY0;
			}
			else if (curEnemy->type_enemy1 == 1) {
				WIDTH = WIDTH_ENEMY1;
				HEIGHT = HEIGHT_ENEMY1;
			}
			else return;
			if ((curBullet->x > curEnemy->x) && (curBullet->x < (curEnemy->x + WIDTH))) {
				if ((curBullet->y > curEnemy->y) && (curBullet->y < (curEnemy->y + HEIGHT))) {
					//std::cout << curEnemy->health << std::endl;
					if (curEnemy->health <= 0) {
						curEnemy->isExist = 0;
						user.score++;
						playsound(2, 0);
						createFireworks(&curEnemy);
					}
					else {
						//std::cout << curBullet->hitpoint << std::endl;
						curEnemy->health -= curBullet->hitpoint;
					}
					curBullet->isExist = 0;


				}
			}

			curEnemy = curEnemy->pnext;
		}


		curBullet = curBullet->pnext;
	}
}
void update_Bullet(EnemyNode** pp_Enemy_List_Head, BulletNode** pp_Player_Bullet_List_Head, int command, int frameBuffer, int vx, int vy, int hitpoint) {
	update_BulletPosition(pp_Player_Bullet_List_Head, command, frameBuffer, vx, vy, hitpoint);
	bulletCrashEnemyCheck(pp_Enemy_List_Head, pp_Player_Bullet_List_Head);
	listRemoveNode_Bullet(pp_Player_Bullet_List_Head);//超出视野或者击中飞行器的子弹删除掉

}




