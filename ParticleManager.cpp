#include "ParticleManager.h"
#include "Map.h"
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

class ParticleSwarm
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
	ParticleSwarm(int, int, float);
	void Draw() const;
	void Move();
	bool Finish() const { return vec.size() <= 1; }

private:
	double vx;
	double vz = 0;
	float hsv_h;
	clock_t ct = 0;
	std::list<Particle> vec;
};
ParticleSwarm::ParticleSwarm(int x, int y, float colorh = float(rand() % 256))
{
	hsv_h = colorh + rand() % 20;
	hsv_h = hsv_h > 255 ? hsv_h - 256 : hsv_h;//保证颜色值在0-255之间

	//Z轴的负向对着人，即人对着屏幕的方向为Z轴的正向,与OpenGL的相反
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
		vec.push_back(Particle(xx, yy, cvy));
		len--;
	}
}
void ParticleSwarm::Draw() const
{
	int n = 0;
	auto size = vec.size();
	for (auto& x : vec)
	{
		if (x.x >= 0 && x.x < SCREENWIDTH && x.y >= 0 && x.y < SCREENHEIGHT)
		{
			//烟花线条的尾端亮度最低，反之首端是比较亮的
			float cv = 0.2f + 0.8f * (size - n) / size - x.z; //原来的float cv = 0.2f + 0.8f * (size - n) / size - x.z / 40 * 0.1f
			auto color = HSVtoRGB(hsv_h, 1.0f, cv > 0 ? cv : 0);
			if (x.z < 0)		// Z axis vertical screen inword如果烟花是往屏幕外扩散的话，就把像素点变大
			{
				//所谓变大就是画一个二个非常小的实心的圆
				setfillcolor(color);//设置当前设备填充颜色
				solidcircle(x.x, x.y, abs(x.z) / 80 > 1 ? 2 : 1);
			}
			else
				putpixel(x.x, x.y, color);
		}
		++n;
	}
}
void ParticleSwarm::Move()
{
	if (ct == 0)
	{
		ct = clock();
		Draw();
		return;
	}
	for (int i = 0; i < 3 && vec.size() > 1; i++)//
		vec.pop_back();		// Delete particles for shortening length画面每次刷新删除3个末尾粒子
	clock_t t = clock() - ct;
	ct = clock();
	for (auto& x : vec)//爆炸花束之中一条光纤的粒子持续运动
	{
		double vy_cur = x.vy - g * t / 1000.0;//vy = v0-gt;
		x.x += int(10 * vx * t / 1000.0);//近似当作匀速直线运动
		x.y += int(10 * (vy_cur * vy_cur - x.vy * x.vy) / 2 / g);//vy*vy-v0*v0 = 2*g*s;
		x.z += int(10 * vz * t / 1000.0);//z方向也上也近似当作匀速直线运动
		x.vy = vy_cur;
	}
	Draw();
}



class Fireworks
{
public:
	Fireworks(int, int);
	void Move();
	bool Empty() const { return vec.empty(); }

private:
	std::list<ParticleSwarm> vec;
};
Fireworks::Fireworks(int x, int y)
{
	bool colorful = rand() % 100 < 20 ? true : false;//1/5的几率判断
	float h = float(rand() % 256);
	int n = rand() % 5 + 45;//烟花升到顶点后，爆炸出来的光线量
	for (int i = 0; i < n; i++)
	{
		if (colorful)//决定烟花的爆炸光线，每一条是否是同一颜色的。1/5的几率判断
			vec.push_back(ParticleSwarm(x, y));
		else
			vec.push_back(ParticleSwarm(x, y, h));
	}
}
void Fireworks::Move()
{
	std::list<decltype(vec.begin())> toDel;
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		if (it->Finish())//如果该粒子群里的粒子数只剩下一个，则跳过
		{
			toDel.push_back(it);
			continue;
		}
		it->Move();//如果粒子群里的粒子数不只是剩下一个，则继续描画它的轨迹
	}
	for (auto& x : toDel)
		vec.erase(x);
}
std::list<Fireworks> vec2;

clock_t ct = clock();
void createFireworks(int x, int y) {
	vec2.push_back(Fireworks(x, y));//从光线顶部开始爆炸,创建烟花对象


}
void update_Particle() {

	if (clock() - ct > 10)//每隔10帧才绘图一次
	{

		ct = clock();
		std::list<decltype(vec2.begin())> toDel2;
		for (auto it = vec2.begin(); it != vec2.end(); ++it)
		{
			if (it->Empty())
			{
				toDel2.push_back(it);//一句话来说就是储存哪个位置需要删除
				continue;
			}
			it->Move();
		}
		for (auto& it : toDel2)
			vec2.erase(it);
	}
}