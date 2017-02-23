#include "Ray.hpp"

Ray::Ray() {
	
}

Ray::Ray(Vec3 pos, Vec3 dir){
	m_pos = pos;
	m_dir = dir;
}

ostream& operator<<(ostream& out, Ray r){
	out << r.m_pos << r.m_dir << endl;
	return out;
}

void Ray::normalize(){
	m_dir.normalize();
}

Vec3 Ray::getPos(){
	return m_pos;
}

Vec3 Ray::getDir(){
	return m_dir;
}

Vec3 Ray::getPos(float t){
	return m_pos + (t * m_dir);
}

