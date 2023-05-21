#include <Windows.h>
#include <time.h>
#include "GameManager.h"
#include "LoadResources.h"
#include "Interface.h"
#include "Map.h"
#include "Player.h"
#include "Operation.h"
#include "FrameManager.h"
#include "Draw.h"
#include "Music.h"
#include "ParticleManager.h"
#include "bunker.h"
#include "DataManager.h"
#include <string>
#define PI 3.1415926
GameState gameState;
Interface OBJ_interface;
Map OBJ_Map;
Player* OBJ_Player = new Player;
Frame frame;
BulletNode* p_Player_Bullet_List_Node;//�ɻ��ӵ��б��ͷ�ڵ�
EnemyBulletNode* p_Enemy_Bullet_List_Node;//�л��ӵ��б�ͷ�ڵ�
EnemyNode* p_Enemy_List_Node;
User user;
clock_t t_begin;
clock_t t_update;
int  n_command;//��ȡ����
int deltaFrame_LineMove = 0;
int deltaFrame_CircleMove = 0;
int tempFrame_LineMove = 0;
int tempFrame_CircleMove = 0;
int framebuffer = 0;
int flag = 0;
int flag2 = 0;
int outf_total = 0;//�����������浵
void AddItem(int framebuffer) {
	outf_total = framebuffer + frame.f_pause;
	srand(framebuffer);
	int randFireOn = rand() % 31 + 20;
	int randHeight = rand() % (HEIGHT_MAP / 4 * 3 - HEIGHT_MAP / 4 + 1) + HEIGHT_MAP / 4;
	int randDelta = rand() % 100 - 50;
	deltaFrame_LineMove = framebuffer - tempFrame_LineMove;//tempframe��¼��һ�ε���AddItem������ʱ��
	deltaFrame_CircleMove = framebuffer - tempFrame_CircleMove;
	//std::cout << deltaFrame_LineMove << std::endl;
	if (deltaFrame_LineMove == 40) {
		tempFrame_LineMove = framebuffer;
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(randFireOn, rand() % (WIDTH_MAP / 5 * 4 - WIDTH_MAP / 5 + 1) + WIDTH_MAP / 5, 3, rand() % (WIDTH_MAP / 5 * 4 - WIDTH_MAP / 5 + 1) + WIDTH_MAP / 5, 3, DEF_MOVE_LINE, PI / 2, 2, ENEMY0, 50, 0, framebuffer));
	}
	if (deltaFrame_CircleMove == 100) {
		tempFrame_CircleMove = framebuffer;
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(randFireOn, 10, randHeight, 10, randHeight, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(randFireOn, 400, randHeight + randDelta, 400, randHeight + randDelta, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
	}

	switch (framebuffer)
	{
		//ÿ��40֡�������˴���������ƶ�����
		//������ֱ���ƶ�
	case 100:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP / 5 * 1, 3, WIDTH_MAP / 5 * 1, 3, DEF_MOVE_LINE, PI / 2, 2, ENEMY0, 50, 0, framebuffer));
		break;
	case 120:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP / 5 * 2, 3, WIDTH_MAP / 5 * 2, 3, DEF_MOVE_LINE, PI / 2, 2, ENEMY0, 50, 0, framebuffer));
		break;
	case 140:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP / 5 * 3, 3, WIDTH_MAP / 5 * 3, 3, DEF_MOVE_LINE, PI / 2, 2, ENEMY0, 50, 0, framebuffer));
		break;
	case 160:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP / 5 * 4, 3, WIDTH_MAP / 5 * 4, 3, DEF_MOVE_LINE, PI / 2, 2, ENEMY0, 50, 0, framebuffer));
		break;
		//��߳����л�
	case 300:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 3, HEIGHT_MAP / 7 * 1, 3, HEIGHT_MAP / 7 * 1, DEF_MOVE_LINE, 0.0f, 2, ENEMY0, 50, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 3, HEIGHT_MAP / 7 * 2, 3, HEIGHT_MAP / 7 * 2, DEF_MOVE_LINE, 0.0f, 2, ENEMY0, 50, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 3, HEIGHT_MAP / 7 * 3, 3, HEIGHT_MAP / 7 * 3, DEF_MOVE_LINE, 0.0f, 2, ENEMY0, 50, 0, framebuffer));
		break;
		//�ұ߳����л�
	case 500:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP - 50, HEIGHT_MAP / 7 * 4, WIDTH_MAP - 50, HEIGHT_MAP / 7 * 4, DEF_MOVE_LINE, PI, 2, ENEMY0, 50, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP - 50, HEIGHT_MAP / 7 * 5, WIDTH_MAP - 50, HEIGHT_MAP / 7 * 5, DEF_MOVE_LINE, PI, 2, ENEMY0, 50, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, WIDTH_MAP - 50, HEIGHT_MAP / 7 * 6, WIDTH_MAP - 50, HEIGHT_MAP / 7 * 6, DEF_MOVE_LINE, PI, 2, ENEMY0, 50, 0, framebuffer));
		break;

		//�ɻ������ұߺ�������߻����ƶ�
	case 600:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
	case 620:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
	case 640:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
	case 660:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
	case 680:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
	case 700:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
	case 720:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 10, HEIGHT_MAP / 2, 10, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_RIGHT, 10, 10, 0.0f, 0.00625, ENEMY1, 100, 0, framebuffer));
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(20, 400, HEIGHT_MAP / 2, 400, HEIGHT_MAP / 2, DEF_MOVE_CIRCLE_LEFT, 400, 10, 0.0f, PI / 500, ENEMY1, 100, 0, framebuffer));
		break;
		//��ʼ����ƶ�
	case 800:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(50, rand() % (WIDTH_MAP / 3 * 2 - WIDTH_MAP / 3 + 1) + WIDTH_MAP / 3, 20, rand() % (WIDTH_MAP / 3 * 2 - WIDTH_MAP / 3 + 1) + WIDTH_MAP / 3, 20, DEF_MOVE_RAND, 6.0f, ENEMY0, 100, 0, framebuffer));
		break;
	case 840:
		Enemy_ListPushHead(&p_Enemy_List_Node, createEnemy(50, rand() % (WIDTH_MAP / 3 * 2 - WIDTH_MAP / 3 + 1) + WIDTH_MAP / 3, 20, rand() % (WIDTH_MAP / 3 * 2 - WIDTH_MAP / 3 + 1) + WIDTH_MAP / 3, 20, DEF_MOVE_RAND, 6.0f, ENEMY0, 100, 0, framebuffer));
		break;








	}
}

void ini() {
	//��ʼ�����
	OBJ_Player->iniPlayer();
	//��ʼ������ӵ��б�
	p_Player_Bullet_List_Node = NULL;//��ʼ������ӵ��б�
	//��ʼ������
	p_Enemy_List_Node = NULL;
	//��ʼ�������ӵ��б�
	p_Enemy_Bullet_List_Node = NULL;
	//��ʼ��֡������
	iniFrame(frame, 0, 0, 0);
	//��ʼ����ʼʱ��
	t_begin = clock();
	user.score = 0;


	OBJ_interface.InitGraphInterface();
}
void update_Paintings(int framebuffer) {
	BeginBatchDraw();
	cleardevice();
	OBJ_Map.update_MapImage();
	OBJ_interface.paintGameInterface();
	OBJ_Player->update_PlayerImage(framebuffer);
	update_BulletImage(&p_Player_Bullet_List_Node);
	update_EnemyImage(&p_Enemy_List_Node);
	update_EnemyBulletImage(&p_Enemy_Bullet_List_Node);
	if (Struct_bunker->isExist) drawBunker();
	update_Particle();
	putStatePlayer();
	EndBatchDraw();
}

void Update() {//֡����

	while (gameState.gaming == 1) {
		t_update = clock();
		if (t_update - t_begin >= 10) {
			t_begin = t_update;
			frame.f_total++;//��֡����10msΪһ֡
			framebuffer = frame.f_total - frame.f_pause;//��Ч����ʱ��
			if (frame.f_total >= 0x3f3f3f3f) {
				std::cout << "��ϲ���ʤ" << std::endl;
				std::cout << "���ĵ÷���" << user.score << std::endl;
				writePlayer();//��¼�������Ϣ������ʵ�����а�
			}
		}
		else continue;
		MouseLisenter();//��ȡ����¼�
		if (!gameState.pause) {

			update_Paintings(framebuffer);
			AddItem(framebuffer);
			n_command = GetInput();
			OBJ_Map.update_Map();
			OBJ_Player->update_Player(n_command, framebuffer);
			update_Bullet(&p_Enemy_List_Node, &p_Player_Bullet_List_Node, n_command, framebuffer, 0, -10, 10);
			update_Enemy(&p_Enemy_List_Node, frame);
			if (Struct_bunker->isExist) update_CrashBunker();
			update_EnemyBullet(&p_Enemy_List_Node, &p_Enemy_Bullet_List_Node, 0, 6, 0, 1, framebuffer);
		}
		else if (gameState.pause) {
			OBJ_interface.paintPauseInterface();//���ƴ浵��ť
		}
		Sleep(20);
	}
	while (gameState.gameOver) {
		OBJ_interface.paintGameOverInterface();
		if (!flag2) {
			writePlayer();
			std::cout << "���:";
			for (int i = 0; i < user.name.size(); i++) {
				std::cout << user.name[i];
			}
			std::cout << std::endl;
			std::cout << "���ĵ÷���:" << user.score << std::endl;
			flag2 = 1;
		}
		stopsound(0);
		Sleep(10);

	}
}



void Gaming() {
	playsound(0, 1);
	Update();
	EndBatchDraw();
}