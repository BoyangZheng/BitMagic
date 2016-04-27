/*
�㷨ԭ��
�ֱ�ͳ�Ƹ�����ɫֵ�ĵ�ĸ�������󾭹�һ���ı��������������ĳһλͼͼ����

mode	
	1 Rͨ��
    2 Gͨ��
    3 Bͨ��
    4 ������ɫͨ��
    5 RGBͨ�� �Ҷ���r*0.11+g*0.59+b*0.30��
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

	//ͳ�Ƹ�����ɫֵ�ĵ�ĸ���
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
	//�½�BitMapObject���Ա���ֱ��ͼ���
	BitMapObject Hismg(256,300);
	Pixel** newdata;
    newdata = new Pixel*[300];
    for (i = 0; i < 300; i++)
        newdata[i] = new Pixel[256];

	//ͳ�Ƴ�ԭʼֵ����һЩ�Ҷ�ֵ���м�ֵ����Ҫ��ֱ��ͼ���е�����
	//ȡ���лҶ�ƽ��ֵ+2����׼����Ϊ�����ʾ�ĻҶ�ֵ�����ڴ����ֵĲ�����ʾ��
	//С�ڴ����ֵİ����ûҶ����ص����*ֱ��ͼͼ���/�����ʾ�ĻҶ�ֵ�����㣬������ֱ��ͼͼ��
	double sum=0,sums=0;
	for(i=0;i<256;i++)
	{
		sum+=count[i];
		sums+=count[i]*count[i];
	}
	double M=sum/256,SD=sums/256-M*M,maxshow=M+2.0*sqrt(SD);

	for(i=0;i<256;i++)
	{
		for(j=0;j<300 && j<count[i]*300/maxshow;j++)//��������С
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

