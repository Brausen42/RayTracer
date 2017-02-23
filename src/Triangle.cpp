#include "Triangle.hpp"

Triangle::Triangle() : Object() {
	m_norms = false;
}

Triangle::Triangle(Vec3 pos, int color_index, int texture_index, bool texture, Vec3 first, Vec3 second, Vec3 third) : Object(pos,color_index,texture_index,texture) {
	m_first = first;
	m_second = second;
	m_third = third;
	m_norms = false;
}

void Triangle::addNorms(Vec3 first,Vec3 second,Vec3 third){
	m_first_norm = first;
	m_second_norm = second;
	m_third_norm = third;
	m_norms = true;
}

void Triangle::addTCs(Vec3 vt1,Vec3 vt2){
	m_vt1 = vt1;
	m_vt2 = vt2;
}

bool Triangle::findIntersection(Ray& r, RayPayload& payload){
	Vec3 e1 = m_second - m_first;
	Vec3 e2 = m_third - m_first;
	Vec3 n = cross(e1,e2);
	float denom = dot(n,r.getDir());
	if(denom == 0.0){
		return false;
	}
	float D = -1 * dot(n,m_first);
	float t = -1 * ((dot(n,r.getPos()) + D) / denom);
	Vec3 planeIntersect;
	if(t >= 0){
		planeIntersect =  r.getPos() + (t * r.getDir());
	}
	else {
		return false;
	}
	// found a plane intersection, now check if it's in the triangle
	Vec3 e3 = planeIntersect - m_second;
	Vec3 e4 = planeIntersect - m_third;
	float A = 0.5 * (cross(e1,e2)).length();
	float a = 0.5 * (cross(e3,e4)).length();
	float b = 0.5 * (cross(e4,e2)).length();
	float c = 0.5 * (cross(e1,e3)).length();
	float alpha = a/A;
	float beta = b/A;
	float gamma = c/A;
	if(alpha + beta + gamma - 1 < 0.000001){
		payload.m_intersect_colors.push_back(m_color_index);
		if(payload.m_dist < 0 || t < payload.m_dist){
			payload.m_dist = t;
			payload.m_color_index = m_color_index;
			payload.m_texture_index = m_texture_index;
			payload.m_texture = m_texture;
			payload.m_intersect = r.getPos(t);
			payload.m_barycentric = Vec3(alpha,beta,gamma);
			return true;
		}
	}
	return false;
}


Vec3 Triangle::getNormal(Ray& r, RayPayload& payload){
	Vec3 n;
	if(m_norms){
		Vec3 first = payload.m_barycentric.getX() * m_first_norm;
		Vec3 second = payload.m_barycentric.getY() * m_second_norm;
		Vec3 third = payload.m_barycentric.getZ() * m_third_norm;
		n = first + second + third;
	}
	else {
		n = cross((m_second - m_first),(m_third - m_first));
	}
	n.normalize();
	return n;
}

float* Triangle::getTextureUV(RayPayload& payload){
	float* temp = new float[2];
	temp[0] = dot(payload.m_barycentric,m_vt1);
	temp[1] = dot(payload.m_barycentric,m_vt2);
	return temp;
}
