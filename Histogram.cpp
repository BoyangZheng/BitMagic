/*
算法原理：
分别统计各种颜色值的点的个数，最后经过一定的比例调整，输出到某一位图图像上

mode	
	1 R通道
    2 G通道
    3 B通道
    4 所有颜色通道
    5 RGB通道 灰度以r*0.11+g*0.59+b*0.30记
*/

#include "FunctionObject.h"
#include <cmath>
using namespace std;

int FunctionObject::Histogram(BitMapObject& bmp_obj,int mode)
{
	long count[256];
	int h=bmp_obj.get_height() , w=bmp_obj.get_width();
	int i;
	long j;

	for(i=0;i<256;i++)
		count[i]=0;

	//统计各种颜色值的点的个数
	//

	for(i=0;i<h;i++)
		for(j=0;j<w;j++){
			int k1,k2,k3;
			k1=bmp_obj.get_data()[i][j].b;
			k2=bmp_obj.get_data()[i][j].g;
			k3=bmp_obj.get_data()[i][j].r;

			switch(mode)
			{
			case 1:
				count[k1]++;
				break;
			case 2:
				count[k2]++;
				break;
			case 3:
				count[k3]++;
				break;
			case 4:
				count[k1]++;
				count[k2]++;
				count[k3]++;
				break;
			case 5:
				int k=(int)(k1*0.11+k2*0.59+k3*0.30);
				count[k]++;
				break;
			}
		}
	//新建BitMapObject，以保存直方图结果
	BitMapObject Hismg(256,300);
	Pixel** newdata;
    newdata = new Pixel*[300];
    for (i = 0; i < 300; i++)
        newdata[i] = new Pixel[256];

	//统计出原始值后，有一些灰度值上有极值，需要对直方图进行调整。
	//取所有灰度平均值+2个标准差作为最大显示的灰度值，大于此数字的不予显示，
	//小于此数字的按（该灰度像素点个数*直方图图像高/最大显示的灰度值）计算，最后输出直方图图像。
	double sum=0,sums=0;
	for(i=0;i<256;i++)
	{
		sum+=count[i];
		sums+=count[i]*count[i];
	}
	double M=sum/256,SD=sums/256-M*M,maxshow=M+2.0*sqrt(SD);

	for(i=0;i<256;i++)
	{
		for(j=0;j<300 && j<count[i]*300/maxshow;j++)//按比例减小
		{
			newdata[299-j][i].b=0;
			newdata[299-j][i].g=0;
			newdata[299-j][i].r=0;
		}
		//set other colors white
		for(;j<300;j++)
		{
			newdata[299-j][i].b=240;
			newdata[299-j][i].g=240;
			newdata[299-j][i].r=240;
		}
	}
	Hismg.set_data(newdata,256,300);
	Hismg.BitMapSave("Histogram.bmp");
	return 1;
}

