#ifndef ELLIPSOID_HPP
#define ELLIPSOID_HPP

#include "Object.hpp"

using namespace std;

class Ellipsoid : public Object {
	public:
		Ellipsoid();
		Ellipsoid(Vec3 pos, int color_index, int texture_index, bool texture, Vec3 radius);
		virtual bool findIntersection(Ray&,RayPayload&);
		virtual Vec3 getNormal(Ray&,RayPayload&);
		virtual float* getTextureUV(RayPayload&);
		void setRadius(Vec3 radius);
		Vec3 getRadius();
	protected:
		Vec3 m_radius;
};

#endif
