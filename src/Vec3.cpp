#include "Vec3.hpp"

Vec3::Vec3() {
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
}

Vec3::Vec3(float x, float y, float z){
	m_x = x;
	m_y = y;
	m_z = z;
}

ostream& operator<<(ostream& out, Vec3 v){
	out << v.m_x << ' ' << v.m_y << ' ' << v.m_z << endl;
	return out;
}

Vec3 operator*(float n, Vec3 v){
	float new_x, new_y, new_z;
	new_x = v.m_x * n;
	new_y = v.m_y * n;
	new_z = v.m_z * n;
	return Vec3(new_x,new_y,new_z);
}

Vec3 operator/(Vec3 v, float n){
	float new_x, new_y, new_z;
	new_x = v.m_x / n;
	new_y = v.m_y / n;
	new_z = v.m_z / n;
	return Vec3(new_x,new_y,new_z);
}

Vec3 operator+(Vec3 v1, Vec3 v2){
	float new_x, new_y, new_z;
	new_x = v1.m_x + v2.m_x;
	new_y = v1.m_y + v2.m_y;
	new_z = v1.m_z + v2.m_z;
	return Vec3(new_x,new_y,new_z);
}

Vec3 operator-(Vec3 v1, Vec3 v2){
	float new_x, new_y, new_z;
	new_x = v1.m_x - v2.m_x;
	new_y = v1.m_y - v2.m_y;
	new_z = v1.m_z - v2.m_z;
	return Vec3(new_x,new_y,new_z);
}

void Vec3::set(float x, float y, float z){
	m_x = x;
	m_y = y;
	m_z = z;
}

float Vec3::length() {
	return sqrt((pow(m_x,2) + pow(m_y,2) + pow(m_z,2)));
}

void Vec3::normalize(){
	float len = length();
	if(len == 0){
		cerr << "**Error: attempting to normalize vector of length 0" << endl;
		exit(1);
	}
	m_x = m_x / len;
	m_y = m_y / len;
	m_z = m_z / len;
}

float Vec3::getX(){
	return m_x;
}

float Vec3::getY(){
	return m_y;
}

float Vec3::getZ(){
	return m_z;
}

Vec3 cross(Vec3 v1, Vec3 v2){
	float new_x, new_y, new_z;
	
	new_x = (v1.m_y * v2.m_z) - (v1.m_z * v2.m_y);
	new_y = (v1.m_z * v2.m_x) - (v1.m_x * v2.m_z);
	new_z = (v1.m_x * v2.m_y) - (v1.m_y * v2.m_x);
	return Vec3(new_x,new_y,new_z);
}

float dot(Vec3 v1, Vec3 v2){
	return (v1.m_x * v2.m_x) + (v1.m_y * v2.m_y) + (v1.m_z * v2.m_z);
}


