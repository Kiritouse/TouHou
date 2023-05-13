#pragma once
#include "Interface.h"
#include "Player.h"
#include "GameManager.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "FrameManager.h"
#include "Enemy.h"
#include <iostream>
#include <graphics.h>
#pragma
struct GameState
{
	int gaming = 0, pause = 0, gameOver = 0, startUI = 1, ranklist = 0;
};
struct User
{
	std::string name;
	int score;
};
extern User user;


extern GameState gameState;
extern Interface OBJ_interface;
extern Player* OBJ_Player;
extern Frame frame;
extern BulletNode* p_Player_Bullet_List_Node;
extern EnemyBulletNode* p_Enemy_Bullet_List_Node;//敌机子弹列表头节点
extern EnemyNode* p_Enemy_List_Node;
extern clock_t t_begin;//记录游戏运行时间
extern int framebuffer;
extern int outf_total;
extern int tempFrame_LineMove;
extern int tempFrame_CircleMove;
/// <summary>
/// 初始化一些数据
/// </summary>
void ini();
void Update();

/// <summary>
///这个函数调用GameManager中所有与游戏有关的函数
/// </summary>
void Gaming();


