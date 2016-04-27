/*
该类的作用：以命令行方式让用户操作。成员函数在以下文件中定义：

CommandObject.cpp------------------------------------------------主要界面
	int Welcome();//欢迎画面
	int Welcome(char* ImageFile);//欢迎画面，用于运行程序时带参数 *.bmp
	int Welcome(char* ImageFile,char* ScriptFile);//欢迎画面，用于运行程序时带参数 *.bmp *.bmc
	int Goodbye();//结束画面

ParseCommand.cpp-------------------------------------------------命令处理
	int ParseCommand(LayerSetObject& lso,char* scmd);//分析命令，并执行

CommandAuxiliary.cpp---------------------------------------------命令处理辅助函数
	int cmd_split(char* scmd);//将命令字符串scmd以空格为分隔符拆开
	int IsType(string s1,string s2);//类型检查，s2为类型扩展名

Help.cpp---------------------------------------------------------帮助
	int help();//帮助
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
	char parameter[MAX_PARA][MAX_PARA_LENGTH];//命令参数，最多支持MAX_PARA个命令，两个常数定义在include.h
	int parameter_num;//命令参数个数
	int cmd_split(char* scmd);//将命令字符串scmd以空格为分隔符拆开
	int IsType(string s1,const string& s2);//类型检查，s2为类型扩展名

public:
	CommandObject();
	~CommandObject();

	int ParseCommand(LayerSetObject& lso,char* scmd);//分析命令，并执行
	int help();//帮助
	int Watermark();//水印设置向导
	int Welcome();//欢迎画面
	int Welcome(char* ImageFile);//欢迎画面，用于运行程序时带参数 *.bmp
	int Welcome(char* ImageFile,char* ScriptFile);//欢迎画面，用于运行程序时带参数 *.bmp *.bmc
	int Goodbye();//结束画面
};

#endif 