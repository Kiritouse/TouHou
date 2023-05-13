#include "Interface.h"
#include "GameManager.h"
#include "Draw.h"
#include <graphics.h>
#include "LoadResources.h"
#include "Operation.h"
#define WIDTH 500
#define HEIGHT 720
ButtonState buttonState;
void Interface::InitGraphInterface() {
	initgraph(WIDTH, HEIGHT);
}
void Interface::paintStartInterface() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, &startbackground);
	if (!buttonState.enterButtonIsHit) //如果没有被移动到那里
		transparentimage(NULL, 140, 400, 209, 64, 0, 0, 209, 64, &enterbutton);
	else//如果已经移动到了那里
		transparentimage(NULL, 140, 400, 209, 64, 0, 64, 209, 64, &enterbutton);

	if (!buttonState.continueButtonIsHit)
		transparentimage(NULL, 150, 500, 180, 59, 0, 0, 180, 59, &continuebutton);
	else
		transparentimage(NULL, 150, 500, 180, 50, 0, 86, 180, 59, &continuebutton);

	if (!buttonState.ranklistButtonIsHit)
		transparentimage(NULL, 140, 600, 209, 64, 0, 0, 209, 64, &ranklist);
	else
		transparentimage(NULL, 140, 600, 209, 64, 0, 64, 209, 64, &ranklist);



	EndBatchDraw();

}
void Interface::paintGameInterface() {
	transparentimage(NULL, 0, HEIGHT - 44, 44, 44, 0, 0, 44, 44, &pausebutton);
}
void Interface::paintPauseInterface() {
	if (!buttonState.saveButtonIsHit) //如果没有移动到那里
		transparentimage(NULL, 120, 400, 256, 57, 0, 0, 256, 57, &savebutton);

	else {//如果已经移动到了那里

		transparentimage(NULL, 120, 400, 256, 50, 0, 80, 256, 50, &savebutton);
	}
}
void Interface::paintGameOverInterface() {
	cleardevice();//清楚
	putimage(0, 0, &gameoverimg);
}
void  update_StartUI() {
	while (gameState.startUI) {//当游戏状态在开始UI状态的时候就
		OBJ_interface.paintStartInterface();
		MouseLisenter();
	}
}
