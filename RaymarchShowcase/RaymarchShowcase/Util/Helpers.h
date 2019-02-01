#pragma once

#include <fstream>
#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <map>

#define PI 3.14159265359f

inline float RadToDeg(float angle)
{
	return angle * (180.0f / PI);
}

inline float DegToRad(float angle)
{
	return angle * (PI / 180.0f);
}

inline void CheckForGLErrors()
{
	GLenum error = glGetError();

	if (error != 0)
	{
		std::cout << "glGetError\n";
	}
}

template <typename K, typename V>
inline std::vector<std::pair<K,V>> MapToVec(const  std::map<K,V> &map) 
{	
	return std::vector<std::pair<K, V>>(map.begin(), map.end());
}

//inline void LoadFile(char* path, char* &output)
//{
//	FILE *file;// = fopen("Shaders/default.vert", "rb");
//	fopen_s(&file, path, "rb");
//	if (file == nullptr)
//	{
//		std::cout << "Error: file can't be read" << std::endl;
//	}
//
//	fseek(file, 0, SEEK_END);
//	int fileSize = ftell(file);
//	rewind(file);
//
//	output = (char *)malloc(fileSize + 1);
//
//	fread(output, fileSize, fileSize, file);
//	fclose(file);
//
//	output[fileSize] = 0;
//}

inline void LoadFile(std::string path, char* &output)
{
	FILE *file;// = fopen("Shaders/default.vert", "rb");
	const char *str = path.c_str();
	fopen_s(&file, str, "rb");
	if (file == nullptr)
	{
		std::cout << "Error: file can't be read" << std::endl;
	}

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	output = (char *)malloc(fileSize + 1);

	fread(output, fileSize, 1, file);
	fclose(file);

	output[fileSize] = 0;

	// sometimes doesn't load, added recursive "fix". TODO: Do real fix
	if (output[0] == 'Í')
	{
		//delete output;
		LoadFile(path, output);	
	}
}

inline void LoadFile(std::string path, unsigned char* &output, long &size)
{
	char* filecontents = 0;

	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, path.c_str(), "rb");

	if (filehandle)
	{
		fseek(filehandle, 0, SEEK_END);
		long length = ftell(filehandle);
		rewind(filehandle);

		filecontents = new char[length + 1];
		fread(filecontents, length, 1, filehandle);
		filecontents[length] = 0;

		if (size)
			size = length;

		fclose(filehandle);
	}

	output = (unsigned char*)filecontents;
}

//inline void LoadFile(std::string path, unsigned char* &output)
//{
//	long i;
//	LoadFile(path, output, i);
//}


template<typename T>
inline void SwapValue(T &a, T &b) 
{
	T temp = a;
	a = b;
	b = temp;
}