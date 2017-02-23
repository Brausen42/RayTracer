#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "Ray.hpp"
#include "Vec3.hpp"
#include "MtlColor.hpp"
#include "Light.hpp"
#include "RayPayload.hpp"

using namespace std;

class Object {
	public:
		Object();
		Object(Vec3 pos, int color_index, int texure_index, bool texture);
		void setColor(int color);
		void setPos(Vec3 pos);
		Vec3 getPos();
		Color getColor(vector<MtlColor*>);
		virtual bool findIntersection(Ray&,RayPayload&) = 0;
		virtual Vec3 getNormal(Ray&,RayPayload&) = 0;
		virtual float* getTextureUV(RayPayload&) = 0;
		virtual void addTCs(Vec3,Vec3);
		virtual void addNorms(Vec3,Vec3,Vec3);
		friend ostream& operator<<(ostream& out, Object* o);
		Vec3 m_pos;
		int m_color_index, m_texture_index;
		bool m_texture;
		
};

#endif
