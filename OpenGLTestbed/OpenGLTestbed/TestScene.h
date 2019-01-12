#pragma once
#include "Scene.h"
#include "Object.h"
#include "Texture.h"

class TestScene : public Scene
{
	// variables
private:
	Object* testObj;

	Texture* testTex;
	Texture* testTex2;

public:

	// functions
private:
public:
	TestScene();
	~TestScene();

	void Update();
	void Render();
};