#pragma once
class Interface
{
public:
	void putButton();
	void InitGraphInterface();
	void paintStartInterface();
	void paintGameInterface();
	void paintPauseInterface();
	void paintGameOverInterface();


};
struct ButtonState
{
	int enterButtonIsHit;//按下为1，没按下为0
	int saveButtonIsHit;
	int continueButtonIsHit;
	int ranklistButtonIsHit;

};
void update_StartUI();
extern ButtonState buttonState;
