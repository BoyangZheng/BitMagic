/*
��������ã��ṩ���е�ͼ�����ԭ��
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
	virtual char* get_type()=0;//����ͼ������ 
};

#endif


