#include "Sphere.hpp"

Sphere::Sphere() : Object() {
	m_radius = 0;
}

Sphere::Sphere(Vec3 pos, int color_index, int texture_index, bool texture, float radius) : Object(pos,color_index,texture_index,texture) {
	m_radius = radius;
}

void Sphere::setRadius(float radius){
	m_radius = radius;
}

bool Sphere::findIntersection(Ray& r, RayPayload& payload){
	float B = 2.0 * dot(r.getDir() , (r.getPos() - getPos()));
	float C = dot(r.getPos() - getPos() , r.getPos() - getPos()) - pow(getRadius(),2);
	float determ = (pow(B,2.0) - 4.0 * C);
	if( determ < 0){
		return false;
	}
	float option_one = (((-1) * B) - sqrt(determ)) / 2.0;
	float option_two = (((-1) * B) + sqrt(determ)) / 2.0;
	float dist = -1;
	// check if the object was in the ray's positive trajectory
	if (option_one >= 0 && (option_one < option_two || option_two < 0)) {
		dist = option_one;
	}
	else if (option_two >= 0) {
		dist = option_two;
	}
	if(dist >= 0){
		payload.m_intersect_colors.push_back(m_color_index);
		if(payload.m_dist < 0 || dist < payload.m_dist){
			payload.m_dist = dist;
			payload.m_color_index = m_color_index;
			payload.m_texture_index = m_texture_index;
			payload.m_texture = m_texture;
			payload.m_intersect = r.getPos(dist);
			return true;
		}
	}
	return false;
}


float Sphere::getRadius(){
	return m_radius;
}

Vec3 Sphere::getNormal(Ray& r, RayPayload& payload){
	return (r.getPos(payload.m_dist) - m_pos) / m_radius;
}

float* Sphere::getTextureUV(RayPayload& payload){
	float* temp = new float[2];
	Vec3 N = (payload.m_intersect - m_pos)/ m_radius;
	float phi = acos(N.getZ());
	float theta = atan2(N.getY(),N.getX());
	temp[1] = phi/M_PI;
	if(theta < 0){
		theta = theta + (2.0 * M_PI);
	}
	temp[0] = theta / (2.0 * M_PI);
	return temp;
}
