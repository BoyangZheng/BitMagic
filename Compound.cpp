#include "LayerObject.h"

int LayerSetObject::Compound(){
	vector<LayerObject>::iterator first;

	//��ʼ����źϳɺ�ͼ�������
	Pixel** data = new Pixel*[height];
	for (int h = 0; h < height; h++)
		data[h] = new Pixel [width];
	bool* blank=new bool[height*width];
	int i;//����VC6������
	for (i=0;i<height*width;i++)
		blank[i]=true;

	//���ϳɣ�����Ͳ㿪ʼ
	for(int k=0;k<(int)vlso.size();k++)
	{
		first=vlso.begin();
		while(first!=vlso.end())
		{
			if (first->get_z()==k+1)
				break;
			first++;
		}

		if(first->get_visible()!=0)//���Բ��ɼ�ͼ��
		{
			int tmpw=first->get_width();
			int tmph=first->get_height();
			int tmpx=first->get_x();
			int tmpy=first->get_y();
			//����4����ȷ������ĳһͼ��ʱ��Ҫ������ͼ������ķ�Χ
			int wb= tmpx>0 ? tmpx : 0;
			int hb= tmpy>0 ? tmpy : 0;
			int we= tmpx+tmpw<width  ? tmpx+tmpw : width;
			int he= tmpy+tmph<height ? tmpy+tmph : height;
			Pixel** src=data;
			Pixel** dest=first->get_data();
			double trp=first->get_transparency()*1.0 /100;
			int mode=first->get_mix_mode();

			for(i=hb;i<he;i++)
				for(int j=wb;j<we;j++)
				{
					if(first->get_blank()[(i-tmpy)*tmpw+(j-tmpx)]==false)
					{
						if(mode==0)
						{
							///����͸����
							data[i][j].r=BYTE(src[i][j].r*(1-trp) + dest[i-tmpy][j-tmpx].r*trp);
							data[i][j].g=BYTE(src[i][j].g*(1-trp) + dest[i-tmpy][j-tmpx].g*trp);
							data[i][j].b=BYTE(src[i][j].b*(1-trp) + dest[i-tmpy][j-tmpx].b*trp);
						}
						else
						{
							///���ǻ��ģʽ
							switch(mode)
							{
							case 1://���ģʽ���䰵
								data[i][j].r = src[i][j].r < dest[i-tmpy][j-tmpx].r ? src[i][j].r : dest[i-tmpy][j-tmpx].r;
								data[i][j].g = src[i][j].g < dest[i-tmpy][j-tmpx].g ? src[i][j].g : dest[i-tmpy][j-tmpx].g;
								data[i][j].b = src[i][j].b < dest[i-tmpy][j-tmpx].b ? src[i][j].b : dest[i-tmpy][j-tmpx].b;
								break;
							case 2://���ģʽ������
								data[i][j].r = src[i][j].r > dest[i-tmpy][j-tmpx].r ? src[i][j].r : dest[i-tmpy][j-tmpx].r;
								data[i][j].g = src[i][j].g > dest[i-tmpy][j-tmpx].g ? src[i][j].g : dest[i-tmpy][j-tmpx].g;
								data[i][j].b = src[i][j].b > dest[i-tmpy][j-tmpx].b ? src[i][j].b : dest[i-tmpy][j-tmpx].b;
								break;
							}
						}
						blank[i*width+j]=false;
					}
				}
		}
	}
	//���ϳɽ������cur_image
	cur_image.set_data(data,width,height);
	cur_image.set_blank(blank);

	return 1;
}

int LayerSetObject::SaveImage(const char* filename){
	Compound();
	cur_image.BitMapSave(filename);
	return 1;
}

int LayerSetObject::Show(){
	Compound();
	SaveImage("temp.bmp");
	//ShellExecute(NULL,"open","temp.bmp",NULL,NULL,SW_SHOW); //Not available in VS2005/2008 without some Header Files
	return 1;
}

int LayerSetObject::ShowDetail(){
	vector<LayerObject>::iterator first=vlso.begin();
	
	cout<<"��ǰ��Ϣ���£�"<<endl;
	cout<<"������"<<width<<"���ߣ�"<<height<<"����ǰѡ�в�Ϊ"<<cur_l->get_name()<<endl;
	cout<<"����\tZ��λ��\t����\t��͸��\t���\tλ��x\tλ��y\t��Դ\n";
	while(first!=vlso.end())
	{
		cout<<first->get_name()<<"\t";
		cout<<first->get_z()<<"\t";
		cout<<first->get_visible()<<"\t";
		cout<<first->get_transparency()<<"\t";
		cout<<first->get_mix_mode()<<"\t";
		cout<<first->get_x()<<"\t";
		cout<<first->get_y()<<"\t";
		cout<<first->get_source()<<endl;
		first++;
	}
	return 1;
}

//Set Property 
int LayerSetObject::set_size(long width1,long height1)//�趨������С
{
	this->width=width1;
	this->height=height1;
	return 1;
}
