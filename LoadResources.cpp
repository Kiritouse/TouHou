#include "LoadResources.h"
#include "Bullet.h"
#include "Music.h"
IMAGE  startbackground, background, player, playerRight, playerLeft, normalBullets, enemy0, enemyBullet0, enemy1, boss, enterbutton, pausebutton, savebutton, continuebutton, powerProp, bunker, gameoverimg, ranklist;
SOUND gameScenebgm, shoot, boom;

void loadResources(void) {
	//加载背景图片
	loadimage(&background, _T("sources\\Background\\background.png"));
	loadimage(&startbackground, _T("sources\\Background\\ui.png"));
	loadimage(&gameoverimg, _T("sources\\Background\\gameover.png"));
	//加载Ui
	loadimage(&pausebutton, _T("sources\\Ui\\Button\\pause.png"));
	loadimage(&enterbutton, _T("sources\\Ui\\Button\\button-enter.png"));
	loadimage(&savebutton, _T("sources\\Ui\\Button\\save.png"));
	loadimage(&continuebutton, _T("sources\\Ui\\Button\\button-continue.png"));
	loadimage(&ranklist, _T("sources\\Ui\\Button\\button-rankinlist.png"));

	//加载道具

	//加载人物动画
	loadimage(&player, _T("sources\\Players\\PlayerUpAndDown.png"));
	loadimage(&playerRight, _T("sources\\Players\\PlayerRight.png"));
	loadimage(&playerLeft, _T("sources\\Players\\PlayerLeft.png"));

	//加载无敌时所需要使用的图片
	loadimage(&bunker, _T("sources\\Players\\bunker.png"));

	//加载子弹
	loadimage(&normalBullets, _T("sources\\Players\\Bullets\\Player\\normalBullets.png"));

	//加载敌人
	loadimage(&enemy0, _T("sources\\Enemy\\Enemy0.png"));
	loadimage(&enemy1, _T("sources\\Enemy\\Enemy1.png"));
	loadimage(&boss, _T("sources\\Enemy\\Boss.png"));
	loadimage(&enemyBullet0, _T("sources\\Enemy\\EnemyBullets\\EnemyBullet0.png"));

	//加载背景音乐
	loadsound(&gameScenebgm, _T("sources\\Music\\BGM\\Weight_of_the_World.mp3"));
	loadsound(&shoot, _T("sources\\Music\\Fire.mp3"));
	loadsound(&boom, _T("sources\\Music\\Boom.mp3"));




}

