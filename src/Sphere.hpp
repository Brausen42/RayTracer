#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

using namespace std;

class Sphere : public Object {
	public:
		Sphere();
		Sphere(Vec3, int , int ,bool, float);
		void setRadius(float radius);
		float getRadius();
		virtual bool findIntersection(Ray&,RayPayload&);
		virtual Vec3 getNormal(Ray&,RayPayload&);
		virtual float* getTextureUV(RayPayload&);
	protected:
		float m_radius;
};

#endif
