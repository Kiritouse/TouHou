#include "GameManager.h"
#include "LoadResources.h"
#include "Operation.h"
#include "DataManager.h"
#include "Music.h"
int main() {

	loadResources();
	ini();//初始化所有数据
	while (gameState.startUI) {//当游戏状态在开始UI状态的时候就
		OBJ_interface.paintStartInterface();

		MouseLisenter();//如果已经读取了存档文件,isSave变量就为1,点了开始游戏或者继续游戏后gameState就会变成gaming
	}



	while (gameState.gaming) {
		Gaming();
	}

}