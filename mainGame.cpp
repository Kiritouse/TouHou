#include "GameManager.h"
#include "LoadResources.h"
#include "Operation.h"
#include "DataManager.h"
#include "Music.h"
int main() {

	loadResources();
	ini();//��ʼ����������
	while (gameState.startUI) {//����Ϸ״̬�ڿ�ʼUI״̬��ʱ���
		OBJ_interface.paintStartInterface();

		MouseLisenter();//����Ѿ���ȡ�˴浵�ļ�,isSave������Ϊ1,���˿�ʼ��Ϸ���߼�����Ϸ��gameState�ͻ���gaming
	}



	while (gameState.gaming) {
		Gaming();
	}

}