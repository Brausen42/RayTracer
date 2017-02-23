#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Vec3.hpp"
#include "Color.hpp"

using namespace std;

class Light {
	public:
		Light();
		Light(Vec3 v,float type, Color color);
		Vec3 getL(Vec3);
		bool isDirectional();
		Vec3 getPos();
		friend ostream& operator<<(ostream&,Light);
	private:
		Vec3 m_v;
		Color m_color;
		float m_type;
};

#endif
