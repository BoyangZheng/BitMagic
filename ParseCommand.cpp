#include "CommandObject.h"
//#include <iostream>
//#include <cstring>
//#include <string>
//#include <sstream> 
//#include <fstream>
//using namespace std;

int CommandObject::ParseCommand(LayerSetObject& lso,char* scmd)
{
	FunctionObject func;

	parameter_num=0;
	cmd_split(scmd);
	int wrong_cmd=1;//标志命令输入是否出错，0为无错。

	//图像功能命令
	if(strcmp(parameter[0],"rotate")==0)
		if(parameter_num==2)
		{
			//将字符串转换成数字，下同
			stringstream ss(parameter[1]); 
			double temp; 
			ss >> temp;
			
			func.Rotate(*(lso.get_cur_l()),temp);
			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"zoom")==0)
		if(parameter_num==3)
		{
			int newx,newy;
			//用户输入zoom命令有两种形式，分别是设为绝对数字，缩放成画布相应的比例（数字后加%以示区别）。
			if (parameter[1][strlen(parameter[1])-1]=='%')
			{
				parameter[1][strlen(parameter[1])-1]=0;
				parameter[2][strlen(parameter[2])-1]=0;
				stringstream ss;
				ss<<parameter[1]<<" "<<parameter[2];
				ss >> newx;
				ss >> newy;
				//newx=(int)(lso.get_cur_l()->get_width()*newx/100);
				//newy=(int)(lso.get_cur_l()->get_height()*newy/100);
				newx=(int)(lso.get_width()*newx/100);
				newy=(int)(lso.get_height()*newy/100);
			}
			else
			{
				stringstream ss;
				ss<<parameter[1]<<" "<<parameter[2];
				ss >> newx;
				ss >> newy;
			}	
			func.Zoom(*(lso.get_cur_l()),newx,newy);
			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"setblank")==0)
		if(parameter_num==5)
		{
			int br,bg,bb;
			stringstream ss;
			int tolerance;
			ss<<parameter[1]<<" "<<parameter[2]<<" "<<parameter[3]<<" "<<parameter[4];//输入欲设定为透明的颜色的R G B 值
			ss>>br>>bg>>bb;
			Pixel bcolor(br,bg,bb);
			ss>>tolerance;
			func.SetBlank(*(lso.get_cur_l()),bcolor,tolerance);

			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"histogram")==0)
		if(parameter_num==1)
		{
			lso.Compound();
			func.Histogram(lso.get_cur_image(),5);//默认以RGB形式输出直方图
			wrong_cmd=0;
		}
		else
			if(parameter_num==2)
			{
				stringstream ss(parameter[1]); 
				int temp; 
				ss >> temp;

				lso.Compound();
				func.Histogram(lso.get_cur_image(),temp);
				wrong_cmd=0;
			}

	//图层管理命令
	if(strcmp(parameter[0],"info")==0)
		if(parameter_num==1)
		{
			lso.ShowDetail();
			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"compound")==0)
		if(parameter_num==1)
		{
			lso.Compound();
			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"setsize")==0)
		if(parameter_num==3)
		{
			int neww,newh;
			stringstream ss;
			ss<<parameter[1]<<" "<<parameter[2];
			ss >> neww;
			ss >> newh;
			lso.set_size(neww,newh);
			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"create")==0)
			if(parameter_num==2)
			{
				lso.CreateLayer(parameter[1]);
				wrong_cmd=0;
			}

	if(strcmp(parameter[0],"delete")==0)
		if(parameter_num==1)
		{
			string lname=lso.get_cur_l()->get_name();
			for(string::size_type i=0;i!=lname.size();++i) 
				lname[i]=tolower(lname[i]);

			lso.DeleteLayer(lname);
			wrong_cmd=0;
		}
		else
			if(parameter_num==2)
			{
				lso.DeleteLayer(parameter[1]);
				wrong_cmd=0;
			}

	if(strcmp(parameter[0],"select")==0)
			if(parameter_num==2)
			{
				lso.SelectLayer(parameter[1]);
				wrong_cmd=0;
			}

	if(strcmp(parameter[0],"duplicate")==0)
		if(parameter_num==1)
		{
			lso.Duplicate();
			wrong_cmd=0;
		}

	//图层调整命令
	if(strcmp(parameter[0],"setz")==0)
			if(parameter_num==2)
			{
				if(strcmp(parameter[1],"top")==0){
					lso.ChangeLayerZindex(1);
					wrong_cmd=0;
				}
				if(strcmp(parameter[1],"bottom")==0){
					lso.ChangeLayerZindex(2);
					wrong_cmd=0;
				}
				if(strcmp(parameter[1],"up")==0){
					lso.ChangeLayerZindex(3);
					wrong_cmd=0;
				}
				if(strcmp(parameter[1],"down")==0){
					lso.ChangeLayerZindex(4);
					wrong_cmd=0;
				}
			}

	if(strcmp(parameter[0],"moveto")==0)
		if(parameter_num==3)
		{
			int newx,newy; 

			if (parameter[1][strlen(parameter[1])-1]=='%')
			{
				parameter[1][strlen(parameter[1])-1]=0;
				parameter[2][strlen(parameter[2])-1]=0;
				stringstream ss;
				ss<<parameter[1]<<" "<<parameter[2];
				ss >> newx;
				ss >> newy;
				newx=(int)(lso.get_width()*newx/100);
				newy=(int)(lso.get_height()*newy/100);
			}
			else
			{
				stringstream ss;
				ss<<parameter[1]<<" "<<parameter[2];
				ss >> newx;
				ss >> newy;
			}	
			//func.Zoom(*(lso.get_cur_l()),newx,newy);
			wrong_cmd=0;

			stringstream ss;//
				ss<<parameter[1]<<" "<<parameter[2];
				ss >> newx;
				ss >> newy;

				lso.get_cur_l()->set_location(newx,newy);
				wrong_cmd=0;
			}

	if(strcmp(parameter[0],"transparency")==0)
			if(parameter_num==2)
			{
				stringstream ss(parameter[1]); 
				int temp; 
				ss >> temp;

				lso.get_cur_l()->set_transparency(temp);
				wrong_cmd=0;
			}

	if(strcmp(parameter[0],"mixmode")==0)
			if(parameter_num==2)
			{
				stringstream ss(parameter[1]); 
				int temp; 
				ss >> temp;

				lso.get_cur_l()->set_mix_mode(temp);
				wrong_cmd=0;
			}

	if(strcmp(parameter[0],"setname")==0)
			if(parameter_num==2)
			{
				string strtemp(parameter[1]);
				lso.get_cur_l()->set_name(strtemp);
				wrong_cmd=0;
			}

	//程序命令
	if(strcmp(parameter[0],"save")==0)
		if(parameter_num==1)
		{
			lso.SaveImage("temp.bmp");
			wrong_cmd=0;
		}
		else
			if(parameter_num==2)
			{
				if(strcmp(parameter[1],"self")==0)
				{
					if(lso.SelectLayer("l0"))
						;
					string tname=lso.get_cur_l()->get_source();
					tname=string("mod_")+tname;
					lso.SaveImage(tname.c_str());
					wrong_cmd=0;
				}
				else
				{
					lso.SaveImage(parameter[1]);
					wrong_cmd=0;
				}
			}

	if(strcmp(parameter[0],"show")==0)
		if(parameter_num==1)
		{
			lso.Show();
			wrong_cmd=0;
		}

	if(strcmp(parameter[0],"help")==0)
		if(parameter_num==1)
		{
			help();
			wrong_cmd=0;
		}
		
	if(strcmp(parameter[0],"exit")==0)
			wrong_cmd=0;

	if(wrong_cmd && parameter_num>=1)
		cout<<"命令用法错误！"<<endl;

	return 1;
}
