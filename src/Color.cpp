#include "Color.hpp"

Color::Color() {
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

Color::Color(float red, float green, float blue){
	m_red = red;
	m_green = green;
	m_blue = blue;
}

float Color::getRed(){
	return m_red;
}

float Color::getGreen(){
	return m_green;
}

float Color::getBlue(){
	return m_blue;
}

ostream& operator<<(ostream& out, Color c){
	out << (int)c.m_red << ' ' << (int)c.m_green << ' ' << (int)c.m_blue << endl;
	return out;
}

Color operator*(Color c, float n){
	return Color(c.m_red * n, c.m_green * n, c.m_blue * n);
}

void Color::setComponents(float red, float green, float blue){
	m_red = red;
	m_green = green;
	m_blue = blue;
}
