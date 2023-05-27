#include "DataManager.h"
#include "Player.h"
#include "GameManager.h"
#include "Bullet.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
const int I_ENEMY0 = 114514;
const int I_ENEMY1 = 1919810;


std::vector<User> users;
bool compare(User a, User b) {
	return a.score > b.score;
}
void writeData() {
	//储存玩家数据
	FILE* fp;//游戏存档文件句柄
	fopen_s(&fp, "save.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "Can't open save.txt!\n");
		exit(1);
	}
	else {

		for (int i = 0; i < user.name.size(); i++) {
			if (i != user.name.size() - 1) {
				fprintf(fp, "%c", user.name[i]);
			}
			else fprintf(fp, "%c ", user.name[i]);
		}
		fprintf(fp, "%d\n", user.score);
		fprintf(fp, "%d\n", outf_total);
		fprintf(fp, "%d\n", tempFrame_LineMove);
		fprintf(fp, "%d\n", tempFrame_CircleMove);
		//记录玩家的状态
		fprintf(fp, "%d %d\n", Struct_PlayerPosition.x, Struct_PlayerPosition.y);
		fprintf(fp, "%d\n", OBJ_Player->health);
		//统计场上玩家子弹情况
		BulletNode* curBullet = p_Player_Bullet_List_Node;
		fprintf(fp, "%d\n", cntBullet);
		//curBullet = p_Player_Bullet_List_Node;
		while (curBullet != NULL) {
			fprintf(fp, "%d %d\n", curBullet->x, curBullet->y);
			fprintf(fp, "%d %d\n", curBullet->vx, curBullet->vy);
			curBullet = curBullet->pnext;
		}
		std::cout << "存档成功！" << std::endl;
		fclose(fp);
	}
}
void writePlayer() {//只有玩家阵亡后才会调用这个函数，将玩家的最终得分写入
	FILE* fpuser;
	fopen_s(&fpuser, "data.txt", "a");
	if (fpuser == NULL) {
		fprintf(stderr, "Can't open data.txt!\n");
		exit(1);
	}
	else {
		for (int i = 0; i < user.name.size(); i++) {
			if (i != user.name.size() - 1) {
				fprintf(fpuser, "%c", user.name[i]);
			}
			else fprintf(fpuser, "%c ", user.name[i]);

		}
		fprintf(fpuser, "%d\n", user.score);
	}
	fclose(fpuser);
}

void loadData() {
	FILE* fpp;
	fopen_s(&fpp, "save.txt", "r");
	if (fpp == NULL) {
		fprintf(stderr, "Can't open save.txt!\n");
		exit(2);
	}
	else {
		//读取用户名称和分数
		fscanf(fpp, "%s", users);
		fscanf(fpp, "%d", &user.score);

		fscanf(fpp, "%d", &frame.f_total);
		fscanf(fpp, "%d", &tempFrame_LineMove);
		fscanf(fpp, "%d", &tempFrame_CircleMove);
		//读取玩家状态
		fscanf(fpp, "%d %d", &Struct_PlayerPosition.x, &Struct_PlayerPosition.y);
		fscanf(fpp, "%d", &OBJ_Player->health);

		fscanf(fpp, "%d", &cntBullet);
		int  tempx = 0, tempy = 0;
		int tempvx = 0, tempvy = 0;
		int temphitpoint = 0;
		while (cntBullet--) {
			fscanf(fpp, "%d %d", &tempx, &tempy);
			fscanf(fpp, "%d %d", &tempvx, &tempvy);
			Bullet_listPushBack(&p_Player_Bullet_List_Node, creatPlayerBullet(tempx, tempy, tempvx, tempvy, 1));

		}
		fclose(fpp);//关闭
	}
}
void showRank() {

	//依次读取用户id和分数并且存入结构体中;
	std::ifstream file("data.txt");
	std::string id;
	int tempscore;
	while (file >> id >> tempscore) {//依次读取
		users.push_back({ id,tempscore });
	}
	//根据分数排序
	std::stable_sort(users.begin(), users.end(), compare);
	//显示出排序结果
	std::cout << "排行榜：" << std::endl;
	for (auto i : users) {
		std::cout << i.name << "  " << i.score << std::endl;
	}

}