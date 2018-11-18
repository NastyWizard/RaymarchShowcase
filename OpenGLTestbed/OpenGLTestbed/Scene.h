#pragma once
#include "SceneNode.h"

class Scene : public SceneNode
{
private:

public:
	Scene(std::string Name);
	~Scene();

	void Update();
	void Render();
};