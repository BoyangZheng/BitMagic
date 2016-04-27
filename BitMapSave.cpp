#include "include.h"
#include "BitMapObject.h"

int BitMapObject::BitMapSave(const char* filename)
{
	ofstream outfile;
	outfile.open(filename,ofstream::out|ofstream::binary);

	if (!outfile.good())
	{
		cout<<"outfile open error!"<<"\n ERROR NUM: 0"<<endl;
	}

	////////////////////////////////////////////////////////////////////////////
	////file header
	////////////////////////////////////////////////////////////////////////////
	outfile.write("BM",2);
        int i;
	long filesize = (width*3+4-width*3%4)*height+54;
	unsigned char *np=(unsigned char *)&filesize;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}
	for (i=0;i<4;i++)
	{
		outfile.put((char)0);
	}

	long offset = 54;//All the 24-bit bmp file are the same
	np = (unsigned char *)&offset;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}
	long headlength = 0x28;//All the same
	np = (unsigned char *)&headlength;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}
	np = (unsigned char *)&width;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}
	np = (unsigned char *)&height;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}

	//biBitCount, the information is 2-byte
	outfile.put((char)1);
	outfile.put((char)0);

	//bits of color, here is 24, the information is 2-byte
	outfile.put((char)24);
	outfile.put((char)0);

	//compress information, 0 is non-compressed
	for (i=0;i<4;i++)
	{
		outfile.put((char)0);
	}
	long datasize = width*height*24;
	np = (unsigned char *)&datasize;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}

	//resolving power in width and height
	long resolving = 3779;//96 pixels per inch
	np = (unsigned char *)&resolving;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}
	np = (unsigned char *)&resolving;
	for (i=0;i<4;i++)
	{
		outfile.put(*(np+i));
	}

	//color index, 0 - all the color are used
	for (i=0;i<4;i++)
	{
		outfile.put((char)0);
	}

	//important color, here we use all the colors, so not any special color
	for (i=0;i<4;i++)
	{
		outfile.put((char)0);
	}

	//////////////////////////////////////////////////////////////////////////
	//image data
	//////////////////////////////////////////////////////////////////////////
	long p = height-1;
	for(int h=height-1; h>=0; h--){
		for(int w=0; w < width; w++)
			if(this->blank[h*width+w])//注意：透明的点设置为灰色！
			{
				outfile.put((char)127);
				outfile.put((char)127);
				outfile.put((char)127);
			}
			else
			{
				outfile.put(this->data[h][w].b);
				outfile.put(this->data[h][w].g);
				outfile.put(this->data[h][w].r);
			}
		--p;
		if(width*3%4!=0){
			int tmp=4-(width*3%4);
			for(int i=0;i<tmp;i++)
                            outfile.put((char)0);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//file end
	//////////////////////////////////////////////////////////////////////////

	outfile.close();
	return 1;
}

