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
	int enterButtonIsHit;//����Ϊ1��û����Ϊ0
	int saveButtonIsHit;
	int continueButtonIsHit;
	int ranklistButtonIsHit;

};
void update_StartUI();
extern ButtonState buttonState;
