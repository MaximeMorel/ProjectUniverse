////////////////////////////////////////////////////////////////////////////////
#include "scene.hpp"
////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
{
}
////////////////////////////////////////////////////////////////////////////////
Scene::~Scene()
{
}
////////////////////////////////////////////////////////////////////////////////
void Scene::add(Mesh* mesh)
{
    m_meshes.push_back(mesh);
}
////////////////////////////////////////////////////////////////////////////////
