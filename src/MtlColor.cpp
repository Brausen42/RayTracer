#include "MtlColor.hpp"

MtlColor::MtlColor() {
	m_d = Color();
	m_s = Color();
	m_ka = 0;
	m_kd = 0;
	m_ks = 0;
	m_n = 0;
	m_alpha = 1;
	m_refraction = 1;
}

MtlColor::MtlColor(Color d, Color s, float ka, float kd, float ks, float n, float alpha, float refraction){
	m_d = d;
	m_s = s;
	m_ka = ka;
	m_kd = kd;
	m_ks = ks;
	m_n = n;
	m_alpha = alpha;
	m_refraction = refraction;
}

Color MtlColor::getDiffuseColor(){
	return m_d;
}

Color MtlColor::getSpectralColor(){
	return m_s;
}

float MtlColor::getPhongAmbiance(color_code color){
	// easily allow intensity to be adjusted
	float intensity = 1.0;
	switch(color){
		case eRed:
			return intensity * (m_ka * m_d.getRed());
			break;
		case eGreen:
			return intensity * (m_ka * m_d.getGreen());
			break;
		case eBlue:
			return intensity * (m_ka * m_d.getBlue());
			break;
		default:
			// error
			break;
	}
	return -1;
}

float MtlColor::getPhongAmbiance(color_code color, Color alternative){
	// easily allow intensity to be adjusted
	float intensity = 1.0;
	switch(color){
		case eRed:
			return intensity * (m_ka * alternative.getRed());
			break;
		case eGreen:
			return intensity * (m_ka * alternative.getGreen());
			break;
		case eBlue:
			return intensity * (m_ka * alternative.getBlue());
			break;
		default:
			// error
			break;
	}
	return -1;
}

float MtlColor::getPhongIllumination(color_code color,Vec3 N, Vec3 L, Vec3 H){
	// precalculate NL and NH to make things cleaner
	float NL = max((float)0,dot(N,L));
	float NH = max((float)0,dot(N,H));
	// easily allow intensity to be adjusted
	float intensity = 1.0;
	switch(color){
		case eRed:
			return (intensity * ((m_kd * m_d.getRed() * NL) + (m_ks * m_s.getRed() * (pow(NH,m_n)))));
			break;
		case eGreen:
			return (intensity * ((m_kd * m_d.getGreen() * NL) + (m_ks * m_s.getGreen() * (pow(NH,m_n)))));
			break;
		case eBlue:
			return (intensity * ((m_kd * m_d.getBlue() * NL) + (m_ks * m_s.getBlue() * (pow(NH,m_n)))));
			break;
		default:
			// error
			break;
	}
	return -1;
}

ostream& operator<<(ostream& out, MtlColor color){
	out << color.m_d << color.m_s << color.m_ka << endl << color.m_kd << endl << color.m_ks << endl << color.m_n << endl;
	return out;
}
