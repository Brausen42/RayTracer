#include "Scene.hpp"

Scene::Scene() {}

void Scene::setBkgColor(Color color){
	m_bkgcolor = color;
}
void Scene::addMtlColor(MtlColor* mtlcolor){
	m_colors.push_back(mtlcolor);
}
void Scene::addObject(Object* object){
	m_objects.push_back(object);
}
void Scene::addLight(Light* light){
	m_lights.push_back(light);
}
void Scene::addVertex(Vec3 vertex){
	m_vertices.push_back(vertex);
}
void Scene::addVertexNormal(Vec3 vertex_norm){
	m_vertex_normals.push_back(vertex_norm);
}
void Scene::addTexture(Color** texture){
	m_textures.push_back(texture);
}
void Scene::addTextureCoordinate(float* text_coords){
	m_texture_coordinates.push_back(text_coords);
}
void Scene::addTextureSize(float* text_size){
	m_texture_sizes.push_back(text_size);
}
