/*
该类的作用：实现对图像进行变形，调整的各种功能。
该类成员函数分别定义在与函数名同名的cpp文件中。
对图层进行操作的功能继承LayerSetObject（参见LayerObject.h）
*/

#ifndef FunctionObject_H_
#define FunctionObject_H_

#include "ImageObject.h"
#include "BitMapObject.h"
#include "LayerObject.h"

class FunctionObject:public LayerSetObject
{
public:
	virtual int Zoom(BitMapObject& bmp_obj,int neww,int newh);//对bmp_obj进行缩放，neww，newh为缩放后的大小
	virtual int Rotate(BitMapObject& bmp_obj,double angle);//bmp_obj逆时针旋转angle度
	virtual int SetBlank(BitMapObject& bmp_obj,Pixel pcolor,int tolerance);//对bmp_obj进行透明色设置，pcolor为颜色，tolerance为容差
	virtual int Histogram(BitMapObject& bmp_obj,int mode);//给出bmp_obj的直方图，里面的模式参见函数定义
};

#endif
