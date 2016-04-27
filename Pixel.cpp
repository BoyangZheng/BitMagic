#include "include.h"
#include "BitMapObject.h"

Pixel::Pixel(const Pixel& other)
{
    r=other.r;
    g=other.g;
    b=other.b;
}

Pixel::Pixel(int x, int y, int z)
{
    r=x;
    g=y;
    b=z;
}

Pixel& Pixel::operator =(const Pixel& other)
{
	r=other.r;
    g=other.g;
    b=other.b;
    return *this;
}

Pixel Pixel::operator *(double other)
{
    Pixel temp;
    temp.r=static_cast<double>(r)*other;
    temp.g=static_cast<double>(g)*other;
    temp.b=static_cast<double>(b)*other;
    return temp;
}

Pixel Pixel::operator +(const Pixel& other)
{
    Pixel temp;
    temp.r=r+other.r;
    temp.g=g+other.g;
    temp.b=b+other.b;
    return temp;

}