#include "FunctionObject.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;

int FunctionObject::Zoom(BitMapObject& bmp_obj,int neww,int newh)
{
    int tmpw=bmp_obj.get_width()-1,tmph=bmp_obj.get_height()-1;
	double wfenpei=(tmpw+1)*1.0/neww;//从缩放后图像长宽逆向缩放的缩放倍数
	double hfenpei=(tmph+1)*1.0/newh;
	int i,j;//兼容VC6的设置

	//初始化缩放后图像的数据
	Pixel** newdata;        
	newdata=new Pixel* [newh];
    for(int h=0;h<newh;h++)
        newdata[h]=new Pixel [neww];
	bool* newblk=new bool[newh*neww];
	for(i=0;i<neww*newh;i++)
		newblk[i]=false;

    try {
        if(tmpw==0 || tmph==0)
            throw runtime_error("Can not deal with 1 pixel inmage...");
    } 
	catch (runtime_error err) 
	{
        cerr<<err.what()<<endl;
        return -1;
    }
	
    //缩放过程，使用双线性插值法
    for(i=0;i<newh;i++)
	{   
        for(j=0;j<neww;j++) 
		{
			double wp=j*wfenpei;
			double hp=i*hfenpei;
			int wp0=(int)wp;//插值法左上角点坐标
			int hp0=(int)hp;
			if(wp0>=tmpw)
			{
				int test;
				test=1;
			}
			int wp1=wp0+1 < tmpw ? wp0+1 : tmpw;
			int hp1=hp0+1 < tmph ? hp0+1 : tmph;
			double qw=wp-wp0;//权重
			double qh=hp-hp0;
                        
			Pixel p00=bmp_obj.get_data()[hp0][wp0];
			Pixel p01=bmp_obj.get_data()[hp0][wp1];
			Pixel p10=bmp_obj.get_data()[hp1][wp0];
			Pixel p11=bmp_obj.get_data()[hp1][wp1];
			newdata[i][j].b = (p10.b-p00.b) * qw + (p01.b-p00.b) * qh + (p11.b+p00.b-p10.b-p01.b) * qw * qh + p00.b;
			newdata[i][j].g = (p10.g-p00.g) * qw + (p01.g-p00.g) * qh + (p11.g+p00.g-p10.g-p01.g) * qw * qh + p00.g;
			newdata[i][j].r = (p10.r-p00.r) * qw + (p01.r-p00.r) * qh + (p11.r+p00.r-p10.r-p01.r) * qw * qh + p00.r;
		}
    }
        
    bmp_obj.set_data(newdata,neww,newh);
	bmp_obj.set_blank(newblk);
    return 1;
}