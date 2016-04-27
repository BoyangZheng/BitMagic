#include "CommandObject.h"
#include <iostream>
#include <string>
using namespace std;

int CommandObject::help()
{
	string str;

	cout<<"==============������⣺ͼ���������=============="<<endl;
	cout<<"create filename"<<endl;
	cout<<"  ��;���½�ͼ�㣬�������ļ���Ϊfilename��ͼ��ִ�к���ͼ�㱻ѡ��"<<endl;
	cout<<"  ������char* filename�����޵�ǰĿ¼��bmpͼ���ļ���"<<endl;
	cout<<"  ʾ����create temp.bmp"<<endl;
	cout<<""<<endl;
	cout<<"delete"<<endl;
	cout<<"  ��;��ɾ����ǰѡ��ͼ��"<<endl;
	cout<<""<<endl;
	cout<<"delete layername"<<endl;
	cout<<"  ��;��ɾ������Ϊlayername��ͼ��"<<endl;
	cout<<"  ������layernameͼ�����ƣ���ͨ��info����鿴"<<endl;
	cout<<"  ʾ����delete L0"<<endl;
	cout<<""<<endl;
	cout<<"duplicate"<<endl;
	cout<<"  ��;�����Ƶ�ǰͼ�㣬ִ�к���ͼ��λ����ϣ��ұ�ѡ��"<<endl;
	cout<<""<<endl;
	cout<<"info"<<endl;
	cout<<"  ��;��������ǰ�ĵ���Ϣ������������С����ǰѡ��ͼ�㣬ÿ����Ϣ"<<endl;
	cout<<""<<endl;
	cout<<"select layername"<<endl;
	cout<<"  ��;��ѡ������Ϊlayername��ͼ��"<<endl;
	cout<<"  ������layernameͼ�����ƣ���ͨ��info����鿴"<<endl;
	cout<<"  ʾ����select L0"<<endl;
	cout<<""<<endl;
	cout<<"setsize width height"<<endl;
	cout<<"  ��;������������Ϊ��width���أ���height���ء�������ԭ��ͼ�����»������Ͻ�"<<endl;
	cout<<"  ������int width,height����������ֵ��С��1000"<<endl;
	cout<<"  ʾ����setsize 800 600"<<endl;
	cout<<""<<endl;
	cout<<"������������������� "<<endl;
	getline(cin,str);
	cout<<"==============������⣺ͼ���������=============="<<endl;
	cout<<"moveto x y"<<endl;
	cout<<"  ��;����ѡ��ͼ���Ƶ���Ի�����x��y��λ��"<<endl;
	cout<<"  ������int x��y;����ԭ�㣨0��0��λ�����Ͻǣ�x>0������ԭ���ҷ���y>0������ԭ���·�"<<endl;
	cout<<"  ʾ����moveto 20 15"<<endl;
	cout<<""<<endl;
	cout<<"mixmode mode"<<endl;
	cout<<"  ��;������ѡ��ͼ��Ļ��ģʽ"<<endl;
	cout<<"  ������int mode��ֵ����Ϊ"<<endl;
	cout<<"            0 ����"<<endl;
	cout<<"            1 �䰵�������²��нϰ�����ɫΪ���ɫ��"<<endl;
	cout<<"            2 �����������²��н�������ɫΪ���ɫ��"<<endl;
	cout<<"            ע�⣬��mode��Ϊ0ʱ����͸��������ʧЧ"<<endl;
	cout<<"  ʾ����mixmode 1"<<endl;
	cout<<""<<endl;
	cout<<"setname name"<<endl;
	cout<<"  ��;����ѡ��ͼ������Ƹ�Ϊname"<<endl;
	cout<<"  ������char* name"<<endl;
	cout<<"  ʾ����setname myL"<<endl;
	cout<<""<<endl;
	cout<<"setz mode"<<endl;
	cout<<"  ��;����ѡ��ͼ�����ϻ������ƶ�"<<endl;
	cout<<"  ������char* mode��ֵ����Ϊ"<<endl;
	cout<<"            top         ��ǰ���ö�"<<endl;
	cout<<"            bottom  ��ǰ���õ�"<<endl;
	cout<<"            up          ��ǰ��������һ��"<<endl;
	cout<<"            down     ��ǰ��������һ��"<<endl;
	cout<<"  ʾ����setz top"<<endl;
	cout<<""<<endl;
	cout<<"transparency trp"<<endl;
	cout<<"  ��;������ѡ��ͼ���͸����"<<endl;
	cout<<"  ������int trp��trp��ΧΪ0~100��ע�⣬��mode��Ϊ0ʱ����͸��������ʧЧ"<<endl;
	cout<<"  ʾ����transparency 10"<<endl;
	cout<<""<<endl;
	cout<<"������������������� "<<endl;
	getline(cin,str);
	cout<<"==============������⣺ͼ���������=============="<<endl;
	cout<<"rotate angle"<<endl;
	cout<<"  ��;����ʱ����תangle�ȵ�ǰѡ��ͼ���ͼ��"<<endl;
	cout<<"  ������double angle��"<<endl;
	cout<<"  ʾ����rotate 45"<<endl;
	cout<<""<<endl;
	cout<<"zoom width height"<<endl;
	cout<<"  ��;����ѡ��ͼ���ͼ���������Ϊwidth���أ���Ϊheight���ص�ͼ��"<<endl;
	cout<<"  ������int width;int height;����width��heightֵ������1000��"<<endl;
	cout<<"  ʾ����zoom 800 600"<<endl;
	cout<<""<<endl;
	cout<<"zoom zoomx zoomy"<<endl;
	cout<<"  ��;����ѡ��ͼ���ͼ��Ŀ��Ŵ���С������������zoomx%���߷Ŵ���С������������"<<endl;
	cout<<""<<endl;
	cout<<"zoomy%"<<endl;
	cout<<"  ������zoomx��zoomyΪ�ַ����Σ���ʾ��Ϊ0%��100%"<<endl;
	cout<<"  ʾ����zoom 200% 200%"<<endl;
	cout<<""<<endl;
	cout<<"setblank red green blue tolerance"<<endl;
	cout<<"  ��;������ѡ��ͼ���ͼ�񣬽���ɫΪ�ԣ�red��green��blue��Ϊ��׼�ģ��ݲ�Ϊtolerance"<<endl;
	cout<<""<<endl;
	cout<<"����ɫ��Ϊ͸��"<<endl;
	cout<<"  ������red��green��blue��ΧΪ0~255��tolerance������Ϊ10��һ��С��32��"<<endl;
	cout<<"  ʾ����setblank 255 255 255 10 ������ɫ��Ϊ͸��ɫ��"<<endl;
	cout<<""<<endl;
	cout<<"histogram [mode]"<<endl;
	cout<<"  ��;��������ǰͼ���ֱ��ͼ"<<endl;
	cout<<"  ������mode��ֵ����Ϊ"<<endl;
	cout<<"            1 Rͨ��"<<endl;
	cout<<"            2 Gͨ��"<<endl;
	cout<<"            3 Bͨ��"<<endl;
	cout<<"            4 ������ɫͨ��"<<endl;
	cout<<"            5 RGBͨ��"<<endl;
	cout<<"            ���modeδ��������Ĭ��Ϊ5"<<endl;
	cout<<"  ʾ����histogram 5"<<endl;
	cout<<" "<<endl;
	cout<<"������������������� "<<endl;
	getline(cin,str);
	cout<<"==============������⣺��������=============="<<endl;
	cout<<"exit"<<endl;
	cout<<"  ��;���˳�����"<<endl;
	cout<<""<<endl;
	cout<<"help"<<endl;
	cout<<"  ��;����ð���"<<endl;
	cout<<""<<endl;
	cout<<"save"<<endl;
	cout<<"  ��;�����浱ǰ�޸Ľ����temp.bmp"<<endl;
	cout<<""<<endl;
	cout<<"save filename"<<endl;
	cout<<"  ��;�����浱ǰ�޸Ľ��������Ϊfilename���ļ�"<<endl;
	cout<<"  ������char* filename��bmpͼ���ļ�����"<<endl;
	cout<<"  ʾ����save out.bmp"<<endl;
	cout<<""<<endl;
	cout<<"show"<<endl;
	cout<<"  ��;�������ⲿ������ʾ��ǰ�޸ĺ��ͼ��"<<endl;

	return 1;
}