#pragma once
#include "NodeTags.h"
#include <vector>


class SceneNode 
{
	//variables
private:
	std::vector<SceneNode*> children;

	std::string name;

	int tags;

	static int ID;

public:

	//functions
private:
public:
	SceneNode(std::string Name);
	~SceneNode();

	void AddChild(SceneNode* c);
	SceneNode* FindChild(std::string Name);
	SceneNode* FindChild(Tags tag);

	virtual void Update();
	virtual void Render();

	void AddTag(Tags tag);
	void RemoveTag(Tags tag);
	bool HasTag(Tags tag);
};