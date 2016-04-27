/*
��������ã�������������ʾλͼ�ļ����ࡣ���Ա���������������ļ��У�

Pixel.cpp---------------------------------���ص�ṹ�Ķ���

BitMapObject.cpp--------------------------ͼ��������Բ������������
    BitMapObject();
	BitMapObject::BitMapObject(long width1,long height1);
    BitMapObject(const BitMapObject& other);
    ~BitMapObject();
    Pixel** get_data() const;
    bool* get_blank() const;
    int get_width() const;
    int get_height() const;
	char* get_type();
    int set_data(Pixel **px, long w, long h);
    int set_blank(bool *blk);
    int set_size(long width, long height);

BitMapLoader.cpp--------------------------ͼ������ļ���ȡ
    int BitMapLoad(char* filename);

BitMapSave.cpp----------------------------ͼ���ౣ�浽�ļ�
    int BitMapSave(char* filename);
*/


#ifndef BitMapObject_H_
#define BitMapObject_H_

#include "include.h"
#include "ImageObject.h"

typedef unsigned char BYTE;

struct Pixel 
{
public:
    Pixel(int x=255, int y=255, int z=255);
    Pixel(const Pixel& other);
    Pixel& operator=(const Pixel& other);
    Pixel operator*(double other);
    Pixel operator+(const Pixel& other);
    BYTE r, g, b;//���ص��ɫ����ɫ����ɫ��ֵ
};

class BitMapObject: virtual public ImageObject
{
private:
    Pixel **data;//���ص�ֵ
    bool *blank; //���ص��Ƿ�͸��
    int width;
    int height;
    long data_start; // The number Indicates the start position of the image

public:
    BitMapObject();
	BitMapObject::BitMapObject(long width1,long height1);
    BitMapObject(const BitMapObject& other);
    ~BitMapObject();

    // Get Property
    Pixel** get_data() const;
    bool* get_blank() const;
    int get_width() const;
    int get_height() const;
	char* get_type();

    // Set Property
    int set_data(Pixel **px, long w, long h);
    int set_blank(bool *blk);
    int set_size(long width, long height);

    // ImageObject:Load and save
    int BitMapLoad(const char* filename);
    int BitMapSave(const char* filename);
};

#endif
