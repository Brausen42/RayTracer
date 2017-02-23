#ifndef RAYPAYLOAD_HPP
#define RAYPAYLOAD_HPP

#include "Vec3.hpp"
#include <vector>

using namespace std;

class RayPayload {
	public:
		RayPayload();
		int m_object_id;
		float m_dist;
		int m_color_index;
		int m_texture_index;
		bool m_texture;
		Vec3 m_barycentric;
		Vec3 m_intersect;
		int m_intersects_count;
		vector<int> m_intersect_colors;
};

#endif
