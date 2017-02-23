#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Vec3 {
	public:
		Vec3();
		Vec3(float x, float y, float z);
		void normalize();
		float length();
		void set(float x, float y, float z);
		float getX();
		float getY();
		float getZ();
		friend ostream& operator<<(ostream&,Vec3);
		friend Vec3 operator+(Vec3 v1, Vec3 v2);
		friend Vec3 operator-(Vec3 v1, Vec3 v2);
		friend Vec3 operator*(float n, Vec3 v);
		friend Vec3 operator/(Vec3 v, float n);
		friend Vec3 cross(Vec3 v1, Vec3 v2);
		friend float dot(Vec3 v1, Vec3 v2);
	private:
		float m_x, m_y, m_z;
};

#endif
