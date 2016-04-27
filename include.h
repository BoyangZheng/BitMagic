#ifndef Include_H_
#define Include_H_

#include <windows.h>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stdexcept>

using namespace std;

//全局设置
const int MAX_LINE_LENGTH=100;		//整行命令的最大长度
const int MAX_PARA=10;				//命令的最多参数个数
const int MAX_PARA_LENGTH=50;		//单个参数的最大长度
const int MAX_FILENAME_LENGTH=50;	//文件的最大长度
const int DEFAULT_IMAGE_WIDTH=800;	//默认图像宽，用于初始化BitMapObject
const int DEFAULT_IMAGE_HEIGHT=600;	//默认图像长，用于初始化BitMapObject
const int DEFAULT_CANVAS_WIDTH=800;	//默认画布宽，用于初始化LayerSetObject
const int DEFAULT_CANVAS_HEIGHT=600;//默认画布长，用于初始化LayerSetObject

#endif