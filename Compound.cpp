#include "LayerObject.h"

int LayerSetObject::Compound(){
	vector<LayerObject>::iterator first;

	//初始化存放合成后图像的数据
	Pixel** data = new Pixel*[height];
	for (int h = 0; h < height; h++)
		data[h] = new Pixel [width];
	bool* blank=new bool[height*width];
	int i;//兼容VC6的设置
	for (i=0;i<height*width;i++)
		blank[i]=true;

	//逐层合成，从最低层开始
	for(int k=0;k<(int)vlso.size();k++)
	{
		first=vlso.begin();
		while(first!=vlso.end())
		{
			if (first->get_z()==k+1)
				break;
			first++;
		}

		if(first->get_visible()!=0)//忽略不可见图层
		{
			int tmpw=first->get_width();
			int tmph=first->get_height();
			int tmpx=first->get_x();
			int tmpy=first->get_y();
			//以下4行是确定覆盖某一图层时需要操作的图像坐标的范围
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
							///考虑透明度
							data[i][j].r=BYTE(src[i][j].r*(1-trp) + dest[i-tmpy][j-tmpx].r*trp);
							data[i][j].g=BYTE(src[i][j].g*(1-trp) + dest[i-tmpy][j-tmpx].g*trp);
							data[i][j].b=BYTE(src[i][j].b*(1-trp) + dest[i-tmpy][j-tmpx].b*trp);
						}
						else
						{
							///考虑混合模式
							switch(mode)
							{
							case 1://混合模式：变暗
								data[i][j].r = src[i][j].r < dest[i-tmpy][j-tmpx].r ? src[i][j].r : dest[i-tmpy][j-tmpx].r;
								data[i][j].g = src[i][j].g < dest[i-tmpy][j-tmpx].g ? src[i][j].g : dest[i-tmpy][j-tmpx].g;
								data[i][j].b = src[i][j].b < dest[i-tmpy][j-tmpx].b ? src[i][j].b : dest[i-tmpy][j-tmpx].b;
								break;
							case 2://混合模式：变亮
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
	//将合成结果存如cur_image
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
	
	cout<<"当前信息如下："<<endl;
	cout<<"画布宽："<<width<<"，高："<<height<<"；当前选中层为"<<cur_l->get_name()<<endl;
	cout<<"层名\tZ轴位置\t可视\t不透明\t混合\t位置x\t位置y\t来源\n";
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
int LayerSetObject::set_size(long width1,long height1)//设定画布大小
{
	this->width=width1;
	this->height=height1;
	return 1;
}
