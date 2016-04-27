#include "LayerObject.h"

int LayerObject::id=0;

LayerObject::LayerObject(){
	source="null";
	name="layer";
	loc_x=0;
	loc_y=0;
	z_index=0;
	visible=1;
	transparency=100;
	mix_mode=0;
}

LayerObject::LayerObject(const LayerObject& other):BitMapObject(other){
	source=other.source;
	name=other.name;
	loc_x=other.loc_x;
	loc_y=other.loc_y;
	z_index=other.z_index;
	visible=other.visible;
	transparency=other.transparency;
	mix_mode=other.mix_mode;
}
 
LayerObject::~LayerObject(){
}

// Get Property
string LayerObject::get_name(){
	return this->name;
}

string LayerObject::get_source(){
	return this->source;
}

long LayerObject::get_x(){
	return this->loc_x;
}

long LayerObject::get_y(){
	return this->loc_y;
}

int LayerObject::get_z(){
	return this->z_index;
}

int LayerObject::get_visible(){
	return this->visible;
}

int LayerObject::get_transparency(){
	return this->transparency;
}

int LayerObject::get_mix_mode(){
	return this->mix_mode;
}


// Set Property 
int LayerObject::set_name(string& nname){
	this->name=nname;
	return 1;
}

int LayerObject::set_source(string& sname){
	this->source=sname;
	return 1;
}

int LayerObject::set_location(long new_loc_x,long new_loc_y){
	this->loc_x=new_loc_x;
	this->loc_y=new_loc_y;
	return 1;
}

int LayerObject::set_visible(bool vis){
	this->visible=vis;
	return 1;
}

int LayerObject::set_transparency(int trp){
	this->transparency=trp;
	return 1;
}

int LayerObject::set_mix_mode(int mix){
	this->mix_mode=mix;
	return 1;
}

int LayerObject::set_z(int new_z){
	this->z_index=new_z;
	return 1;
}