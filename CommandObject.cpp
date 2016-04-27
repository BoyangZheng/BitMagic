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


	cout<<"****************\n* BitMagic 0.1 *\n****************\n��ѡ��һ��ܣ�\n[1]ˮӡ��ʦ-������\n[3]��Ҫ��������~\n[0]�˳�\n";
	cin>>cmmd;

	while( cmmd!=1 && cmmd!=2 && cmmd!=3 && cmmd!=4 && cmmd!=0 ) 
	{
		cout<<"��ѡ��һ��ܣ�"<<endl;
		cin>>cmmd;
	}

	switch(cmmd)
	{
	case 1:
		Watermark();
		break;
	case 3:
		cout<<"������Ҫ�򿪵�BMPͼ���·�����ļ���:";
		cin>>filename;
		while (lso.CreateLayer(filename)==-1)
			cin>>filename;	
		
		if(IsType(filename,"bmp"))
		{
			cout<<"bmpͼ�����ɣ�������������������������HELP��"<<endl;
			string scmd;
			do{
				getline(cin,scmd);
				char tscmd[MAX_LINE_LENGTH];//MAX_LINE_LENGTH������include.h
				strcpy(tscmd,scmd.c_str());
				ParseCommand(lso,tscmd);
			}while(strcmp(parameter[0],"exit")!=0);
		}
		else
			cout<<"���bmp�ļ���"<<endl;
		break;
	default:cout<<"��������"<<endl;
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

		cout<<"bmpͼ�����ɣ�������������������������HELP��"<<endl;
		string scmd;
		do{
			getline(cin,scmd);
			char tscmd[MAX_LINE_LENGTH];
			strcpy(tscmd,scmd.c_str());
			ParseCommand(lso,tscmd);
		}while(strcmp(parameter[0],"exit")!=0);
	}
	else
		cout<<"�����÷�����\n��ȷ�÷� BitMagic [filename1] [filename2]\nfilename1��bmpͼ��\nfilename2��BitMagic�����ļ�"<<endl;	
	
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
				throw runtime_error("ָ����bmc�ļ������ڣ�");
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
		cout<<"������ɡ�"<<endl;
	}
	else
		cout<<"�����÷�����\n��ȷ�÷� BitMagic [filename1] [filename2]\nfilename1��bmpͼ��\nfilename2��BitMagic�����ļ�"<<endl;
	
	return 1;
}

int CommandObject::Goodbye()
{
	cout<<"��л��ʹ��BitMagic 0.1"<<endl;
	cout<<"������"<<endl;
	cout<<"  3060601370 ֣����"<<endl;
	cout<<"  3060601314 ����"<<endl;
	cout<<"  3071102635 ����"<<endl;
	cout<<"  3080030116 ����"<<endl;
	return 1;
}

