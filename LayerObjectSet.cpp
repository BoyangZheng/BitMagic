#include "LayerObject.h"

LayerSetObject::LayerSetObject(){
	long width=DEFAULT_CANVAS_WIDTH;//默认画布宽，定义在include.h
	long height=DEFAULT_CANVAS_HEIGHT;//默认画布高，定义在include.h
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
		cout<<"图层 "<<cur_l->get_name()<<" 被选中"<<endl;
		return 1;
	}
}

int LayerSetObject::CreateLayer(){
	return 1;
}

int LayerSetObject::CreateLayer(char *filename){
	LayerObject ltemp;
	if (ltemp.BitMapLoad(filename)==-1)
		return -1;//图像打开失败
	
	vlso.push_back(ltemp);
	cur_l=vlso.begin()+vlso.size()-1;//指向新图层，之后的操作都是设定新图层属性
	cur_l->set_z(vlso.size());//将新打开图层至于最顶层
	//设定新图层名称
	stringstream ss;
	string newname;
	ss<<"L"<<(ltemp.id++);
	ss>>newname;
	cur_l->set_name(newname);
	//设定新图层来源文件
	string newsource(filename);
	cur_l->set_source(newsource);

	if(vlso.size()-1==0)
	{
		//如果是第一次打开图层，那么第一次打开的图层的高宽作为画布的高宽
		width=cur_l->get_width();
		height=cur_l->get_height();		
		//初始化cur_image
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
		cout<<"只剩下一层，不能删除！"<<endl;
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
			cout<<"未找到该层"<<endl;
			return 0;
		}
		else
		{
			//设定余下图层在Z轴上的顺序
			int cur_z=cur_l->get_z();
			int tmp_z;
			first=vlso.begin();
			while(first!=vlso.end())
			{
				if( (tmp_z=first->get_z()) > cur_z)
					first->set_z(tmp_z-1);
				first++;
			}
			//vlso.erase(cur_l);//函数调用后，vlso中其他元素的data和blank所指的地址保持不变，然而所指地址的内容却可能发生了改变，错误！因此改用以下方式实现：
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
	
	cur_l->set_z(vlso.size());//复制后的图层置于最顶层
	return 1;
}

int LayerSetObject::ChangeLayerZindex(int id){
	//id:1 当前层至顶；2 至底；3 上移一层；4 下移一层
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
			cout<<"已经是最顶层！"<<endl;
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
			cout<<"已经是最底层！"<<endl;
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
		cout<<"参数错误，未对当前层进行上下层移动"<<endl;
		return 0;
	}

	cout<<"上下移动图层完成"<<endl;
	this->ShowDetail();
	return 1;
}

int LayerSetObject::ChangeLayerName(string lname){
	cur_l->set_name(lname);
	return 1;
}

