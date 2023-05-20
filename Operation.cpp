#include "Operation.h"
#include "GameManager.h"
#include "Interface.h"
#include "DataManager.h"
#include "Bullet.h"
#include "Music.h"
#include <graphics.h>
#include <Windows.h>
#define START_BUTTON (m.x >= 140 && m.x <= 349 && m.y >= 400 && m.y <= 464)
#define PAUSE_BUTTON (m.x >= 0 && m.x <= 44 && m.y >= 676 && m.y <= 720)
#define SAVE_BUTTON (m.x>=120&&m.x<=376&&m.y>=400&&m.y<=450)
#define CONTINUE_BUTTON (m.x>=150&&m.x<=339&&m.y>=500&&m.y<=559)
#define RANKLIST_BUTTON (m.x>=140&&m.x<=349&&m.y>=600&&m.y<=664)
static int PauseFlag = 0;
int GetInput() {
	int inputState = CMD_NO_INPUT;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		inputState |= CMD_LEFT;//更新为当前的状态
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	inputState |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		inputState |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		inputState |= CMD_DOWN;
	if (GetAsyncKeyState('Z') && 0X8000) inputState |= CMD_FIRE;
	if (GetAsyncKeyState('X') && 0X8000) inputState |= CMD_SKILL;
	return inputState;
}
void MouseLisenter() {
	HWND hwnd = GetHWnd();										//获取绘图窗口句柄
	HWND hwnd_now = GetForegroundWindow();						//获取当前焦点窗口句柄
	MOUSEMSG m;
	HCURSOR hcur;
	if (MouseHit() && gameState.startUI) {//如果说鼠标点击了，并且在游戏开始界面的UI
		//判断是点击的是哪按键
		m = GetMouseMsg();
		if (START_BUTTON)
			buttonState.enterButtonIsHit = 1;
		else
			buttonState.enterButtonIsHit = 0;

		if (CONTINUE_BUTTON)
			buttonState.continueButtonIsHit = 1;
		else
			buttonState.continueButtonIsHit = 0;

		if (RANKLIST_BUTTON)
			buttonState.ranklistButtonIsHit = 1;
		else
			buttonState.ranklistButtonIsHit = 0;
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN://当按下了鼠标左键
			if (START_BUTTON) {

				std::cout << "请输入你的名称:";
				std::cin >> user.name;


				gameState.startUI = 0;
				gameState.gaming = 1;

			}
			if (CONTINUE_BUTTON) {//读取存档
				loadData();
				isSave = 1;//代表已经读取了存档文件
				gameState.startUI = 0;
				gameState.gaming = 1;
			}
			if (RANKLIST_BUTTON) {
				showRank();
			}
		default:
			break;
		}
	}
	if (MouseHit() && gameState.gaming) {

		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (PAUSE_BUTTON) {

				//std::cout << "asdasdsa" << std::endl;
				if (PauseFlag) {//上一次的状态是暂停
					gameState.pause = 0;
					PauseFlag = 0;//情况暂停状态
					resumesound(0);
				}
				else {//上一次的状态是游戏中
					gameState.pause = 1;
					frame.f_zawarudo = frame.f_total;//记录下当前暂停时的时间
					PauseFlag = 1;//进入暂停状态
					pausesound(0);

				}
			}
		default:
			break;
		}
	}

	if (MouseHit() && gameState.gaming && gameState.pause) {
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN://当按下了鼠标左键
			if (SAVE_BUTTON) {
				buttonState.saveButtonIsHit = 1;
				writeData();
				isSave = 1;
			}

			else
			{
				buttonState.saveButtonIsHit = 0;
				break;
			}
		default:
			break;
		}
	}
}