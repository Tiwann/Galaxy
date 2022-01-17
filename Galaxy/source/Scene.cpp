#include "Scene.h"
#include "Log.h"

namespace Galaxy
{

	Scene::Scene()
	{
		LOG_TRACE("[SCENE] Creating scene");
	}

	Scene Scene::Get()
	{
		static Scene instance = Scene();
		return instance;
	}

	void Scene::Init()
	{
	}

	void Scene::Update()
	{
	}

	void Scene::RegisterSceneObject(const SceneObject* object)
	{
	}
}