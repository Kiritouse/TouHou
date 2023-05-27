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
	//�����������
	FILE* fp;//��Ϸ�浵�ļ����
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
		//��¼��ҵ�״̬
		fprintf(fp, "%d %d\n", Struct_PlayerPosition.x, Struct_PlayerPosition.y);
		fprintf(fp, "%d\n", OBJ_Player->health);
		//ͳ�Ƴ�������ӵ����
		BulletNode* curBullet = p_Player_Bullet_List_Node;
		fprintf(fp, "%d\n", cntBullet);
		//curBullet = p_Player_Bullet_List_Node;
		while (curBullet != NULL) {
			fprintf(fp, "%d %d\n", curBullet->x, curBullet->y);
			fprintf(fp, "%d %d\n", curBullet->vx, curBullet->vy);
			curBullet = curBullet->pnext;
		}
		std::cout << "�浵�ɹ���" << std::endl;
		fclose(fp);
	}
}
void writePlayer() {//ֻ�����������Ż�����������������ҵ����յ÷�д��
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
		//��ȡ�û����ƺͷ���
		fscanf(fpp, "%s", users);
		fscanf(fpp, "%d", &user.score);

		fscanf(fpp, "%d", &frame.f_total);
		fscanf(fpp, "%d", &tempFrame_LineMove);
		fscanf(fpp, "%d", &tempFrame_CircleMove);
		//��ȡ���״̬
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
		fclose(fpp);//�ر�
	}
}
void showRank() {

	//���ζ�ȡ�û�id�ͷ������Ҵ���ṹ����;
	std::ifstream file("data.txt");
	std::string id;
	int tempscore;
	while (file >> id >> tempscore) {//���ζ�ȡ
		users.push_back({ id,tempscore });
	}
	//���ݷ�������
	std::stable_sort(users.begin(), users.end(), compare);
	//��ʾ��������
	std::cout << "���а�" << std::endl;
	for (auto i : users) {
		std::cout << i.name << "  " << i.score << std::endl;
	}

}