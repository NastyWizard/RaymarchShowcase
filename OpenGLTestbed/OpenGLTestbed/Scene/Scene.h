#pragma once
#include "..\Objects\SceneNode.h"

class Scene : public SceneNode
{
private:

public:
	Scene(std::string Name);
	~Scene();

	void Init();
	void Update();
	void Render();
};