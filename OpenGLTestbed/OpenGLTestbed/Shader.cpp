#include "Shader.h"

void Shader::Initialize(std::string vert, std::string frag)
{

	// create shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// VERTEX

	// load the shader code

	char* vertShaderRaw[1];
	do
	{
		LoadFile(vert, vertShaderRaw[0]);
	} while (*vertShaderRaw[0] == 'Í');

	glShaderSource(vertexShader, 1, vertShaderRaw, nullptr);
	glCompileShader(vertexShader);

	checkCompileErrors(vertexShader, "VERTEX");

	// FRAGMENT

	// load the shader code

	char* fragShaderRaw[1];

	LoadFile(frag, fragShaderRaw[0]);

	glShaderSource(fragmentShader, 1, fragShaderRaw, nullptr);
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

