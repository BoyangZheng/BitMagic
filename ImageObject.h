/*
该类的作用：提供所有的图像类的原型
*/


#ifndef ImageObject_H_
#define ImageObject_H_

class ImageObject 
{
protected:
	int width;
	int height;
public:
	ImageObject(){};
	~ImageObject(){};
	virtual char* get_type()=0;//给出图像类型 
};

#endif


