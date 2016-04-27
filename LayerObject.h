/*包含两个类，一个是图层类，一个是图层集合类（或者称作图层文档类）

class LayerObject的作用：继承图像类，并加入图层属性。所有成员函数在LayerObject.cpp中定义

class LayerSetObject的作用：图层集合类，可以对每一层图层进行管理以及对整个图层集合进行操作。所有成员函数在如下文件中定义：

LayerObjectSet.cpp-----------------------------对具体的某一层进行操作
	vector<LayerObject>::iterator get_cur_l();	
	long get_width();
	long get_height();
	int SelectLayer(string lname);//选中名称为lname的图层
	int CreateLayer();//新建图层 *当前0.1版此函数没有用
	int CreateLayer(char* filename);//新建图层，并载入文件名为filename的图像，执行后，新图层被选中
	int DeleteLayer(string lname);//删除名称为layername的图层
	int Duplicate();//复制当前图层
	int ChangeLayerZindex(int id);//复制当前图层，执行后，新图层位于最顶上，且被选中
	int ChangeLayerName(string lname);//将选中图层向上或向下移动

Compound.cpp-----------------------------------对整个图像集合进行操作
	int Compound();//合成所有图像
	int SaveImage(char* filename);//保存合成图像
	int Show();//execute "windows 图片与传真查看器" to display cur_image
	int ShowDetail();//给出当前文档信息，包括画布大小，当前选中图层，每层信息
	int set_size(long width1,long height1);//设定画布大小
*/
#ifndef LayerObject_H_
#define LayerObject_H_

#include "include.h"
#include "ImageObject.h"
#include "BitMapObject.h"

class LayerObject:public BitMapObject//再后续版本加入其他图像格式类的继承，以及工作路径图层的继承
{
private:
	string name;//图层名称
	string source;//图层中图像的来源
	long loc_x;//相对画布原点（位于左上角）的坐标x
	long loc_y;//相对画布原点（位于左上角）的坐标y
	int z_index;//在文档中的Z轴值（上下层位置）
	int visible;//图层是否可见
	int transparency;//图层透明度
	int mix_mode;//图层混合模式

public:
	static int id;

	LayerObject();
	LayerObject(const LayerObject& other); 
	~LayerObject();
	
	// Get Property
	long get_x();
	long get_y();
	int get_z();
	int get_visible();
	int get_transparency();
	int get_mix_mode();
	string get_name();
	string get_source();

	// Set Property 
	int set_location(long new_loc_x,long new_loc_y);
	int set_z(int new_z);
	int set_visible(bool vis);
	int set_transparency(int trp);
	int set_mix_mode(int mix);
	int set_name(string& nname);
	int set_source(string& sname);
};

class LayerSetObject
{
private:
	long width;//画布宽
	long height;//画布高
	vector<LayerObject> vlso;//图层集合
	vector<LayerObject>::iterator cur_l;//当前被选中图层
	LayerObject cur_image;//当前图层合成后的图像

public:
	LayerSetObject();
	~LayerSetObject();

	int Compound();//合成所有图像
	int SaveImage(const char* filename);//保存合成图像
	int Show();//execute "windows 图片与传真查看器" to display cur_image
	int ShowDetail();//给出当前文档信息，包括画布大小，当前选中图层，每层信息

	//get Property
	vector<LayerObject>::iterator get_cur_l();
	long get_width() const;
	long get_height() const;
	LayerObject& get_cur_image();

	//Set Property
	int set_size(long width1,long height1);//设定画布大小
	
	//operate the layers
	int SelectLayer(string lname);//选中名称为lname的图层
	int CreateLayer();//新建图层 *当前0.1版此函数没有用
	int CreateLayer(char* filename);//新建图层，并载入文件名为filename的图像，执行后，新图层被选中
	int DeleteLayer(string lname);//删除名称为layername的图层
	int Duplicate();//复制当前图层
	int ChangeLayerZindex(int id);//复制当前图层，执行后，新图层位于最顶上，且被选中
	int ChangeLayerName(string lname);//将选中图层向上或向下移动
};

#endif
