#pragma once
#include <vector>

class MeshPrimitives 
{

public:
	static void Create2DRect(float width, float height, std::vector<float> &vertArray, std::vector<unsigned int> &indexArray);

};