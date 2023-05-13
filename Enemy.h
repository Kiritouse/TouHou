#pragma once
#include "FrameManager.h"
#define PI 3.1415926
#define DEF_MOVE_STOP 0
#define DEF_MOVE_LINE 1 //线性的移动方式
#define DEF_MOVE_CIRCLE_RIGHT 2//圆弧形的移动方式，向右边移动
#define DEF_MOVE_CIRCLE_LEFT 3//圆弧形的移动方式，向左边移动
#define DEF_MOVE_RAND 4//随机线性移动

#define WIDTH_ENEMY0 40
#define HEIGHT_ENEMY0 59

#define WIDTH_ENEMY1 43
#define HEIGHT_ENEMY1 58

#define WIDTH_BOSS 36
#define HEIGHT_BOSS 56
extern int cntEnemy;

struct  EnemyNode
{
	int FireSwitch;//敌机开火键位
	int fire_on;//如果总帧数与一个中间变量的插值为fire_on就切换开火状态，即每隔fire_on帧就开一次火

	int type_enemy0 = 0, type_enemy1 = 0, type_boss = 0;
	int x, y, x0, y0;//初始创建角色的位置信息,x,y为每次移动的位置，x0和y0为初始位置

	int moveMode;//初始的移动方式,沿着坐标轴
	int xo, yo, r;//对于弧形移动的所需参数，xo和yo为圆心,r为半径
	double radian;//偏转角，用于直线移动和随机移动

	int health;//生命值

	int f_create;//创建该角色时的帧数

	int width;//模型的宽高
	int height;

	int hitpoints;//伤害值
	double speed;
	int weaponLevel;//武器的等级，其实就是子弹的种类

	int isExist;//物体是否需要销毁

	EnemyNode* pnext;//指向下一个节点的指针
};
enum EnemyName {
	ENEMY0,
	ENEMY1,
	BOSS,
};
//负责直线移动
EnemyNode* createEnemy(int fire_on, int x0, int y0, int x, int y, int moveMode, double radian, double speed, EnemyName name, int health, int weaponLevel, int framebuffer);
//负责
EnemyNode* createEnemy(int fire_on, int x0, int y0, int x, int y, int moveMode, double speed, EnemyName name, int health, int weaponLevel, int framebuffer);

EnemyNode* createEnemy(int fire_on, int x0, int y0, int x, int y, int moveMode, int xo, int yo, double radian, double speed, EnemyName name, int health, int weaponLevel, int framebuffer);
void Enemy_ListPushHead(EnemyNode** pp_Enemy_List_Node, EnemyNode* newNode);
void update_Enemy(EnemyNode** pp_Enemy_List_Node_Head, Frame frame);
void update_EnemyImage(EnemyNode** pp_Enemy_List_Node_Head);








