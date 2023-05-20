#pragma once
#include "GameManager.h"
extern int g_soundID;
//ÒôÆµ±àºÅ
typedef int SOUND;
//¼ÓÔØÒôÆµ
void loadsound(SOUND* pSound, const wchar_t* fileName);
//ÔİÍ£ÒôÆµ
void pausesound(int sid);
//»Ö¸´ÒôÆµ
void resumesound(int sid);
//½áÊø²¥·Å
void stopsound(int sid);
//¿ªÊ¼²¥·Å
void playsound(int sid, int repeat);