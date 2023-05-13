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
extern EnemyBulletNode* p_Enemy_Bullet_List_Node;//�л��ӵ��б�ͷ�ڵ�
extern EnemyNode* p_Enemy_List_Node;
extern clock_t t_begin;//��¼��Ϸ����ʱ��
extern int framebuffer;
extern int outf_total;
extern int tempFrame_LineMove;
extern int tempFrame_CircleMove;
/// <summary>
/// ��ʼ��һЩ����
/// </summary>
void ini();
void Update();

/// <summary>
///�����������GameManager����������Ϸ�йصĺ���
/// </summary>
void Gaming();


