#include "TestScene.h"

TestScene::TestScene() : Scene("TestScene")
{
	
	AddChild(testObj);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	Scene::Update();
}

void TestScene::Render()
{
	Scene::Render();
}
