#include "include.h"
#include "BitMapObject.h"

//Image Object Property

BitMapObject::BitMapObject()
{
    data=NULL;
    blank=NULL;
    width=-1;
    height=-1;
    data_start=-1;
}

BitMapObject::BitMapObject(long width1,long height1)
{
	width=width1;
	height=height1;
    data = new Pixel*[height];
    for (int h = 0; h < height; h++)
        data[h] = new Pixel [width];
	blank=new bool[height*width];
	for (int i=0;i<height*width;i++)
		blank[i]=false;
}

BitMapObject::BitMapObject(const BitMapObject& other)
{
	height = other.height;
	width = other.width;

	data = new Pixel* [height];
	int h;//¼æÈÝVC6
	for (h = 0; h < height; h++)
		data[h] = new Pixel[width];

	for (h = 0; h < height; h++)
		for (int w = 0; w < width; w++)
			data[h][w] = other.data[h][w]; 

	blank=new bool [width*height];
	for(int i=0;i<width*height;i++)
		blank[i]=other.blank[i];

	data_start=other.data_start;
}

BitMapObject::~BitMapObject()
{
	if (data!=NULL){
		for(int i=0;i<height;i++)
			delete [] data[i];
		delete[]data;
	}

	if (blank!=NULL)
		delete[] blank;
}

Pixel** BitMapObject::get_data() const
{
	return data;
}

bool* BitMapObject::get_blank() const
{
	return blank;
}

int BitMapObject::get_width() const
{
	return width;
}

int BitMapObject::get_height() const
{
	return height;
}

char* BitMapObject::get_type()
{
	return "BMP";
}

int BitMapObject::set_data(Pixel** px, long w, long h) 
{
	int i;//¼æÈÝVC6
    if (w != width || h != height) {
        for(i=0;i<height;i++)
            delete [] data[i];
        delete [] data;
        set_size(w, h);
        data=new Pixel* [height];
        for(i=0;i<height;i++)
            data[i]=new Pixel [width];
    }        
        
    for (i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            data[i][j].r = px[i][j].r;
            data[i][j].g = px[i][j].g;
            data[i][j].b = px[i][j].b;
        }

	return 1;
}

int BitMapObject::set_blank(bool *blk)
{
	if(blank!=NULL)
		delete[] blank; 
	
	blank=new bool[height*width];
	for (int i=0;i < height*width;i++)
		blank[i]=blk[i];
	return 1;
}

int BitMapObject::set_size(long width1,long height1)
{
	this->width=width1;
	this->height=height1;
	return 1;
}
