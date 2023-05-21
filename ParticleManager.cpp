#include "ParticleManager.h"
#include "Map.h"
#include <iostream>
#include <time.h>
#include <list>
#include <graphics.h>
const int SCREENWIDTH = WIDTH_MAP;					// ��Ļ�Ŀ��
const int SCREENHEIGHT = HEIGHT_MAP;					// ��Ļ�ĸ߶�
const double g = 9.8;				//����
const int len_max = 130;				// ���ߵ���󳤶�
const int h_max = SCREENHEIGHT - len_max;		// �����ܵ������߸߶�
const double v_max = sqrt(2 * g * h_max / 10);	// �����ٶ� mgh=mv^2 ��������=����  
//����10��Ե���ǹ�ʽ����m����λ,1m����10�����ص�
const int n_max = 5;				// �̻�����Ļ��ͬʱ������������

//������
class Particles
{
	struct Particle
	{
		int x;			//��ʾ���ӵ��˶����̵�x����
		int y;			//��ʾ���ӵ��˶����̵�y����
		int z = 0;		//  Z�ᴹֱ��Ļ����
		double vy;		//  �ṹ�������vy��ÿ�����ӵ�y�����ٶ�
		Particle(int xx, int yy, double vv) :x(xx), y(yy), vy(vv) {}
	};
public:
	Particles(int, int, float);
	void Draw() const;
	void Move();
	bool Finish() const { return list_Particle.size() <= 1; }

private:
	double vx;
	double vz = 0;
	float hsv_h;
	clock_t ct = 0;
	std::list<Particle> list_Particle;
};
Particles::Particles(int x, int y, float colorh = float(rand() % 256))
{
	hsv_h = colorh + rand() % 20;
	hsv_h = hsv_h > 255 ? hsv_h - 256 : hsv_h;//��֤��ɫֵ��0-255֮��

	//�����������z�Ḻ����
	double vm = v_max / 2 * (rand() % 5 + 15.0) / 25.0;
	double radian_xz = (rand() % 360) * PI / 180;//X��ƫ��Z��ĽǶ�0--2*PI
	double radian_xy = (rand() % 90) * PI / 180 + PI / 2;//X��ƫ��Y��ĽǶ�PI/2--PI
	vx = vm * cos(radian_xy) * cos(radian_xz);//������X���ͶӰ
	vz = vm * cos(radian_xy) * sin(radian_xz);//������Z���ͶӰ
	double vy = vm * sin(radian_xy); //������Y���ͶӰ

	//len��ʾ�����˶��켣�ĳ��ȣ�Ҳ������Ϊ��װ�����ӵ�����
	int len = rand() % 30 + 30;//��ֵԽ���̻���ը�ķ�Χ��ɢ���ķ�Χ��Խ��
	//��һ�ο̻����Ǳ�ը���������е�����һ����
	while (len)
	{
		//Ŀ������λ�ã���ʼ����λ��+ƫ���ס�10
		int xx = x + int(10 * vx * len / 200.0);

		//��������ʽ�õ����ص�y����
		double cvy = vy - g * len / 200.0;//v2 = v0-gt;
		int yy = y + int(10 * (cvy * cvy - vy * vy) / 2 / g);//vt^2-v0^2 = 2gx;
		list_Particle.push_back(Particle(xx, yy, cvy));
		len--;
	}
}
void Particles::Draw() const
{
	int n = 0;
	auto size = list_Particle.size();
	for (auto& x : list_Particle)
	{
		if (x.x >= 0 && x.x < SCREENWIDTH && x.y >= 0 && x.y < SCREENHEIGHT)
		{
			//�̻�������β��������ͣ���֮�׶��ǱȽ�����
			float cv = 0.2f + 0.8f * (size - n) / size - x.z;
			auto color = HSVtoRGB(hsv_h, 1.0f, cv > 0 ? cv : 0);
			if (x.z > 0)		// Z axis vertical screen inword����̻�������Ļ����ɢ�Ļ����Ͱ����ص���
			{
				//��ν�����ǻ�һ�������ǳ�С��ʵ�ĵ�Բ
				setfillcolor(color);//���õ�ǰ�豸�����ɫ
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
	if (ct == 0)//��¼�´���������ʱ��ʱ��
	{
		ct = clock();
		Draw();
		return;
	}
	for (int i = 0; i < 3 && list_Particle.size() > 1; i++)//
		list_Particle.pop_back();		// ����ÿ��ˢ��ɾ��3��ĩβ����
	clock_t t = clock() - ct;
	ct = clock();
	for (auto& x : list_Particle)//��ը����֮��һ�����˵����ӳ����˶�
	{
		double vy_cur = x.vy - g * t / 1000.0;//vy = v0-gt;
		x.x += int(10 * vx * t / 1000.0);//���Ƶ�������ֱ���˶�
		x.y += int(10 * (vy_cur * vy_cur - x.vy * x.vy) / 2 / g);//vy*vy-v0*v0 = 2*g*s;
		x.z += int(10 * vz * t / 1000.0);//z����Ҳ��Ҳ���Ƶ�������ֱ���˶�
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

private:
	std::list<Particles> list_ParticleSwarm;
};
Boom::Boom(int x, int y)
{
	srand(time(nullptr));
	bool colorful = rand() % 100 < 20 ? true : false;//1/5�ļ����ж�ÿһ�������Ƿ�Ӧ��Ϊ������ɫ
	float h = float(rand() % 256);
	int n = rand() % 5 + 45;//��ը�����Ĺ�����
	for (int i = 0; i < n; i++)
	{

		if (colorful) {//�����̻��ı�ը���ߣ�ÿһ���Ƿ�Ӧ��Ϊ������ɫ
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
		if (it->Finish())//�����������Ⱥ���ĳ������������������ֻʣ��һ������ɾ��������������������
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
	list_Boom.push_back(Boom(x, y));//�ӹ��߶�����ʼ��ը,�����̻�����
}
void update_Particle() {

	if (clock() - ct > 10)//ÿ��10֡�Ż�ͼһ��
	{

		ct = clock();
		std::list<decltype(list_Boom.begin())> toDel2;
		for (auto it = list_Boom.begin(); it != list_Boom.end(); ++it)
		{
			if (it->isEmpty())//���������ȺΪ��
			{
				toDel2.push_back(it);//һ�仰��˵���Ǵ����ĸ�λ����Ҫɾ��
				continue;
			}
			it->Move();
		}
		for (auto& it : toDel2)
			list_Boom.erase(it);
	}
}