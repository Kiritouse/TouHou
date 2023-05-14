#include "Player.h"
#include <graphics.h>
#include "FrameManager.h"
#include "Operation.h"
#include "Map.h"
#include "Draw.h"
#include "LoadResources.h"
#include "DataManager.h"
int lastLeftState = 0;
PlayerCollider playerCollider;//���˳������Ͻǳ�����˳ʱ����ת
struct orimg {
	int x = 3, y = 0;
}originPoint_img;
Player::Position  Struct_PlayerPosition;
Player::Direction Struct_Direction;
Player::ObjectState E_TYPE_PlayerState;
int leftOpFramebuffer, rightOpFramebuffer, upOpFramebuffer, downOpFramebuffer, tempframe;
/// <summary>
/// ����������ݵĳ�ʼ��
/// </summary>
void Player::iniPlayer() {
	speed = 6;
	Struct_PlayerPosition.x = 240;
	Struct_PlayerPosition.y = 670;
	health = 10;
	E_TYPE_PlayerState = Live;
	Struct_Direction.up = 0;
	Struct_Direction.down = 0;
	Struct_Direction.left = 0;
	Struct_Direction.right = 0;
}
void Player::update_PlayerPosition(int _cmd, int framebuffer) {
	//������ײ��
	playerCollider.xl = Struct_PlayerPosition.x + ((WIDTH_PLAYER - 8) >> 1);
	playerCollider.xr = playerCollider.xl + 8;
	playerCollider.yu = Struct_PlayerPosition.y + ((HEIGHT_PLAYER - 8) >> 1);
	playerCollider.yd = playerCollider.yu + 8;



	static int stateRightStop = 1, stateLeftStop = 1, stateUpStop = 1, stateDownStop = 1, stateRight = 0, stateLeft = 0, stateUp = 0, stateDown = 0;
	if (_cmd & CMD_UP && Struct_PlayerPosition.y >= 0) {
		Struct_Direction.up = 1;
		Struct_PlayerPosition.y -= speed;

		if (stateUpStop == 1) {//��֤�����Ҽ���ʱ��ֻ���¼һ�ε�ʱ��
			upOpFramebuffer = framebuffer;//��¼�µ�ǰ�����Ҽ�������ʱ��
			stateUpStop = 0;
		}
		stateUp = 1;
	}
	else {
		if (stateUp == 1) {//���֮ǰ�Ĳ��������ƶ�״̬
			Struct_Direction.up = 0;
			stateUp = 0;
		}
		stateUpStop = 1;
	}

	if (_cmd & CMD_DOWN && Struct_PlayerPosition.y < HEIGHT_MAP - HEIGHT_PLAYER) {
		Struct_Direction.down = 1;
		Struct_PlayerPosition.y += speed;
		if (stateDownStop == 1) {//��֤�����Ҽ���ʱ��ֻ���¼һ�ε�ʱ��
			downOpFramebuffer = framebuffer;//��¼�µ�ǰ�����Ҽ�������ʱ��
			stateDownStop = 0;
		}
		stateDown = 1;
	}
	else {
		if (stateDown == 1) {//���֮ǰ�Ĳ��������ƶ�״̬
			Struct_Direction.down = 0;
			stateDown = 0;
		}
		stateDown = 1;
	}
	if (_cmd & CMD_RIGHT && Struct_PlayerPosition.x < WIDTH_MAP - WIDTH_PLAYER) {
		Struct_Direction.right = 1;
		Struct_PlayerPosition.x += speed;
		if (stateRightStop == 1) {//��֤�����Ҽ���ʱ��ֻ���¼һ�ε�ʱ��
			rightOpFramebuffer = framebuffer;//��¼�µ�ǰ�����Ҽ�������ʱ��
			stateRightStop = 0;
		}
		stateRight = 1;
	}
	else {
		if (stateRight == 1) {//���֮ǰ�Ĳ��������ƶ�״̬
			Struct_Direction.right = 0;
			stateRight = 0;
		}
		stateRightStop = 1;
	}

	if (_cmd & CMD_LEFT && Struct_PlayerPosition.x >= 0) {
		Struct_Direction.left = 1;
		Struct_PlayerPosition.x -= speed;
		if (stateLeftStop == 1) {
			leftOpFramebuffer = framebuffer;//��¼�µ�ǰ�������������ʱ��
			stateLeftStop = 0;
		}
		stateLeft = 1;//�������ƶ�״̬
	}
	else {
		if (stateLeft == 1) {
			Struct_Direction.left = 0;
			stateLeft = 0;//
		}
		stateLeftStop = 1;
	}

}

void Player::update_PlayerImage(int frameBuffer) {//
	int weight = 255;
	transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
		originPoint_img.x, originPoint_img.y, WIDTH_PLAYER, HEIGHT_PLAYER, &player);

	if (Struct_Direction.up - Struct_Direction.down > 0) {
		frameBuffer = frameBuffer - upOpFramebuffer;
		if (frameBuffer >= 0 && frameBuffer < 5)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				36, 0, WIDTH_PLAYER, HEIGHT_PLAYER_RIGHT, &player, weight);
		if (frameBuffer >= 5 && frameBuffer < 10)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				68, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 10 && frameBuffer < 15)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				100, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 15 && frameBuffer < 20)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				132, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 20 && frameBuffer < 25)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				164, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 25 && frameBuffer < 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				196, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				223, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
	}
	else if (Struct_Direction.up - Struct_Direction.down < 0) {
		frameBuffer = frameBuffer - downOpFramebuffer;
		if (frameBuffer >= 0 && frameBuffer < 5)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				36, 0, WIDTH_PLAYER, HEIGHT_PLAYER_RIGHT, &player, weight);
		if (frameBuffer >= 5 && frameBuffer < 10)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				68, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 10 && frameBuffer < 15)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				100, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 15 && frameBuffer < 20)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				132, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 20 && frameBuffer < 25)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				164, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 25 && frameBuffer < 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				196, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);
		if (frameBuffer >= 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER, HEIGHT_PLAYER,
				223, 0, WIDTH_PLAYER, HEIGHT_PLAYER, &player, weight);

	}
	else if (Struct_Direction.right - Struct_Direction.left > 0) {
		frameBuffer = frameBuffer - rightOpFramebuffer;
		if (frameBuffer >= 0 && frameBuffer < 5)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				33, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
		if (frameBuffer >= 5 && frameBuffer < 10)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				64, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
		if (frameBuffer >= 10 && frameBuffer < 15)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				96, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
		if (frameBuffer >= 15 && frameBuffer < 20)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				128, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
		if (frameBuffer >= 20 && frameBuffer < 25)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				160, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
		if (frameBuffer >= 25 && frameBuffer < 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				192, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
		if (frameBuffer >= 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT,
				223, 0, WIDTH_PLAYER_RIGHT, HEIGHT_PLAYER_RIGHT, &playerRight, weight);
	}
	else if (Struct_Direction.right - Struct_Direction.left < 0) {
		frameBuffer = frameBuffer - leftOpFramebuffer;
		if (frameBuffer >= 0 && frameBuffer < 5)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				36, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);
		if (frameBuffer >= 5 && frameBuffer < 10)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				68, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);
		if (frameBuffer >= 10 && frameBuffer < 15)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				99, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);
		if (frameBuffer >= 15 && frameBuffer < 20)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				132, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);
		if (frameBuffer >= 20 && frameBuffer < 25)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				164, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);
		if (frameBuffer >= 25 && frameBuffer < 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				196, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);
		if (frameBuffer >= 30)
			transparentimage(NULL, Struct_PlayerPosition.x, Struct_PlayerPosition.y, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT,
				228, 0, WIDTH_PLAYER_LEFT, HEIGHT_PLAYER_LEFT, &playerLeft, weight);

	}



}
void putStatePlayer() {
	TCHAR health_text[50];
	_stprintf_s(health_text, _T("Health:%d"), OBJ_Player->health);
	settextcolor(RGB(255, 255, 255));

	outtextxy(Struct_PlayerPosition.x - 20, Struct_PlayerPosition.y - 20, health_text);
	TCHAR score_text[50];
	_stprintf_s(score_text, _T("Score:%d"), user.score);
	settextcolor(RGB(255, 255, 255));

	outtextxy(Struct_PlayerPosition.x - 13, Struct_PlayerPosition.y + HEIGHT_PLAYER, score_text);
}

void Player::update_Player(int n_command, int framebuffer) {
	update_PlayerPosition(n_command, framebuffer);
	update_PlayerImage(framebuffer);
}