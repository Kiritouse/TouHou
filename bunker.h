#pragma once
//当玩家被击中的时候才会出现
#define WIDTH_BUNKER 59
#define HEIGHT_BUNKER 60
struct  Bunker
{
	//碰撞体的边界
	int xl, xr;
	int yu, yd;
	int isExist;
	int f_create;//护盾持续了多少帧
	int cnt;//能持续几次
	Bunker(int xl, int xr, int yu, int yd, int f_create, int isExist, int cnt);
};
void update_CrashBunker();
void drawBunker();
extern Bunker* Struct_bunker;
