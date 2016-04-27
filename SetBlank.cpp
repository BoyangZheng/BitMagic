/*
�㷨ԭ��
��Ŀ��ɫpcolor��RGBֵÿ�������ĲС���ݲ�tolerance����ɫ���ж�Ϊͬһ����ɫ
��Щͬ����ɫ�����ص㱻�趨Ϊ͸�����ԡ�
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
