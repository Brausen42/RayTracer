#ifndef SCENE_HPP
#define SCENE_HPP

#include "Object.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include "Color.hpp"
#include "MtlColor.hpp"
#include "Light.hpp"
#include <vector>

using namespace std;

class Scene {
	public:
		Scene();
		void setBkgColor(Color);
		void addMtlColor(MtlColor*);
		void addObject(Object*);
		void addLight(Light*);
		void addVertex(Vec3);
		void addVertexNormal(Vec3);
		void addTexture(Color**);
		void addTextureCoordinate(float*);
		void addTextureSize(float*);
		Color m_bkgcolor;
		vector<MtlColor*> m_colors;
		vector<Object*> m_objects;
		vector<Light*> m_lights;
		vector<Vec3> m_vertices;
		vector<Vec3> m_vertex_normals;
		vector<Color**> m_textures;
		vector<float*> m_texture_coordinates;
		vector<float*> m_texture_sizes;
		Vec3 m_eye;
};

#endif
