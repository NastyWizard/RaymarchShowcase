#include "Shader.h"
#include <assert.h>

void Shader::Initialize(std::string vert, std::string frag)
{

	this->vert = vert;
	this->frag = frag;

	// create shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// VERTEX

	// shader
	char* vertShaderRaw[1];
	LoadFile(vert, vertShaderRaw[0]);

	// includes
	char* vertShader[1];
	HandleIncludes(vertShaderRaw[0], vertShader[0]);

	glShaderSource(vertexShader, 1, vertShader, nullptr);
	glCompileShader(vertexShader);

	checkCompileErrors(vertexShader, "VERTEX");

	// FRAGMENT

	// shader
	char* fragShaderRaw[1];
	LoadFile(frag, fragShaderRaw[0]);

	// includes
	char* fragShader[1];
	HandleIncludes(fragShaderRaw[0], fragShader[0]);


	glShaderSource(fragmentShader, 1, fragShader, nullptr);
	glCompileShader(fragmentShader);

	checkCompileErrors(fragmentShader, "FRAGMENT");

	// link the shader to the program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkCompileErrors(shaderProgram, "PROGRAM");

	// clear shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// takes in raw shader data, outputs shader data with included shader data.
void Shader::HandleIncludes(char* in, char*& out)
{
	std::string in_s = std::string(in);

	// find the include line
	size_t pos = in_s.find("#include");
	while(pos != std::string::npos)
	{
		// get shader location
		size_t urlPos = in_s.find("\"", pos) + sizeof(BYTE);
		assert(urlPos != std::string::npos);

		size_t eol = in_s.find("\"", urlPos + 1) + 1;

		size_t fileNameSize = eol - urlPos;

		char* fileName = (char*)malloc(fileNameSize);
		strncpy_s(fileName, fileNameSize, in_s.c_str() + urlPos, fileNameSize - (sizeof(BYTE)));

		// clear the line
		in_s.erase(pos, eol - pos);

		// load the file
		char* file;
		LoadFile(fileName, file);

		// place the included file in
		in_s.insert(pos, file);

		// find next include
		pos = in_s.find("#include", pos);
		delete file;
	}

	// copy data into output string
	out = (char*)malloc(in_s.length()+1);
	strcpy_s(out, in_s.length()+1, in_s.c_str());

}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type.c_str() << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type.c_str() << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}


void Shader::UseShader()
{
	glUseProgram(shaderProgram);
}

std::string Shader::GetVertex()
{
	return vert;
}

std::string Shader::GetFragment()
{
	return frag;
}

