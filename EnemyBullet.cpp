#include <stdlib.h>
#include "EnemyBullet.h"
#include "Map.h"
#include "Draw.h"
#include "LoadResources.h"
#include "bunker.h"
#include "DataManager.h"
#define DEF_TYPE_ENEMY0 0//识别敌人的标识符
#define DEF_TYPE_ENEMY1 1
#define WIDTH_ENEMYBULLET0 22
#define HEIGHT_ENEMYBULLET0 21
//负责敌人子弹的初始化
EnemyBulletNode* createEnemyBulletNode(EnemyNode** pp_curEnemy, float vx, float vy, int level, int hitpoint) {
	EnemyBulletNode* newEnemyBulletNode = new EnemyBulletNode;
	newEnemyBulletNode->x = (*pp_curEnemy)->x + WIDTH_ENEMY0 / 2 - 8;
	newEnemyBulletNode->y = (*pp_curEnemy)->y + HEIGHT_ENEMY0 / 2 - 10;
	newEnemyBulletNode->vx = vx;
	newEnemyBulletNode->vy = vy;
	newEnemyBulletNode->level = level;
	newEnemyBulletNode->hitpoint = hitpoint;
	newEnemyBulletNode->isExist = 1;
	newEnemyBulletNode->pnext = NULL;
	return newEnemyBulletNode;
}
void EnemyBulletListPushBack(EnemyBulletNode** pp_Enemy_Bullet_List_Head, EnemyBulletNode* newNode) {
	if (*pp_Enemy_Bullet_List_Head == NULL) {
		*pp_Enemy_Bullet_List_Head = newNode;
		return;
	}
	EnemyBulletNode* cur = *pp_Enemy_Bullet_List_Head;
	while (cur->pnext != NULL) {
		cur = cur->pnext;
	}
	cur->pnext = newNode;
}
void update_EnemyBulletPosition(EnemyNode** pp_Enemy_List_Head, EnemyBulletNode** pp_Enemy_Bullet_List_Head, float vx, float vy, int level, int hitpoint, int framebuffer) {
	EnemyNode* curEnemy = *pp_Enemy_List_Head;
	if (E_TYPE_PlayerState == OBJ_Player->Invulnerable) {
		if (framebuffer - Struct_bunker->f_create >= 50) {
			Struct_bunker->isExist = 0;//删除护盾
			E_TYPE_PlayerState = OBJ_Player->Live;//改变角色状态
		}
	}
	while (curEnemy != NULL) {
		if (framebuffer - curEnemy->f_create == curEnemy->fire_on) {
			EnemyBulletListPushBack(pp_Enemy_Bullet_List_Head, createEnemyBulletNode(&curEnemy, vx, vy, level, hitpoint));
			curEnemy->f_create = framebuffer;;
		}
		curEnemy = curEnemy->pnext;
	}
	EnemyBulletNode* curEnemyBullet = *pp_Enemy_Bullet_List_Head;
	while (curEnemyBullet != NULL) {
		curEnemyBullet->x += curEnemyBullet->vx;
		curEnemyBullet->y += curEnemyBullet->vy;
		//	判断是否越界
		if ((curEnemyBullet->y < -20) || (curEnemyBullet->y > HEIGHT_MAP) || (curEnemyBullet->x > WIDTH_MAP) || (curEnemyBullet->x < -20))
			curEnemyBullet->isExist = 0;


		//如果有护盾就根据护盾的碰撞体进行判断
		if (Struct_bunker->isExist == 1) {
			if (curEnemyBullet->x + WIDTH_BULLET0 / 2 > Struct_bunker->xl && curEnemyBullet->x + HEIGHT_BULLET0<Struct_bunker->xr &&
				curEnemyBullet->y + HEIGHT_BULLET0>Struct_bunker->yu && curEnemyBullet->y + HEIGHT_BULLET0 < Struct_bunker->yd) {
				curEnemyBullet->isExist = 0;
			}
		}
		//else {//判断是否被击中
		if (curEnemyBullet->x + WIDTH_BULLET0 / 2 > Struct_PlayerPosition.x && curEnemyBullet->x + WIDTH_BULLET0 / 2 < Struct_PlayerPosition.x + WIDTH_PLAYER &&
			curEnemyBullet->y + HEIGHT_BULLET0 > Struct_PlayerPosition.y && curEnemyBullet->y + HEIGHT_BULLET0 < Struct_PlayerPosition.y + HEIGHT_PLAYER) {
			//先清除敌人子弹
			curEnemyBullet->isExist = 0;

			if (E_TYPE_PlayerState == OBJ_Player->Live) {//才扣血


				OBJ_Player->health -= curEnemyBullet->hitpoint;
				E_TYPE_PlayerState = OBJ_Player->Invulnerable;//进入无敌状态一会儿
				if (Struct_bunker->cnt != 0) {
					Struct_bunker->isExist = 1;//使护盾出现
					Struct_bunker->cnt--;
				}
				Struct_bunker->f_create = framebuffer;//记录下创建护盾时的帧数



				if (OBJ_Player->health <= 0) {

					E_TYPE_PlayerState = OBJ_Player->Dead;
					gameState.gaming = 0;
					gameState.gameOver = 1;
				}
			}

		}
		//}

		curEnemyBullet = curEnemyBullet->pnext;//指向下一个节点
	}

}
void listRemoveNodeEnemyBullet(EnemyBulletNode** p_Enemy_Bullet_List_Head)
{
	if (p_Enemy_Bullet_List_Head == NULL)//如果链表为空，就没有可删除的节点了
		return;
	EnemyBulletNode* curP = *p_Enemy_Bullet_List_Head;//curret先指向第一个节点
	EnemyBulletNode* prevP = NULL;  //previous指向上一个节点的指针
	while (curP != NULL)//遍历链表
	{
		if (curP->isExist == 0)
		{
			if (*p_Enemy_Bullet_List_Head == curP)
			{
				*p_Enemy_Bullet_List_Head = curP->pnext;
				free(curP);
				curP = *p_Enemy_Bullet_List_Head;
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
void update_EnemyBulletImage(EnemyBulletNode** pp_Enemy_Bullet_List_Head) {
	for (EnemyBulletNode* curEnemyNode = *pp_Enemy_Bullet_List_Head; curEnemyNode != NULL; curEnemyNode = curEnemyNode->pnext)
	{
		transparentimage(NULL, curEnemyNode->x, curEnemyNode->y, WIDTH_ENEMYBULLET0, HEIGHT_ENEMYBULLET0,
			0, 0, WIDTH_ENEMYBULLET0, HEIGHT_ENEMYBULLET0, &enemyBullet0, 255);
	}
}
void update_EnemyBullet(EnemyNode** pp_Enemy_List_Head, EnemyBulletNode** pp_Enemy_Bullet_List_Head, float vx, float vy, int level, int hitpoint, int framebuffer) {
	update_EnemyBulletPosition(pp_Enemy_List_Head, pp_Enemy_Bullet_List_Head, vx, vy, level, hitpoint, framebuffer);
	listRemoveNodeEnemyBullet(pp_Enemy_Bullet_List_Head);
}
