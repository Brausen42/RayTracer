#ifndef MTLCOLOR_HPP
#define MTLCOLOR_HPP

#include "Color.hpp"
#include "Vec3.hpp"

using namespace std;


class MtlColor {
	public:
		MtlColor();
		MtlColor(Color d, Color s, float ka, float kd, float ks, float n, float alpha, float refraction);
		Color getDiffuseColor();
		Color getSpectralColor();
		float getPhongAmbiance(color_code);
		float getPhongAmbiance(color_code,Color);
		float getPhongIllumination(color_code, Vec3, Vec3, Vec3);
		friend ostream& operator<<(ostream& out, MtlColor color);
		Color m_d, m_s;
		float m_ka, m_kd, m_ks, m_n, m_alpha, m_refraction;
};

#endif
