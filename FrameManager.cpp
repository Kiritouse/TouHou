#include <time.h>
#include <Windows.h>
#include <graphics.h>
#include "FrameManager.h"
//负责帧数的初始化
void iniFrame(Frame frame, int tf_total, int tf_zawarudo, int tf_resume, int tf_pause) {
	frame.f_total = tf_total;
	frame.f_zawarudo = tf_zawarudo;
	frame.f_resume = tf_resume;
	frame.f_pause = tf_pause;
}
