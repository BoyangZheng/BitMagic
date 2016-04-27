#include "CommandObject.h"

CommandObject::CommandObject()
{
}

CommandObject::~CommandObject()
{
}

int CommandObject::Welcome()
{
	int cmmd;
//	string scmd;
	LayerSetObject lso;
	char filename[50];


	cout<<"****************\n* BitMagic 0.1 *\n****************\n请选择一项功能：\n[1]水印大师-设置向导\n[3]我要玩命令行~\n[0]退出\n";
	cin>>cmmd;

	while( cmmd!=1 && cmmd!=2 && cmmd!=3 && cmmd!=4 && cmmd!=0 ) 
	{
		cout<<"请选择一项功能！"<<endl;
		cin>>cmmd;
	}

	switch(cmmd)
	{
	case 1:
		Watermark();
		break;
	case 3:
		cout<<"请输入要打开的BMP图像的路径和文件名:";
		cin>>filename;
		while (lso.CreateLayer(filename)==-1)
			cin>>filename;	
		
		if(IsType(filename,"bmp"))
		{
			cout<<"bmp图像打开完成，请输入命令。如需帮助，请输入HELP。"<<endl;
			string scmd;
			do{
				getline(cin,scmd);
				char tscmd[MAX_LINE_LENGTH];//MAX_LINE_LENGTH定义在include.h
				strcpy(tscmd,scmd.c_str());
				ParseCommand(lso,tscmd);
			}while(strcmp(parameter[0],"exit")!=0);
		}
		else
			cout<<"请打开bmp文件！"<<endl;
		break;
	default:cout<<"发生错误！"<<endl;
	}

	return 1;
}

int CommandObject::Welcome(char* filename)
{
	LayerSetObject lso;

	if(IsType(filename,"bmp"))
	{
		while (lso.CreateLayer(filename)==-1)
			cin>>filename;

		cout<<"bmp图像打开完成，请输入命令。如需帮助，请输入HELP。"<<endl;
		string scmd;
		do{
			getline(cin,scmd);
			char tscmd[MAX_LINE_LENGTH];
			strcpy(tscmd,scmd.c_str());
			ParseCommand(lso,tscmd);
		}while(strcmp(parameter[0],"exit")!=0);
	}
	else
		cout<<"命令用法错误！\n正确用法 BitMagic [filename1] [filename2]\nfilename1：bmp图像\nfilename2：BitMagic命令文件"<<endl;	
	
	return 1;
}

int CommandObject::Welcome(char* filename1,char* filename2)
{
	LayerSetObject lso;

	if(IsType(filename1,"bmp") && IsType(filename2,"bmc"))
	{
		while (lso.CreateLayer(filename1)==-1)
			cin>>filename1;	
		ifstream infile;
		try{
			infile.open(filename2,ifstream::in);
			if(!infile.good())
				throw runtime_error("指定的bmc文件不存在！");
		}
		catch(runtime_error err)
		{
			cerr<<err.what()<<endl;
			return -1;
		}
		string scmd;
		do{
			getline(infile,scmd);
			char tscmd[MAX_LINE_LENGTH];
			strcpy(tscmd,scmd.c_str());
			ParseCommand(lso,tscmd);
		}while(strcmp(parameter[0],"exit")!=0);
		infile.close();
		cout<<"处理完成。"<<endl;
	}
	else
		cout<<"命令用法错误！\n正确用法 BitMagic [filename1] [filename2]\nfilename1：bmp图像\nfilename2：BitMagic命令文件"<<endl;
	
	return 1;
}

int CommandObject::Goodbye()
{
	cout<<"感谢您使用BitMagic 0.1"<<endl;
	cout<<"开发者"<<endl;
	cout<<"  3060601370 郑博阳"<<endl;
	cout<<"  3060601314 吴粤"<<endl;
	cout<<"  3071102635 王益"<<endl;
	cout<<"  3080030116 李骁"<<endl;
	return 1;
}

