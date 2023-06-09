#include "ParticleManager.h"
#include "Map.h"
#include <iostream>
#include <time.h>
#include <list>
#include <graphics.h>
const int SCREENWIDTH = WIDTH_MAP;					// 屏幕的宽度
const int SCREENHEIGHT = HEIGHT_MAP;					// 屏幕的高度
const double g = 9.8;				//重力
const int len_max = 130;				// 光线的最大长度
const int h_max = SCREENHEIGHT - len_max;		// 光线能到达的最高高度
const double v_max = sqrt(2 * g * h_max / 10);	// 最大初速度 mgh=mv^2 重力势能=动能  
//除以10的缘故是公式是用m做单位,1m代表10个像素点
const int n_max = 5;				// 烟花在屏幕上同时存在最多的数量

//粒子束
class Particles
{
	struct Particle
	{
		int x;			//表示粒子的运动过程的x坐标
		int y;			//表示粒子的运动过程的y坐标
		int z = 0;		//  Z轴垂直屏幕输入
		double vy;		//  结构体里面的vy是每个粒子的y方向速度
		Particle(int xx, int yy, double vv) :x(xx), y(yy), vy(vv) {}
	};
public:
	Particles(int, int, float);
	void Draw();
	void Move();
	bool Finish() {
		return list_Particle.size() <= 1;
	}

	double vx;
	double vz = 0;
	float hsv_h;
	clock_t ct = 0;
	std::list<Particle> list_Particle;
};
Particles::Particles(int x, int y, float colorh = float(rand() % 256))
{
	hsv_h = colorh + rand() % 20;
	hsv_h = hsv_h > 255 ? hsv_h - 256 : hsv_h;//保证颜色值在0-255之间

	//摄像机方向看向z轴负方向
	double vm = v_max / 2 * (rand() % 5 + 15.0) / 25.0;
	double radian_xz = (rand() % 360) * PI / 180;//X轴偏向Z轴的角度0--2*PI
	double radian_xy = (rand() % 90) * PI / 180 + PI / 2;//X轴偏向Y轴的角度PI/2--PI
	vx = vm * cos(radian_xy) * cos(radian_xz);//向量在X轴的投影
	vz = vm * cos(radian_xy) * sin(radian_xz);//向量在Z轴的投影
	double vy = vm * sin(radian_xy); //向量在Y轴的投影

	//len表示粒子运动轨迹的长度，也可以认为是装填粒子的数量
	int len = rand() % 30 + 30;//数值越大，烟花爆炸的范围，散开的范围就越大。
	//这一段刻画的是爆炸花束粒子中的其中一条线
	while (len)
	{
		//目标像素位置＝初始像素位置+偏移米×10
		int xx = x + int(10 * vx * len / 200.0);

		//根据物理公式得到像素的y坐标
		double cvy = vy - g * len / 200.0;//v2 = v0-gt;
		int yy = y + int(10 * (cvy * cvy - vy * vy) / 2 / g);//vt^2-v0^2 = 2gx;
		list_Particle.push_back(Particle(xx, yy, cvy));
		len--;
	}
}
void Particles::Draw()
{
	int n = 0;
	auto size = list_Particle.size();
	for (auto& x : list_Particle)
	{
		if (x.x >= 0 && x.x < SCREENWIDTH && x.y >= 0 && x.y < SCREENHEIGHT)
		{
			//光束线条的尾端亮度最低，反之首端是比较亮的
			float cv = 0.2f + 0.8f * (size - n) / size - x.z;
			auto color = HSVtoRGB(hsv_h, 1.0f, cv > 0 ? cv : 0);
			if (x.z > 0)		// 如果烟花是往屏幕外扩散的话，就把像素点变大
			{
				//所谓变大就是画一个二个非常小的实心的圆
				setfillcolor(color);//设置当前设备填充颜色
				solidcircle(x.x, x.y, x.z / 80 > 1 ? 2 : 1);
			}
			else
				putpixel(x.x, x.y, color);
		}
		++n;
	}
}
void Particles::Move()
{
	if (ct == 0)//记录下创建粒子束时的时间
	{
		ct = clock();
		Draw();
		return;
	}
	for (int i = 0; i < 3 && list_Particle.size() > 1; i++)//
		list_Particle.pop_back();		// 画面每次刷新删除3个末尾粒子
	clock_t t = clock() - ct;
	ct = clock();
	for (auto& x : list_Particle)//爆炸光束之中一条光纤的粒子持续运动
	{
		double vy_cur = x.vy - g * t / 1000.0;//vy = v0-gt;
		x.x += int(10 * vx * t / 1000.0);//近似当作匀速直线运动
		x.y += int(10 * (vy_cur * vy_cur - x.vy * x.vy) / 2 / g);//vy*vy-v0*v0 = 2*g*s;
		x.z += int(10 * vz * t / 1000.0);//z方向也上也近似当作匀速直线运动
		x.vy = vy_cur;
	}
	Draw();
}



class Boom
{
public:
	Boom(int, int);
	void Move();
	bool isEmpty() const { return list_ParticleSwarm.empty(); }


	std::list<Particles> list_ParticleSwarm;
};
Boom::Boom(int x, int y)
{
	srand(time(nullptr));
	bool colorful = rand() % 100 < 20 ? true : false;//1/5的几率判断每一条光束是否应该为多种颜色
	float h = float(rand() % 256);
	int n = rand() % 5 + 45;//爆炸出来的光线量
	for (int i = 0; i < n; i++)
	{

		if (colorful) {//决定爆炸特效的爆炸光线每一条是否应该为多种颜色
			list_ParticleSwarm.push_back(Particles(x, y));
		}
		else
			list_ParticleSwarm.push_back(Particles(x, y, h));
	}
}
void Boom::Move()
{
	std::list<decltype(list_ParticleSwarm.begin())> toDel;
	for (auto it = list_ParticleSwarm.begin(); it != list_ParticleSwarm.end(); ++it)
	{
		if (it->Finish())//如果该粒子束群里的某单个粒子束的粒子数只剩下一个，则删除该粒子束，并且跳过
		{
			toDel.push_back(it);
			continue;
		}
		it->Move();
	}
	for (auto& x : toDel)
		list_ParticleSwarm.erase(x);
}
std::list<Boom> list_Boom;

clock_t ct = clock();
void createBoom(int x, int y) {
	list_Boom.push_back(Boom(x, y));//从光线顶部开始爆炸,创建爆炸对象
}
void update_Particle() {

	if (clock() - ct > 10)//每隔10帧才绘图一次
	{

		ct = clock();
		std::list<decltype(list_Boom.begin())> toDel2;
		for (auto it = list_Boom.begin(); it != list_Boom.end(); ++it)
		{
			if (it->isEmpty())//如果粒子束群为空
			{
				toDel2.push_back(it);//一句话来说就是储存哪个位置需要删除
				continue;
			}
			it->Move();
		}
		for (auto& it : toDel2)
			list_Boom.erase(it);
	}
}