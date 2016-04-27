/*
算法原理：
和目标色pcolor的RGB值每个分量的差都小于容差tolerance的颜色被判定为同一种颜色
这些同种颜色的像素点被设定为透明属性。
*/

#include "FunctionObject.h"
#include <cmath>
using namespace std;

int FunctionObject::SetBlank(BitMapObject& bmp_obj,Pixel pcolor,int tolerance)
{
	int w=bmp_obj.get_width(),h=bmp_obj.get_height();
	Pixel** newdata=bmp_obj.get_data();
	bool* newblk=new bool[w*h];

	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
			if (  ( newdata[i][j].b - pcolor.b)<=tolerance && ( newdata[i][j].b - pcolor.b)>=-1*tolerance 
				&&  ( newdata[i][j].g - pcolor.g)<=tolerance && ( newdata[i][j].g - pcolor.g)>=-1*tolerance 
				&& ( newdata[i][j].r - pcolor.r)<=tolerance && ( newdata[i][j].r - pcolor.r)>=-1*tolerance )
				newblk[i*w+j]=true;
			else
				newblk[i*w+j]=false;
	bmp_obj.set_blank(newblk);
	return 1;
}
