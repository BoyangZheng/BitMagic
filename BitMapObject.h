/*
该类的作用：程序中用来表示位图文件的类。其成员函数定义在下列文件中：

Pixel.cpp---------------------------------像素点结构的定义

BitMapObject.cpp--------------------------图像类的属性操作与基本操作
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

BitMapLoader.cpp--------------------------图像类从文件读取
    int BitMapLoad(char* filename);

BitMapSave.cpp----------------------------图像类保存到文件
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
    BYTE r, g, b;//像素点红色、绿色、蓝色的值
};

class BitMapObject: virtual public ImageObject
{
private:
    Pixel **data;//像素点值
    bool *blank; //像素点是否透明
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
