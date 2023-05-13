#include "bunker.h"
#include "Draw.h"
#include "LoadResources.h"
#include "GameManager.h"
#include "Player.h"
Bunker* Struct_bunker = new Bunker(0, 0, 0, 0, 0, 0, 3);
Bunker::Bunker(int xl, int xr, int yu, int yd, int f_create, int isExist, int cnt) {
	this->xl = xl;
	this->xr = xr;
	this->yu = yu;
	this->yd = yd;
	this->f_create = f_create;
	this->isExist = isExist;
	this->cnt = cnt;
}
void  update_CrashBunker() {
	Struct_bunker->xl = Struct_PlayerPosition.x - WIDTH_PLAYER / 2 - 4;
	Struct_bunker->xr = Struct_bunker->xl + WIDTH_BUNKER;
	Struct_bunker->yu = Struct_PlayerPosition.y - HEIGHT_PLAYER / 2 + 20;
	Struct_bunker->yd = Struct_bunker->yu + HEIGHT_BUNKER;
}
void drawBunker() {//根据玩家的位置绘图
	transparentimage(NULL, Struct_PlayerPosition.x - WIDTH_PLAYER / 2 - 4, Struct_PlayerPosition.y - HEIGHT_PLAYER / 2 + 20, &bunker);
}