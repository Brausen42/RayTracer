#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

using namespace std;

enum color_code {
	eRed,
	eGreen,
	eBlue
};

class Color {
	public:
		Color();
		Color(float red, float green, float blue);
		void setComponents(float red, float green, float blue);
		float getRed();
		float getGreen();
		float getBlue();
		friend ostream& operator<<(ostream& out, Color c);
		friend Color operator*(Color c, float n);
		
		float m_red, m_green, m_blue;
};

#endif
