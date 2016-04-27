/*���������࣬һ����ͼ���࣬һ����ͼ�㼯���ࣨ���߳���ͼ���ĵ��ࣩ

class LayerObject�����ã��̳�ͼ���࣬������ͼ�����ԡ����г�Ա������LayerObject.cpp�ж���

class LayerSetObject�����ã�ͼ�㼯���࣬���Զ�ÿһ��ͼ����й����Լ�������ͼ�㼯�Ͻ��в��������г�Ա�����������ļ��ж��壺

LayerObjectSet.cpp-----------------------------�Ծ����ĳһ����в���
	vector<LayerObject>::iterator get_cur_l();	
	long get_width();
	long get_height();
	int SelectLayer(string lname);//ѡ������Ϊlname��ͼ��
	int CreateLayer();//�½�ͼ�� *��ǰ0.1��˺���û����
	int CreateLayer(char* filename);//�½�ͼ�㣬�������ļ���Ϊfilename��ͼ��ִ�к���ͼ�㱻ѡ��
	int DeleteLayer(string lname);//ɾ������Ϊlayername��ͼ��
	int Duplicate();//���Ƶ�ǰͼ��
	int ChangeLayerZindex(int id);//���Ƶ�ǰͼ�㣬ִ�к���ͼ��λ����ϣ��ұ�ѡ��
	int ChangeLayerName(string lname);//��ѡ��ͼ�����ϻ������ƶ�

Compound.cpp-----------------------------------������ͼ�񼯺Ͻ��в���
	int Compound();//�ϳ�����ͼ��
	int SaveImage(char* filename);//����ϳ�ͼ��
	int Show();//execute "windows ͼƬ�봫��鿴��" to display cur_image
	int ShowDetail();//������ǰ�ĵ���Ϣ������������С����ǰѡ��ͼ�㣬ÿ����Ϣ
	int set_size(long width1,long height1);//�趨������С
*/
#ifndef LayerObject_H_
#define LayerObject_H_

#include "include.h"
#include "ImageObject.h"
#include "BitMapObject.h"

class LayerObject:public BitMapObject//�ٺ����汾��������ͼ���ʽ��ļ̳У��Լ�����·��ͼ��ļ̳�
{
private:
	string name;//ͼ������
	string source;//ͼ����ͼ�����Դ
	long loc_x;//��Ի���ԭ�㣨λ�����Ͻǣ�������x
	long loc_y;//��Ի���ԭ�㣨λ�����Ͻǣ�������y
	int z_index;//���ĵ��е�Z��ֵ�����²�λ�ã�
	int visible;//ͼ���Ƿ�ɼ�
	int transparency;//ͼ��͸����
	int mix_mode;//ͼ����ģʽ

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
	long width;//������
	long height;//������
	vector<LayerObject> vlso;//ͼ�㼯��
	vector<LayerObject>::iterator cur_l;//��ǰ��ѡ��ͼ��
	LayerObject cur_image;//��ǰͼ��ϳɺ��ͼ��

public:
	LayerSetObject();
	~LayerSetObject();

	int Compound();//�ϳ�����ͼ��
	int SaveImage(const char* filename);//����ϳ�ͼ��
	int Show();//execute "windows ͼƬ�봫��鿴��" to display cur_image
	int ShowDetail();//������ǰ�ĵ���Ϣ������������С����ǰѡ��ͼ�㣬ÿ����Ϣ

	//get Property
	vector<LayerObject>::iterator get_cur_l();
	long get_width() const;
	long get_height() const;
	LayerObject& get_cur_image();

	//Set Property
	int set_size(long width1,long height1);//�趨������С
	
	//operate the layers
	int SelectLayer(string lname);//ѡ������Ϊlname��ͼ��
	int CreateLayer();//�½�ͼ�� *��ǰ0.1��˺���û����
	int CreateLayer(char* filename);//�½�ͼ�㣬�������ļ���Ϊfilename��ͼ��ִ�к���ͼ�㱻ѡ��
	int DeleteLayer(string lname);//ɾ������Ϊlayername��ͼ��
	int Duplicate();//���Ƶ�ǰͼ��
	int ChangeLayerZindex(int id);//���Ƶ�ǰͼ�㣬ִ�к���ͼ��λ����ϣ��ұ�ѡ��
	int ChangeLayerName(string lname);//��ѡ��ͼ�����ϻ������ƶ�
};

#endif
