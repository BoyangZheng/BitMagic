#include "FunctionObject.h"
#include <cmath>
using namespace std;

int FunctionObject::Rotate(BitMapObject& bmp_obj,double angle)
{
	//while(angle>=360) angle-=360;
	//while(angle<0) angle+=360;
	const double pi=3.1415926;
	double cosa=cos(angle*pi/180),sina=sin(angle*pi/180);
    int tmpw=bmp_obj.get_width();//原图像宽
	int tmph=bmp_obj.get_height();//原图像高
	int neww,newh;//旋转后图像大小
	neww=(int)(tmpw*abs(cosa)+tmph*abs(sina))+1;
	newh=(int)(tmpw*abs(sina)+tmph*abs(cosa))+1;

	//初始化 旋转后的图像的数据
	Pixel** newdata;
	newdata=new Pixel*[newh];
	for(int h=0;h<newh;++h)
		newdata[h]=new Pixel[neww];
	bool* newblk=new bool[newh*neww];
	
	//注意：i表示x；j表示y;；用法：newdata[j][i];
	int i,j;
	for(i=0;i<neww;++i)
		for(j=0;j<newh;++j) 
		{
			//将旋转后的图像的中心移到坐标中心，并开始反向旋转到原来图像的坐标系中
			double i1=i*1.0-(neww-1)/2.0, j1=j*1.0-(newh-1)/2.0;
			double i2=(cosa*i1-sina*j1) + (tmpw-1)/2.0, j2=(sina*i1+cosa*j1) + (tmph-1)/2.0;
			int i3=(int)i2,j3=(int)j2;
			if(0<=i2 && i2<tmpw-1 && 0<=j2 && j2<tmph-1)
			{
				newblk[j*neww+i]=false;
				/* 双线性插值法1：
				double qw=i2-i3;//横向的权重
				double qh=j2-j3;//纵向的权重
				tmp0=bmp_obj.get_data()[j3][i3] * qw + bmp_obj.get_data()[j3][i3+1] * (1-qw);
				tmp1=bmp_obj.get_data()[j3+1][i3] *qw + bmp_obj.get_data()[j3+1][i3+1] * (1-qw);
				newdata[j][i]=tmp0 * qh + tmp1 * (1-qh);
				*/ 
				/* 双线性插值法2;
				Pixel p00=bmp_obj.get_data()[j3][i3];
				Pixel p01=bmp_obj.get_data()[j3][i3+1];
				Pixel p10=bmp_obj.get_data()[j3+1][i3];
				Pixel p11=bmp_obj.get_data()[j3+1][i3+1];
				newdata[j][i].b = (p10.b-p00.b) * qw + (p01.b-p00.b) * qh + (p11.b+p00.b-p10.b-p01.b) * qw * qh + p00.b;
				newdata[j][i].g = (p10.g-p00.g) * qw + (p01.g-p00.g) * qh + (p11.g+p00.g-p10.g-p01.g) * qw * qh + p00.g;
				newdata[j][i].r = (p10.r-p00.r) * qw + (p01.r-p00.r) * qh + (p11.r+p00.r-p10.r-p01.r) * qw * qh + p00.r;
				由于最邻近法效果最优，采取下法：*/
				newdata[j][i]=bmp_obj.get_data()[j3][i3];
			}
			else
				if( (i2==tmpw-1 && j2==tmph-1) || (i2==tmpw-1 && j2<tmph-1) || (i2<tmpw-1 && j2==tmph-1) )
					newdata[j][i]=bmp_obj.get_data()[j3][i3]*1.0;
				else//如果旋转后的图像反向旋转到原图像的坐标系后，有些像素点落在原图像范围之外，那么标志为透明
				{
					newdata[j][i].b=255;
					newdata[j][i].g=255;
					newdata[j][i].r=255;
					newblk[j*neww+i]=true;			
				}
		}

	bmp_obj.set_data(newdata,neww,newh);
	bmp_obj.set_blank(newblk);
	return 1;
}