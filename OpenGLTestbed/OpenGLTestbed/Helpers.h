#pragma once

#include <fstream>
#include <iostream>

inline void LoadFile(char* path, char* &output)
{
	FILE *file;// = fopen("Shaders/default.vert", "rb");
	fopen_s(&file, path, "rb");
	if (file == nullptr)
	{
		std::cout << "Error: file can't be read" << std::endl;
	}

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	output = (char *)malloc(fileSize + 1);

	fread(output, fileSize, fileSize, file);
	fclose(file);

	output[fileSize] = 0;
}

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

	fread(output, fileSize, fileSize, file);
	fclose(file);

	output[fileSize] = 0;
}

template<typename T>
inline void SwapValue(T &a, T &b) 
{
	T temp = a;
	a = b;
	b = temp;
}