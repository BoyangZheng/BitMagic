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
	default:cout<<"�����÷�����\n��ȷ�÷� BitMagic [filename1] [filename2]\nfilename1��bmpͼ��\nfilename2��BitMagic�����ļ�"<<endl;
	}

	cmd.Goodbye();	
	remove("temp.bmp");//ɾ����ʱ�ļ�
	return 1;
}