#pragma once
#include <graphics.h>
#include "FrameManager.h"
#include "Enemy.h"
#include "Player.h"
struct  EnemyBulletNode
{
	float x, y;
	float vx, vy;

	int level;
	int hitpoint;

	int isExist;
	EnemyBulletNode* pnext;


};
void update_EnemyBullet(EnemyNode** pp_Enemy_List_Head, EnemyBulletNode** pp_Enemy_Bullet_List_Head, float vx, float vy, int level, int hitpoint, int framebuffer);
void update_EnemyBulletImage(EnemyBulletNode** pp_Enemy_Bullet_List_Head);


