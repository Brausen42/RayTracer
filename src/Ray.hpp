#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include "Vec3.hpp"

using namespace std;

class Ray {
	public:
		Ray();
		Ray(Vec3 pos, Vec3 dir);
		Vec3 getPos();
		Vec3 getPos(float t);
		Vec3 getDir();
		void normalize();
		friend ostream& operator<<(ostream&,Ray);
	private:
		Vec3 m_pos, m_dir;
};

#endif
