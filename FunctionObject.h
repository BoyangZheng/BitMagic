/*
��������ã�ʵ�ֶ�ͼ����б��Σ������ĸ��ֹ��ܡ�
�����Ա�����ֱ������뺯����ͬ����cpp�ļ��С�
��ͼ����в����Ĺ��ܼ̳�LayerSetObject���μ�LayerObject.h��
*/

#ifndef FunctionObject_H_
#define FunctionObject_H_

#include "ImageObject.h"
#include "BitMapObject.h"
#include "LayerObject.h"

class FunctionObject:public LayerSetObject
{
public:
	virtual int Zoom(BitMapObject& bmp_obj,int neww,int newh);//��bmp_obj�������ţ�neww��newhΪ���ź�Ĵ�С
	virtual int Rotate(BitMapObject& bmp_obj,double angle);//bmp_obj��ʱ����תangle��
	virtual int SetBlank(BitMapObject& bmp_obj,Pixel pcolor,int tolerance);//��bmp_obj����͸��ɫ���ã�pcolorΪ��ɫ��toleranceΪ�ݲ�
	virtual int Histogram(BitMapObject& bmp_obj,int mode);//����bmp_obj��ֱ��ͼ�������ģʽ�μ���������
};

#endif
