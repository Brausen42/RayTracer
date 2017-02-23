#include "Object.hpp"

Object::Object() {
	m_color_index = 0;
	m_texture_index = 0;
	m_texture = false;
}

Object::Object(Vec3 pos, int color_index, int texture_index, bool texture){
	m_pos = pos;
	m_color_index = color_index;
	m_texture_index = texture_index;
	m_texture = texture;
}

ostream& operator<<(ostream& out, Object* o){
	out << o->m_pos << endl;
	return out;
}

void Object::setPos(Vec3 pos){
	m_pos = pos;
}

void Object::setColor(int color){
	m_color_index = color;
}

Vec3 Object::getPos(){
	return m_pos;
}

Color Object::getColor(vector<MtlColor*> colors){
	return colors[m_color_index]->getDiffuseColor();
}

void Object::addTCs(Vec3 a ,Vec3 b){}
void Object::addNorms(Vec3 a,Vec3 b,Vec3 c){}
