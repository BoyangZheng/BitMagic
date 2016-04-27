#include "include.h"
#include "BitMapObject.h"

int BitMapObject::BitMapLoad(const char* filename)
{
	ifstream infile;
	infile.open(filename,ifstream::in|ifstream::binary);
	try
	{
		if(!infile.good())
			throw runtime_error("输入文件打开错误!请重新输入：");
	}
	catch (runtime_error err) {
        cerr<<err.what()<<endl;
        return -1;
    }

	// Get the width of the image
	infile.seekg(18,ios::beg);
	int tmp = 1;
	int i;//兼容VC6的设置，下同
	width = 0;
	for (i = 0; i < 4; i++)
	{
		width += infile.get() * tmp;
		tmp *= 256;
	}

	// Get the height of the image
	tmp = 1;
	height = 0;
	for (i = 0; i < 4; i++)
	{
		height += infile.get() * tmp;
		tmp *= 256;
	}

	// Get the image data start position 
	infile.seekg(10, ios::beg);
	data_start = 0;
	tmp = 1;
	for (i = 0; i < 4; i++)
	{
		data_start += infile.get() * tmp;
		tmp *= 256;
	}

	// Get the image data
	infile.seekg(data_start,ios::beg);

	data = new Pixel* [height];
	for(i=0;i<height;i++)
	    data[i]=new Pixel [width];
	blank = new bool[width * height];

	//bmp图像编码是从左到右，从下到上的
	long h;
	for(h=height-1; h>=0; h--)
	{
		for(long w = 0; w < width; w++)
		{
		    data[h][w].b = infile.get();
		    data[h][w].g = infile.get();
		    data[h][w].r = infile.get();
		    blank[h*width+w]=false;
		}
		// the data of each row must be 4*n, if not insert 0;
		if(width * 3 % 4 != 0)
		{
			infile.seekg( 4 - (width * 3 % 4), ios::cur);
		}
	}

	infile.close();
	return 1;
}

