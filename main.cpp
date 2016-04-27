#include "include.h"
#include <cstdlib>
#include "ImageObject.h"
#include "LayerObject.h"
#include "FunctionObject.h"
#include "CommandObject.h"


int main(int argc,char *argv[])
{
	CommandObject cmd;

	switch(argc)
	{
	case 1:cmd.Welcome();break;
	case 2:cmd.Welcome(argv[1]);break;
	case 3:cmd.Welcome(argv[1],argv[2]);break;
	default:cout<<"命令用法错误！\n正确用法 BitMagic [filename1] [filename2]\nfilename1：bmp图像\nfilename2：BitMagic命令文件"<<endl;
	}

	cmd.Goodbye();	
	remove("temp.bmp");//删除临时文件
	return 1;
}