#include "CommandObject.h"

int CommandObject::Watermark()
{
	cout<<"+++++++++++++++++++"<<endl;
	cout<<"+ˮӡ��ʦ-������+"<<endl;
	cout<<"+++++++++++++++++++"<<endl;
	cout<<""<<endl;
	
	cout<<"1 �������Ὣ�����ñ������ĸ��ļ��У����������ļ������������Դ�Ϊ�ļ�������bmcΪ��չ����BitMagic�����ļ���"<<endl;
	string bmc;
	cin>>bmc;
	bmc+=".bmc";
	ofstream outfile;
	outfile.open(bmc.c_str(),ofstream::out);

	string logo;
	do{
		cout<<"2 ������ˮӡͼ����ļ������������չ��������24λBMP�ļ���"<<endl;
		cin>>logo;
	}while(IsType(logo,"bmp")==0);
	outfile<<"create "<<logo<<endl;

	int locx,locy;
	cout<<"3.1 ��Ҫ��ˮӡ��߽��ھ�Ŀ��ͼ����߽�ٷ�֮���������λ�ã�����������%��"<<endl;
	cin>>locx;
	cout<<"3.2 ��Ҫ��ˮӡ�ϱ߽��ھ�Ŀ��ͼ���ϱ߽�ٷ�֮�������ߵ�λ�ã�����������%)"<<endl;
	cin>>locy;
	outfile<<"moveto "<<locx<<"% "<<locy<<"%"<<endl;

	char choice;
	do{
		cout<<"4 ˮӡ��Ҫ�ı��С�𣿣�y/n��"<<endl;
		cin>>choice;
	}while(choice!='Y' && choice!='y' && choice!='N' && choice!='n');
	if(choice=='Y' || choice=='y')
	{
		int zoomx,zoomy;
		cout<<"4.1 ��ôˮӡ�Ŀ��൱��Ŀ��ͼ��İٷ�֮��������������%��"<<endl;
		cin>>zoomx;
		cout<<"4.2 ��ôˮӡ�ĸ��൱��Ŀ��ͼ��İٷ�֮��������������%��"<<endl;
		cin>>zoomy;
		outfile<<"zoom "<<zoomx<<"% "<<zoomy<<"%"<<endl;
	}
	
	char choice2;
	do{
		cout<<"5 ˮӡ��Ҫ��ת�𣿣�y/n��"<<endl;
		cin>>choice2;
	}while(choice2!='Y' && choice2!='y' && choice2!='N' && choice2!='n');
	if(choice2=='Y' || choice2=='y')
	{
		int angle;
		cout<<"5.1 ��ô��ʱ����ת���ٽǶ��أ�"<<endl;
		cin>>angle;
		outfile<<"rotate "<<angle<<endl;
	}

	char choice3;
	do{
		cout<<"6 ��Ҫ��ˮӡ��ĳ����ɫ����Ϊ͸��ɫ�𣿣�y/n��"<<endl;
		cin>>choice3;
	}while(choice3!='Y' && choice3!='y' && choice3!='N' && choice3!='n');
	if(choice3=='Y' || choice3=='y')
	{
		int nr,ng,nb,tole;
		cout<<"6.1 ������ɫ��RGBֵ�Ƕ��٣�����ֿ�������������0~255����������ɫ��RGBΪ255��255��255��"<<endl;
		cin>>nr>>ng>>nb;
		cout<<"6.2 �ݲΧ�Ƕ��٣�0~40��"<<endl;
		cin>>tole;
		outfile<<"setblank "<<nr<<" "<<ng<<" "<<nb<<" "<<tole<<endl;
	}	
	
	int mixmode,trp;
	cout<<"7 ˮӡ����Ŀ��ͼ���ϣ������ֻ�Ϸ�ʽ����0�����ǣ�1���䰵��2��������"<<endl;
	cin>>mixmode;
	if(mixmode==0)//����ΪĬ�ϻ�Ϸ�ʽ��ֻ�������ַ�ʽ�£��ſ���ʹ�ò�͸��������
	{
		cout<<"7.1 ˮӡ�Ĳ�͸�����ǣ���0~100��������"<<endl;
		cin>>trp;
		outfile<<"transparency "<<trp<<endl;
	}
	else
	{
		outfile<<"mixmode "<<mixmode<<endl;
	}

	outfile<<"save self"<<endl;
	outfile<<"exit"<<endl;
	cout<<"ˮӡ������ɣ������������������л���������bitmagic [name].bmp "<<bmc<<"��ֱ�����ˮӡ�ˣ�"<<endl;
	cout<<""<<endl;
	outfile.close();

	char choice4;
	do{
		cout<<"��Ҫ���������𣿣�y/n��"<<endl;
		cin>>choice4;
	}while(choice4!='Y' && choice4!='y' && choice4!='N' && choice4!='n');
	if(choice4=='Y' || choice4=='y')
	{
		ofstream batfile;
		batfile.open("bmc.bat",ofstream::out);
		cout<<"  ��������Щͼ����ļ�������end��������"<<endl;
		string imgfile;
		cin>>imgfile;
		while(imgfile!=string("end"))
		{			
			if(IsType(imgfile,"bmp")==0)
				cout<<"��bmp�ļ����Թ�"<<endl;
			else
				batfile<<"bitmagic "<<imgfile<<" "<<bmc<<endl;
			cin>>imgfile;
		}
		batfile.close();
		cout<<"�Ѿ�����bmb.bat������������ֱ��ʵ����������"<<endl;
	}
	
	return 1;
}
