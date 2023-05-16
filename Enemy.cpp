#include "Enemy.h"
#include "Operation.h"
#include "Map.h"
#include "Draw.h"
#include "LoadResources.h"
#include "MathAndPhysics.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <random>
#define CIRCLE_RIGHT  0
#define CIRCLE_LEFT  1
const double MOVE_FACTOR = 0.1;
int cntEnemy = 0;
//负责敌人的初始化
EnemyNode* createEnemy(int fire_on, int x0, int y0, int x, int y, int moveMode, double radian, double speed, EnemyName name, int health, int weaponLevel, int framebuffer) {
	EnemyNode* pNew = new EnemyNode;
	switch (name)
	{
	case ENEMY0:
		pNew->type_enemy0 = 1;
		break;
	case ENEMY1:
		pNew->type_enemy1 = 1;
		break;
	}
	//std::cout << "asdasd" << std::endl;
	pNew->x = x;
	pNew->y = y;
	pNew->x0 = x0;
	pNew->y0 = y0;
	pNew->moveMode = moveMode;
	pNew->radian = radian;
	pNew->speed = speed;
	pNew->health = health;
	pNew->weaponLevel = weaponLevel;
	pNew->f_create = framebuffer;
	pNew->isExist = 1;
	pNew->fire_on = fire_on;
	pNew->pnext = NULL;
	return pNew;
}
EnemyNode* createEnemy(int fire_on, int x0, int y0, int x, int y, int moveMode, double speed, EnemyName name, int health, int weaponLevel, int framebuffer) {
	EnemyNode* pNew = new EnemyNode;
	switch (name)
	{
	case ENEMY0:
		pNew->type_enemy0 = 1;
		break;
	case ENEMY1:
		pNew->type_enemy1 = 1;
		break;
	}
	pNew->fire_on = fire_on;
	pNew->x = x;
	pNew->y = y;
	pNew->x0 = x0;
	pNew->y0 = y0;
	pNew->moveMode = moveMode;
	pNew->speed = speed;
	pNew->health = health;
	pNew->weaponLevel = weaponLevel;
	pNew->f_create = framebuffer;
	pNew->isExist = 1;
	pNew->pnext = NULL;
	return pNew;
}
EnemyNode* createEnemy(int fire_on, int x0, int y0, int x, int y, int moveMode, int xo, int yo, double radian, double speed, EnemyName name, int health, int weaponLevel, int framebuffer) {
	EnemyNode* pNew = new EnemyNode;
	switch (name)
	{
	case ENEMY0:
		pNew->type_enemy0 = 1;
		break;
	case ENEMY1:
		pNew->type_enemy1 = 1;
		break;
	}
	pNew->fire_on = fire_on;
	pNew->x = x;
	pNew->y = y;
	pNew->x0 = x0;
	pNew->y0 = y0;
	pNew->moveMode = moveMode;
	pNew->radian = radian;
	pNew->xo = xo;
	pNew->yo = yo;
	pNew->r = y0 - yo;

	pNew->speed = speed;
	pNew->health = health;
	pNew->weaponLevel = weaponLevel;
	pNew->f_create = framebuffer;
	pNew->isExist = 1;
	pNew->pnext = NULL;
	return pNew;
}

void Enemy_ListPushHead(EnemyNode** pp_Enemy_List_Node_Head, EnemyNode* newNode) {
	if (*pp_Enemy_List_Node_Head == NULL)//如果链表为空，那么新增的节点就是第一个,头节点
	{
		*pp_Enemy_List_Node_Head = newNode;
		return;
	}
	newNode->pnext = (*pp_Enemy_List_Node_Head)->pnext;//让新增节点指向原先头节点指向的数据
	(*pp_Enemy_List_Node_Head)->pnext = newNode;//让原头节点指向新增节点
	cntEnemy++;
}
void update_EnemyImage(EnemyNode** p_Enemy_List) {
	for (EnemyNode* cur = *p_Enemy_List; cur != NULL; cur = cur->pnext) {
		if (cur->type_enemy0 == 1) {
			transparentimage(NULL, cur->x, cur->y, WIDTH_ENEMY0, HEIGHT_ENEMY0,
				0, 0, WIDTH_ENEMY0, HEIGHT_ENEMY0, &enemy0);
		}
		else if (cur->type_enemy1 == 1) {
			transparentimage(NULL, cur->x, cur->y, WIDTH_ENEMY1, HEIGHT_ENEMY1,
				0, 0, WIDTH_ENEMY1, HEIGHT_ENEMY1, &enemy1);
		}
		else if (cur->type_boss == 1) {
			transparentimage(NULL, cur->x, cur->y, WIDTH_BOSS, HEIGHT_BOSS,
				0, 0, WIDTH_BOSS, HEIGHT_BOSS, &enemy1);
		}
	}
}

void moveLine(EnemyNode* cur) {

	int xnext = cur->x + cur->speed * cos(cur->radian);
	int ynext = cur->y + cur->speed * sin(cur->radian);
	if (cur->type_enemy0 == 1)
	{
		if (xnext < WIDTH_MAP - WIDTH_ENEMY0 && ynext < HEIGHT_MAP - HEIGHT_ENEMY0 && xnext > 0 && ynext > 0) {
			cur->x = xnext;
			cur->y = ynext;
		}
		else cur->isExist = 0;
		return;
	}
	else if (cur->type_enemy1 == 1) {
		if (xnext < WIDTH_MAP - WIDTH_ENEMY1 && ynext < HEIGHT_MAP - HEIGHT_ENEMY1 && xnext >0 && ynext > 0) {
			cur->x = xnext;
			cur->y = ynext;
		}
		else cur->isExist = 0;
		return;
	}
}
void moveCircle(EnemyNode* cur, int framebuffer, int type) {
	int xnext, ynext;
	if (type == CIRCLE_RIGHT) {
		xnext = cur->x0 + cur->r * sin(cur->radian);
		ynext = cur->y0 - (cur->r - cur->r * cos(cur->radian));
		cur->radian = cur->radian + cur->speed;
	}
	else if (type == CIRCLE_LEFT) {
		xnext = cur->x0 - cur->r * sin(cur->radian);
		ynext = cur->y0 - (cur->r - cur->r * cos(cur->radian));
		cur->radian = cur->radian + cur->speed;

	}
	if (cur->type_enemy0 == 1) {
		if (xnext < WIDTH_MAP - WIDTH_ENEMY0 && ynext < HEIGHT_MAP - HEIGHT_ENEMY0 && xnext > 1 && ynext > 1) {
			cur->x = xnext;
			cur->y = ynext;
		}
		else {
			cur->isExist = 0;
			return;
		}
	}
	else if (cur->type_enemy1 == 1) {

		if (xnext < WIDTH_MAP - WIDTH_ENEMY1 && ynext < HEIGHT_MAP - HEIGHT_ENEMY1 && xnext > 1 && ynext > 1) {
			cur->x = xnext;
			cur->y = ynext;
		}
		else {
			cur->isExist = 0;
			return;
		}
	}

}
void moveRand(EnemyNode* cur, int framebuffer) {
	srand((unsigned int)time(NULL));
	int xnext = cur->x + rand() % ((int)cur->speed + 1) - (cur->speed) / 2;
	int ynext = cur->y + rand() % ((int)cur->speed + 1) - (cur->speed) / 20;
	if (cur->type_enemy0 == 1) {

		if (xnext < WIDTH_MAP - WIDTH_ENEMY0 && ynext < HEIGHT_MAP - HEIGHT_ENEMY0 && xnext > 0 && ynext >0) {
			cur->x = xnext;
			cur->y = ynext;
		}
		else {
			cur->isExist = 0;
			return;
		}
	}
	else if (cur->type_enemy1 == 1) {
		if (xnext < WIDTH_MAP - WIDTH_ENEMY1 && ynext < HEIGHT_MAP - HEIGHT_ENEMY1 && xnext > 0 && ynext >0) {
			cur->x = xnext;
			cur->y = ynext;
		}
		else {
			cur->isExist = 0;
			return;
		}
	}

}
void moveBoss(EnemyNode* cur) {
	if (cur->type_boss == 1) {
		if (cur->y <= HEIGHT_MAP / 3) {
			cur->y += cur->speed;
		}
		else {
			srand(time(0));
			int xnext = cur->x + rand() % (int)cur->speed - (cur->speed / 2);//左右随机移动
			if (xnext < 2 || xnext >= WIDTH_MAP - WIDTH_BOSS) {
				cur->x = xnext;//只把符合要求的x的位移值给cur->x
			}
		}
	}
}
void update_EnemyPosition(EnemyNode** pp_Enemy_List_Node_Head, Frame frame) {//用指针遍历每个飞机节点，根据飞机的初始位置,初始方向,选择不同的更新方式
	if (*pp_Enemy_List_Node_Head == NULL) return;
	EnemyNode* cur = *pp_Enemy_List_Node_Head;
	int framebuffer = frame.f_total - frame.f_pause;
	while (cur != NULL)
	{
		if (cur->isExist == 0) return;//如果已经被删除了就不需要再移动了
		if (cur->type_boss == 1) moveBoss(cur);
		else {
			switch (cur->moveMode)
			{
			case DEF_MOVE_LINE:
				moveLine(cur);
				break;
			case DEF_MOVE_CIRCLE_RIGHT:
				moveCircle(cur, framebuffer, CIRCLE_RIGHT);
				break;
			case DEF_MOVE_CIRCLE_LEFT:
				moveCircle(cur, framebuffer, CIRCLE_LEFT);
				break;
			case DEF_MOVE_RAND:
				moveRand(cur, framebuffer);
				break;
			default:
				break;
			}
		}
		cur = cur->pnext;
	}
}
void listRemoveNode_Enemy(EnemyNode** pp_Enemy_List_Node_Head)
{
	if (*pp_Enemy_List_Node_Head == NULL)//如果链表为空，就没有可删除的节点了
		return;

	EnemyNode* curP_Enemy = *pp_Enemy_List_Node_Head;//curret先指向第一个节点
	EnemyNode* prevP_Enemy = NULL;  //previous指向上一个节点的指针
	while (curP_Enemy != NULL)//遍历链表
	{
		if (curP_Enemy->isExist == 0)
		{

			if (*pp_Enemy_List_Node_Head == curP_Enemy)
			{
				*pp_Enemy_List_Node_Head = curP_Enemy->pnext;
				free(curP_Enemy);
				curP_Enemy = *pp_Enemy_List_Node_Head;
			}
			else
			{
				prevP_Enemy->pnext = curP_Enemy->pnext;
				free(curP_Enemy);
				curP_Enemy = prevP_Enemy;
			}
			cntEnemy--;
		}
		else
		{
			prevP_Enemy = curP_Enemy;
			curP_Enemy = curP_Enemy->pnext;
		}
	}
}


void update_Enemy(EnemyNode** pp_Enemy_List_Node_Head, Frame frame) {
	update_EnemyPosition(pp_Enemy_List_Node_Head, frame);
	listRemoveNode_Enemy(pp_Enemy_List_Node_Head);
}