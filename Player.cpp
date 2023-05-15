#include "Player.h"
#include <graphics.h>
#include "FrameManager.h"
#include "Operation.h"
#include "Map.h"
#include "Draw.h"
#include "LoadResources.h"
#include "DataManager.h"
int lastLeftState = 0;
PlayerCollider playerCollider;//点的顺序从左上角出发，顺时针旋转
struct orimg {
	int x = 3, y = 0;
}originPoint_img;
Player::Position  Struct_PlayerPosition;
Player::Direction Struct_Direction;
Player::ObjectState E_TYPE_PlayerState;
int leftOpFramebuffer, rightOpFramebuffer, upOpFramebuffer, downOpFramebuffer, tempframe;
/// <summary>
/// 负责玩家数据的初始化
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
	//更新碰撞体
	playerCollider.xl = Struct_PlayerPosition.x + ((WIDTH_PLAYER - 8) >> 1);
	playerCollider.xr = playerCollider.xl + 8;
	playerCollider.yu = Struct_PlayerPosition.y + ((HEIGHT_PLAYER - 8) >> 1);
	playerCollider.yd = playerCollider.yu + 8;
	static int stateRightStop = 1, stateLeftStop = 1, stateUpStop = 1, stateDownStop = 1, stateRight = 0, stateLeft = 0, stateUp = 0, stateDown = 0;
	if (_cmd & CMD_UP && Struct_PlayerPosition.y >= 0) {
		Struct_Direction.up = 1;
		Struct_PlayerPosition.y -= speed;

		if (stateUpStop == 1) {//保证长按右键的时候只会记录一次的时间
			upOpFramebuffer = framebuffer;//记录下当前按下右键操作的时间
			stateUpStop = 0;
		}
		stateUp = 1;
	}
	else {
		if (stateUp == 1) {//如果之前的操作是上移动状态
			Struct_Direction.up = 0;
			stateUp = 0;
		}
		stateUpStop = 1;
	}

	if (_cmd & CMD_DOWN && Struct_PlayerPosition.y < HEIGHT_MAP - HEIGHT_PLAYER) {
		Struct_Direction.down = 1;
		Struct_PlayerPosition.y += speed;
		if (stateDownStop == 1) {//保证长按右键的时候只会记录一次的时间
			downOpFramebuffer = framebuffer;//记录下当前按下右键操作的时间
			stateDownStop = 0;
		}
		stateDown = 1;
	}
	else {
		if (stateDown == 1) {//如果之前的操作是右移动状态
			Struct_Direction.down = 0;
			stateDown = 0;
		}
		stateDown = 1;
	}
	if (_cmd & CMD_RIGHT && Struct_PlayerPosition.x < WIDTH_MAP - WIDTH_PLAYER) {
		Struct_Direction.right = 1;
		Struct_PlayerPosition.x += speed;
		if (stateRightStop == 1) {//保证长按右键的时候只会记录一次的时间
			rightOpFramebuffer = framebuffer;//记录下当前按下右键操作的时间
			stateRightStop = 0;
		}
		stateRight = 1;
	}
	else {
		if (stateRight == 1) {//如果之前的操作是右移动状态
			Struct_Direction.right = 0;
			stateRight = 0;
		}
		stateRightStop = 1;
	}

	if (_cmd & CMD_LEFT && Struct_PlayerPosition.x >= 0) {
		Struct_Direction.left = 1;
		Struct_PlayerPosition.x -= speed;
		if (stateLeftStop == 1) {
			leftOpFramebuffer = framebuffer;//记录下当前按下左键操作的时间
			stateLeftStop = 0;
		}
		stateLeft = 1;//进入左移动状态
	}
	else {
		if (stateLeft == 1) {
			Struct_Direction.left = 0;
			stateLeft = 0;//
		}
		stateLeftStop = 1;
	}

}
/// <summary>
/// 更新玩家动画
/// </summary>
/// <param name="frameBuffer">总运行帧数</param>
void Player::update_PlayerImage(int frameBuffer) {
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
	//展示玩家生命值
	TCHAR health_text[50];
	_stprintf_s(health_text, _T("Health:%d"), OBJ_Player->health);
	settextcolor(RGB(255, 255, 255));
	outtextxy(Struct_PlayerPosition.x - 20, Struct_PlayerPosition.y - 20, health_text);

	//展示玩家得分
	TCHAR score_text[50];
	_stprintf_s(score_text, _T("Score:%d"), user.score);
	settextcolor(RGB(255, 255, 255));
	outtextxy(Struct_PlayerPosition.x - 13, Struct_PlayerPosition.y + HEIGHT_PLAYER, score_text);
}

void Player::update_Player(int n_command, int framebuffer) {
	update_PlayerPosition(n_command, framebuffer);
	update_PlayerImage(framebuffer);
}
