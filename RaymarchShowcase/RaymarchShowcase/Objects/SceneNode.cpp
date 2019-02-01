#include "SceneNode.h"

SceneNode::SceneNode(std::string Name)
{
	name = Name;
}

SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if(children[i] != nullptr)
			delete children[i];
	}
}

void SceneNode::AddChild(SceneNode* c)
{
	children.push_back(c);
}

// finds first child by name
SceneNode * SceneNode::FindChild(std::string Name)
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->name == Name)
			return children[i];
	}
	return nullptr;
}

// finds first child by tag
SceneNode * SceneNode::FindChild(Tags tag)
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->HasTag(tag))
			return children[i];
	}
	return nullptr;
}

void SceneNode::Init()
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->Init();
	}
}

void SceneNode::Update()
{
	for (unsigned int i = 0; i < children.size(); i++) 
	{
		children[i]->Update();
	}
}

void SceneNode::Render()
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->Render();
	}
}

void SceneNode::AddTag(Tags tag)
{
	tags |= tag;
}

void SceneNode::RemoveTag(Tags tag)
{
	tags &= ~tag;
}

bool SceneNode::HasTag(Tags tag)
{
	return (tags & tag) == tag;
}
