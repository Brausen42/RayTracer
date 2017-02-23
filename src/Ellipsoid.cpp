#include "Ellipsoid.hpp"

Ellipsoid::Ellipsoid() : Object() {

}

Ellipsoid::Ellipsoid(Vec3 pos, int color, int texture_ind, bool texture, Vec3 radius) : Object(pos,color,texture_ind,texture) {
	m_radius = radius;
}

void Ellipsoid::setRadius(Vec3 radius){
	m_radius = radius;
}

bool Ellipsoid::findIntersection(Ray& r, RayPayload& payload){
	// TODO
	return false;
}

Vec3 Ellipsoid::getNormal(Ray& r, RayPayload& payload){
	return Vec3();
}

float* Ellipsoid::getTextureUV(RayPayload& payload){
	return (new float(0));
}


Vec3 Ellipsoid::getRadius(){
	return m_radius;
}
