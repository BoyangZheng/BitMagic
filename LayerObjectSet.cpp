#include "LayerObject.h"

LayerSetObject::LayerSetObject(){
	long width=DEFAULT_CANVAS_WIDTH;//Ĭ�ϻ�����������include.h
	long height=DEFAULT_CANVAS_HEIGHT;//Ĭ�ϻ����ߣ�������include.h
}

LayerSetObject::~LayerSetObject(){
}

//get Property
vector<LayerObject>::iterator LayerSetObject::get_cur_l(){
	return this->cur_l;
}
long LayerSetObject::get_width() const{
	return this->width;
}
long LayerSetObject::get_height() const{
	return this->height;
}

LayerObject& LayerSetObject::get_cur_image(){
	return this->cur_image;
}

//Layers Operation
int LayerSetObject::SelectLayer(string lname){
	vector<LayerObject>::iterator first=vlso.begin();

	while(first!=vlso.end())
	{
		string tmps=first->get_name();
		for(string::size_type i=0;i!=tmps.size();++i) 
			tmps[i]=tolower(tmps[i]);
		if(tmps == lname)
		{
			cur_l=first;
			break;
		}
		first++;
	}

	if(first==vlso.end())
		return 0;
	else
	{
		cout<<"ͼ�� "<<cur_l->get_name()<<" ��ѡ��"<<endl;
		return 1;
	}
}

int LayerSetObject::CreateLayer(){
	return 1;
}

int LayerSetObject::CreateLayer(char *filename){
	LayerObject ltemp;
	if (ltemp.BitMapLoad(filename)==-1)
		return -1;//ͼ���ʧ��
	
	vlso.push_back(ltemp);
	cur_l=vlso.begin()+vlso.size()-1;//ָ����ͼ�㣬֮��Ĳ��������趨��ͼ������
	cur_l->set_z(vlso.size());//���´�ͼ���������
	//�趨��ͼ������
	stringstream ss;
	string newname;
	ss<<"L"<<(ltemp.id++);
	ss>>newname;
	cur_l->set_name(newname);
	//�趨��ͼ����Դ�ļ�
	string newsource(filename);
	cur_l->set_source(newsource);

	if(vlso.size()-1==0)
	{
		//����ǵ�һ�δ�ͼ�㣬��ô��һ�δ򿪵�ͼ��ĸ߿���Ϊ�����ĸ߿�
		width=cur_l->get_width();
		height=cur_l->get_height();		
		//��ʼ��cur_image
		Pixel** data = new Pixel*[height];
		for (int h = 0; h < height; h++)
			data[h] = new Pixel [width];
		bool* blank=new bool[height*width];
		for (int i=0;i<height*width;i++)
			blank[i]=true;
		cur_image.set_data(data,width,height);
		cur_image.set_blank(blank);
	}

	return 1;
}

int LayerSetObject::DeleteLayer(string lname){
	vector<LayerObject>::iterator first=vlso.begin();

	if(vlso.size()==1)
	{
		cout<<"ֻʣ��һ�㣬����ɾ����"<<endl;
		return 0;
	}
	else
	{
		while(first!=vlso.end())
		{
			string tmps=first->get_name();
			for(string::size_type i=0;i!=tmps.size();++i) 
				tmps[i]=tolower(tmps[i]);
			if(tmps == lname)
			{
				cur_l=first;
				break;
			}
			first++;
		}

		if(first==vlso.end())
		{
			cout<<"δ�ҵ��ò�"<<endl;
			return 0;
		}
		else
		{
			//�趨����ͼ����Z���ϵ�˳��
			int cur_z=cur_l->get_z();
			int tmp_z;
			first=vlso.begin();
			while(first!=vlso.end())
			{
				if( (tmp_z=first->get_z()) > cur_z)
					first->set_z(tmp_z-1);
				first++;
			}
			//vlso.erase(cur_l);//�������ú�vlso������Ԫ�ص�data��blank��ָ�ĵ�ַ���ֲ��䣬Ȼ����ָ��ַ������ȴ���ܷ����˸ı䣬������˸������·�ʽʵ�֣�
			string dname=cur_l->get_name();
			vector<LayerObject> vlso2(vlso);
			vlso.clear();
			first=vlso2.begin();
			while(first!=vlso2.end())
			{
				if(first->get_name()!=dname)
					vlso.push_back(*first);
				first++;
			}
			//erase end
			cur_l=vlso.begin();
			return 1;
		}
	}
}

int LayerSetObject::Duplicate(){
	LayerObject ltemp((*cur_l));
	ltemp.set_name(ltemp.get_name() + "C");

	vlso.push_back(ltemp);
	cur_l=vlso.begin()+vlso.size()-1;
	
	cur_l->set_z(vlso.size());//���ƺ��ͼ���������
	return 1;
}

int LayerSetObject::ChangeLayerZindex(int id){
	//id:1 ��ǰ��������2 ���ף�3 ����һ�㣻4 ����һ��
	vector<LayerObject>::iterator first=vlso.begin();
	int cur_z=cur_l->get_z();
	int tmp_z;

	switch(id)
	{
	case 1:
		while(first!=vlso.end())
		{
			if( (tmp_z=first->get_z()) > cur_z)
				first->set_z(tmp_z-1);
			first++;
		}
		cur_l->set_z(vlso.size());
		break;
	case 2:
		while(first!=vlso.end())
		{
			if( (tmp_z=first->get_z()) < cur_z)
				first->set_z(tmp_z+1);
			first++;
		}
		cur_l->set_z(1);
		break;
	case 3:
		if(cur_z==vlso.size())
		{
			cout<<"�Ѿ�����㣡"<<endl;
			return 0;
		}
		else
		{
			while(first!=vlso.end())
			{
				if( (tmp_z=first->get_z()) == (cur_z+1) )
					first->set_z(tmp_z-1);
				first++;
			}
			cur_l->set_z(cur_z+1);
			break;
		}
	case 4:
		if(cur_z==1)
		{
			cout<<"�Ѿ�����ײ㣡"<<endl;
			return 0;
		}
		else
		{
			while(first!=vlso.end())
			{
				if( (tmp_z=first->get_z()) == (cur_z-1) )
					first->set_z(tmp_z+1);
				first++;
			}
			cur_l->set_z(cur_z-1);
			break;
		}
	default:
		cout<<"��������δ�Ե�ǰ��������²��ƶ�"<<endl;
		return 0;
	}

	cout<<"�����ƶ�ͼ�����"<<endl;
	this->ShowDetail();
	return 1;
}

int LayerSetObject::ChangeLayerName(string lname){
	cur_l->set_name(lname);
	return 1;
}

