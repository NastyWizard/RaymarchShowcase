#pragma once
#include "..\Scene.h"
#include "..\..\Objects\Object.h"
#include "..\..\Graphics\Texture.h"

class TestScene : public Scene
{
	// variables
private:
	Object* testObj;

	Texture* testTex;
	Texture* testTex2;
	float angle;

public:

	// functions
private:
public:
	TestScene();
	~TestScene();

	void Update();
	void Render();
};