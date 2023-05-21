#pragma once
struct Frame
{
	int f_total;
	int f_resume;
	int f_pause;
};
void iniFrame(Frame frame, int tf_total, int tf_resume, int tf_pause);
