/*
��������ã��������з�ʽ���û���������Ա�����������ļ��ж��壺

CommandObject.cpp------------------------------------------------��Ҫ����
	int Welcome();//��ӭ����
	int Welcome(char* ImageFile);//��ӭ���棬�������г���ʱ������ *.bmp
	int Welcome(char* ImageFile,char* ScriptFile);//��ӭ���棬�������г���ʱ������ *.bmp *.bmc
	int Goodbye();//��������

ParseCommand.cpp-------------------------------------------------�����
	int ParseCommand(LayerSetObject& lso,char* scmd);//���������ִ��

CommandAuxiliary.cpp---------------------------------------------�����������
	int cmd_split(char* scmd);//�������ַ���scmd�Կո�Ϊ�ָ�����
	int IsType(string s1,string s2);//���ͼ�飬s2Ϊ������չ��

Help.cpp---------------------------------------------------------����
	int help();//����
*/


#ifndef CommandObject_H_
#define CommandObject_H_

#include "include.h"
#include "ImageObject.h"
#include "BitMapObject.h"
#include "LayerObject.h"
#include "FunctionObject.h"
//#include <string>
//using namespace std;

class CommandObject
{
private:
	char parameter[MAX_PARA][MAX_PARA_LENGTH];//������������֧��MAX_PARA�������������������include.h
	int parameter_num;//�����������
	int cmd_split(char* scmd);//�������ַ���scmd�Կո�Ϊ�ָ�����
	int IsType(string s1,const string& s2);//���ͼ�飬s2Ϊ������չ��

public:
	CommandObject();
	~CommandObject();

	int ParseCommand(LayerSetObject& lso,char* scmd);//���������ִ��
	int help();//����
	int Watermark();//ˮӡ������
	int Welcome();//��ӭ����
	int Welcome(char* ImageFile);//��ӭ���棬�������г���ʱ������ *.bmp
	int Welcome(char* ImageFile,char* ScriptFile);//��ӭ���棬�������г���ʱ������ *.bmp *.bmc
	int Goodbye();//��������
};

#endif 