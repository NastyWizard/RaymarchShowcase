#pragma once
#include "Scene.h"
#include <vector>

class SceneManager
{
	// variables
private:
	static SceneManager* instance;
	std::vector<Scene*> sceneList;
	int currentScene = 0;
public:

	// functions
private:
public:

	static SceneManager* GetInstance();

	SceneManager();
	~SceneManager();

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	static void AddScene(Scene* scene);
	static void SetScene(int sceneNum);
	static void SetScene(std::string sceneName);
	static void GoToNextScene();
	static Scene* GetCurrentScene();
};