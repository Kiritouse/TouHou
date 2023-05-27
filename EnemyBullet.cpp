#include <stdlib.h>
#include "EnemyBullet.h"
#include "Map.h"
#include "Draw.h"
#include "LoadResources.h"
#include "bunker.h"
#include "DataManager.h"
#define DEF_TYPE_ENEMY0 0//ʶ����˵ı�ʶ��
#define DEF_TYPE_ENEMY1 1
#define WIDTH_ENEMYBULLET0 22
#define HEIGHT_ENEMYBULLET0 21
//��������ӵ��ĳ�ʼ��
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
			Struct_bunker->isExist = 0;//ɾ������
			E_TYPE_PlayerState = OBJ_Player->Live;//�ı��ɫ״̬
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
		//	�ж��Ƿ�Խ��
		if ((curEnemyBullet->y < -20) || (curEnemyBullet->y > HEIGHT_MAP) || (curEnemyBullet->x > WIDTH_MAP) || (curEnemyBullet->x < -20))
			curEnemyBullet->isExist = 0;


		//����л��ܾ͸��ݻ��ܵ���ײ������ж�
		if (Struct_bunker->isExist == 1) {
			if (curEnemyBullet->x + WIDTH_BULLET0 / 2 > Struct_bunker->xl && curEnemyBullet->x + HEIGHT_BULLET0<Struct_bunker->xr &&
				curEnemyBullet->y + HEIGHT_BULLET0>Struct_bunker->yu && curEnemyBullet->y + HEIGHT_BULLET0 < Struct_bunker->yd) {
				curEnemyBullet->isExist = 0;
			}
		}
		//else {//�ж��Ƿ񱻻���
		if (curEnemyBullet->x + WIDTH_BULLET0 / 2 > Struct_PlayerPosition.x && curEnemyBullet->x + WIDTH_BULLET0 / 2 < Struct_PlayerPosition.x + WIDTH_PLAYER &&
			curEnemyBullet->y + HEIGHT_BULLET0 > Struct_PlayerPosition.y && curEnemyBullet->y + HEIGHT_BULLET0 < Struct_PlayerPosition.y + HEIGHT_PLAYER) {
			//����������ӵ�
			curEnemyBullet->isExist = 0;

			if (E_TYPE_PlayerState == OBJ_Player->Live) {//�ſ�Ѫ


				OBJ_Player->health -= curEnemyBullet->hitpoint;
				E_TYPE_PlayerState = OBJ_Player->Invulnerable;//�����޵�״̬һ���
				if (Struct_bunker->cnt != 0) {
					Struct_bunker->isExist = 1;//ʹ���ܳ���
					Struct_bunker->cnt--;
				}
				Struct_bunker->f_create = framebuffer;//��¼�´�������ʱ��֡��



				if (OBJ_Player->health <= 0) {

					E_TYPE_PlayerState = OBJ_Player->Dead;
					gameState.gaming = 0;
					gameState.gameOver = 1;
				}
			}

		}
		//}

		curEnemyBullet = curEnemyBullet->pnext;//ָ����һ���ڵ�
	}

}
void listRemoveNodeEnemyBullet(EnemyBulletNode** p_Enemy_Bullet_List_Head)
{
	if (p_Enemy_Bullet_List_Head == NULL)//�������Ϊ�գ���û�п�ɾ���Ľڵ���
		return;
	EnemyBulletNode* curP = *p_Enemy_Bullet_List_Head;//curret��ָ���һ���ڵ�
	EnemyBulletNode* prevP = NULL;  //previousָ����һ���ڵ��ָ��
	while (curP != NULL)//��������
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
