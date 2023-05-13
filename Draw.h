#pragma once
#include <conio.h>
#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib,"Winmm.lib") 
/// <summary>
/// 透明贴图函数
/// </summary>
/// <param name="dstimg">目标 IMAGE 对象指针。NULL 表示默认窗体</param>
/// <param name="x">目标贴图位置(要贴在哪里)</param>
/// <param name="y">目标贴图位置(要贴在哪里)</param>
/// <param name="srcimg">源图片</param>
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
/// <summary>
/// 绘制部分区域透明贴图函数
/// </summary>
/// <param name="dstimg">目标 IMAGE 对象指针。NULL 表示默认窗体</param>
/// <param name="xt">目标绘图区域起点坐标</param>
/// <param name="yt">目标绘图区域起点坐标</param>
/// <param name="wt">目标绘图区域绘制宽度</param>
/// <param name="ht">目标绘图区域绘制高度</param>
/// <param name="xo">源文件绘制所选择的起点</param>
/// <param name="yo">源文件绘制所选择的起点</param>
/// <param name="wo">源文件绘制所选择的宽度</param>
/// <param name="ho">源文件绘制所选择的高度</param>
/// <param name="srcimg">源图片指针</param>
void transparentimage(IMAGE* dstimg, int xt, int yt, int wt, int ht,
	int xo, int yo, int wo, int ho, IMAGE* srcimg);
/// <summary>
/// 可自定义绘制宽度的
/// </summary>
/// <param name="dstimg">目标 IMAGE 对象指针。NULL 表示默认窗体</param>
/// <param name="x">目标绘图区域起点坐标</param>
/// <param name="y">目标绘图区域起点坐标</param>
/// <param name="w">目标绘图区域绘制宽度<</param>
/// <param name="h">目标绘图区域绘制高度</param>
/// <param name="srcimg">源图片指针</param>
void transparentimage(IMAGE* dstimg, int x, int y, int w, int h, IMAGE* srcimg);
/// <summary>
/// 实现半透明效果
/// </summary>
/// <param name="dstimg"></param>
/// <param name="xt"></param>
/// <param name="yt"></param>
/// <param name="wt"></param>
/// <param name="ht"></param>
/// <param name="xo"></param>
/// <param name="yo"></param>
/// <param name="wo"></param>
/// <param name="ho"></param>
/// <param name="srcimg"></param>
/// <param name="weight">半透明权重值，0是全透明，255是透明</param>
void transparentimage(IMAGE* dstimg, int xt, int yt, int wt, int ht,
	int xo, int yo, int wo, int ho, IMAGE* srcimg, int weight);

