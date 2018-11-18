#include "SceneManager.h"

SceneManager * SceneManager::GetInstance()
{
	return instance == nullptr ? instance = new SceneManager() : instance;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < GetInstance()->sceneList.size(); i++)
	{
		delete GetInstance()->sceneList[i];
		GetInstance()->sceneList[i] = nullptr;
	}
}

void SceneManager::AddScene(Scene* scene) 
{
	GetInstance()->sceneList.push_back(scene);
}

void SceneManager::SetScene(int sceneNum)
{
	GetInstance()->currentScene = sceneNum;
}

void SceneManager::SetScene(std::string sceneName)
{
	for (int i = 0; i < GetInstance()->sceneList.size(); i++) 
	{
		if (GetInstance()->sceneList[GetInstance()->currentScene]->GetName() == sceneName)
		{
			GetInstance()->currentScene = i;
			break;
		}
	}
}

void SceneManager::GoToNextScene()
{
	GetInstance()->currentScene++;
}

Scene * SceneManager::GetCurrentScene()
{
	return GetInstance()->sceneList.size() > 0 ? GetInstance()->sceneList[GetInstance()->currentScene] : nullptr;
}
