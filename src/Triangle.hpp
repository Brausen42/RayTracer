#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.hpp"

using namespace std;

class Triangle : public Object {
	public:
		Triangle();
		Triangle(Vec3, int, int, bool, Vec3,Vec3,Vec3);
		virtual bool findIntersection(Ray&,RayPayload&);
		virtual Vec3 getNormal(Ray&,RayPayload&);
		virtual float* getTextureUV(RayPayload&);
		void addTCs(Vec3 vt1,Vec3 vt2);
		void addNorms(Vec3 first, Vec3 second, Vec3 third);
	protected:
		Vec3 m_first,m_second,m_third,m_vt1,m_vt2,m_first_norm,m_second_norm,m_third_norm;
		bool m_norms;
};

#endif
