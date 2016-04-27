#include "CommandObject.h"

int CommandObject::Watermark()
{
	cout<<"+++++++++++++++++++"<<endl;
	cout<<"+水印大师-设置向导+"<<endl;
	cout<<"+++++++++++++++++++"<<endl;
	cout<<""<<endl;
	
	cout<<"1 请问您会将该设置保存在哪个文件中？（请输入文件名，将生成以此为文件名，以bmc为扩展名的BitMagic命令文件）"<<endl;
	string bmc;
	cin>>bmc;
	bmc+=".bmc";
	ofstream outfile;
	outfile.open(bmc.c_str(),ofstream::out);

	string logo;
	do{
		cout<<"2 请输入水印图像的文件名（请加上扩展名，仅限24位BMP文件）"<<endl;
		cin>>logo;
	}while(IsType(logo,"bmp")==0);
	outfile<<"create "<<logo<<endl;

	int locx,locy;
	cout<<"3.1 您要将水印左边界在据目标图像左边界百分之几画布宽的位置？（不用输入%）"<<endl;
	cin>>locx;
	cout<<"3.2 您要将水印上边界在据目标图像上边界百分之几画布高的位置？（不用输入%)"<<endl;
	cin>>locy;
	outfile<<"moveto "<<locx<<"% "<<locy<<"%"<<endl;

	char choice;
	do{
		cout<<"4 水印需要改变大小吗？（y/n）"<<endl;
		cin>>choice;
	}while(choice!='Y' && choice!='y' && choice!='N' && choice!='n');
	if(choice=='Y' || choice=='y')
	{
		int zoomx,zoomy;
		cout<<"4.1 那么水印的宽相当于目标图像的百分之几？（不用输入%）"<<endl;
		cin>>zoomx;
		cout<<"4.2 那么水印的高相当于目标图像的百分之几？（不用输入%）"<<endl;
		cin>>zoomy;
		outfile<<"zoom "<<zoomx<<"% "<<zoomy<<"%"<<endl;
	}
	
	char choice2;
	do{
		cout<<"5 水印需要旋转吗？（y/n）"<<endl;
		cin>>choice2;
	}while(choice2!='Y' && choice2!='y' && choice2!='N' && choice2!='n');
	if(choice2=='Y' || choice2=='y')
	{
		int angle;
		cout<<"5.1 那么逆时针旋转多少角度呢？"<<endl;
		cin>>angle;
		outfile<<"rotate "<<angle<<endl;
	}

	char choice3;
	do{
		cout<<"6 需要将水印的某种颜色设置为透明色吗？（y/n）"<<endl;
		cin>>choice3;
	}while(choice3!='Y' && choice3!='y' && choice3!='N' && choice3!='n');
	if(choice3=='Y' || choice3=='y')
	{
		int nr,ng,nb,tole;
		cout<<"6.1 这种颜色的RGB值是多少？（请分开输入三个介于0~255的整数，白色的RGB为255，255，255）"<<endl;
		cin>>nr>>ng>>nb;
		cout<<"6.2 容差范围是多少（0~40）"<<endl;
		cin>>tole;
		outfile<<"setblank "<<nr<<" "<<ng<<" "<<nb<<" "<<tole<<endl;
	}	
	
	int mixmode,trp;
	cout<<"7 水印加在目标图像上，用哪种混合方式？（0：覆盖；1：变暗；2：变亮）"<<endl;
	cin>>mixmode;
	if(mixmode==0)//覆盖为默认混合方式，只有在这种方式下，才可以使用不透明度属性
	{
		cout<<"7.1 水印的不透明度是？（0~100的整数）"<<endl;
		cin>>trp;
		outfile<<"transparency "<<trp<<endl;
	}
	else
	{
		outfile<<"mixmode "<<mixmode<<endl;
	}

	outfile<<"save self"<<endl;
	outfile<<"exit"<<endl;
	cout<<"水印设置完成！现在您可以在命令行环境下输入bitmagic [name].bmp "<<bmc<<"来直接添加水印了！"<<endl;
	cout<<""<<endl;
	outfile.close();

	char choice4;
	do{
		cout<<"需要批量处理吗？（y/n）"<<endl;
		cin>>choice4;
	}while(choice4!='Y' && choice4!='y' && choice4!='N' && choice4!='n');
	if(choice4=='Y' || choice4=='y')
	{
		ofstream batfile;
		batfile.open("bmc.bat",ofstream::out);
		cout<<"  请输入这些图像的文件名，以end结束……"<<endl;
		string imgfile;
		cin>>imgfile;
		while(imgfile!=string("end"))
		{			
			if(IsType(imgfile,"bmp")==0)
				cout<<"非bmp文件，略过"<<endl;
			else
				batfile<<"bitmagic "<<imgfile<<" "<<bmc<<endl;
			cin>>imgfile;
		}
		batfile.close();
		cout<<"已经生成bmb.bat您可以运行它直接实现批量处理！"<<endl;
	}
	
	return 1;
}
