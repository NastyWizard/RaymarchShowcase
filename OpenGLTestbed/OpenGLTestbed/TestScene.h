#pragma once
#include "Scene.h"
#include "Object.h"

class TestScene : public Scene
{
	// variables
private:
	Object* testObj;
public:
	TestScene();
	~TestScene();
	// functions
private:
public:
	void Update();
	void Render();
};