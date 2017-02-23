#include "Light.hpp"

Light::Light() {
	m_v = Vec3();
	m_type = 0;
	m_color = Color();
}

Light::Light(Vec3 v,float type, Color color){
	m_v = v;
	m_type = type;
	m_color = color;
}

bool Light::isDirectional(){
	return m_type == 0;
}

Vec3 Light::getPos(){
	return m_v;
}

Vec3 Light::getL(Vec3 intersect){
	if(m_type == 0){
		Vec3 L = -1 * m_v;
		L.normalize();
		return L;
	}
	else if(m_type == 1){
		Vec3 L =  m_v - intersect;
		L.normalize();
		return L;
	}
	cerr << "**Error: No such light type " << m_type << endl;
	return Vec3();
}

ostream& operator<<(ostream& out, Light l){
	out << l.m_v << l.m_type << endl << l.m_color << endl;
	return out;
}
