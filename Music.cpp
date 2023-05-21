#define _CRT_SECURE_NO_WARNINGS
#include "Music.h"

int g_soundID = 0;//音频编号,采用类似OpenGL的id来进行引用

void playsound(int sid, int repeat)
{
	wchar_t cmdStr[32];
	stopsound(sid);
	if (repeat)
		_stprintf(cmdStr, _T("play S%d from 0 repeat"), sid);
	else
		_stprintf(cmdStr, _T("play S%d from 0"), sid);
	mciSendString(cmdStr, NULL, 0, NULL);
}
void stopsound(int sid)
{
	wchar_t cmdStr[32];
	_stprintf(cmdStr, _T("stop S%d"), sid);
	mciSendString(cmdStr, NULL, 0, NULL);
}
void pausesound(int sid) {
	wchar_t cmdStr[32];
	_stprintf(cmdStr, _T("pause S%d"), sid);
	mciSendString(cmdStr, NULL, 0, NULL);
}
void resumesound(int sid) {
	wchar_t cmdStr[32];
	_stprintf(cmdStr, _T("resume S%d"), sid);
	mciSendString(cmdStr, NULL, 0, NULL);
}
void loadsound(SOUND* pSound, const wchar_t* fileName)
{
	wchar_t* cmdStr;
	int len = _tcslen(fileName) * sizeof(wchar_t);//根据地址字符串计算所需内存空间
	len += 32 * sizeof(wchar_t);//预留一些空间
	cmdStr = (wchar_t*)malloc(len);
	_stprintf(cmdStr, _T("open \"%s\" type mpegvideo alias S%d"), fileName, g_soundID);
	*pSound = g_soundID;//利用id进行引用音频文件
	++g_soundID;
	mciSendString(cmdStr, NULL, 0, NULL);
	free(cmdStr);
}