#include "CommandObject.h"
//#include <iostream>
//#include <cstring>
//#include <string>
//using namespace std;

int CommandObject::IsType(string s1,const string& s2)
{
	int len=s1.size();
	int index=len;
	int k=0;

	while(s1[--index]!='.');

	string temp(len-index-1,' ');

	for(int j=index+1;j<len;j++)
		temp[k++]=s1[j];
	temp[k]=0;

	if(temp==s2)
		return 1;
	else 
		return 0;
}

int CommandObject::cmd_split(char* scmd)
{	
	int len=strlen(scmd);
	int flag=1;
	
	//判断是否完全是空格，用于忽略输入的命令时空格和回车
	for(int j=0;j<len;j++)
		if(scmd[j]!=' ')
			flag=0;

	if(flag)
		strcpy(parameter[0],"  ");
	else
	{
		int i=0,k=0;
		
		//将命令转成小写形式
		for(int j=0;j<len;j++)
			if(scmd[j]>'A' && scmd[j]<'Z')
				scmd[j]=scmd[j]+32;
		//以空格分开字符串
		while(i<len)
		{
			if(scmd[i]!=' ')
			{
				parameter[parameter_num][k++]=scmd[i];
				if(i+1<len && scmd[i+1]==' ')
				{
					parameter[parameter_num][k]=0;
					parameter_num++;
					k=0;
				}
			}
			i++;
		}
		if(scmd[len-1]!=' ')
		{
			parameter[parameter_num][k]=0;
			parameter_num++;
		}
	}
	return 1;
}
