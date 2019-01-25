#include "Shader.h"
#include <assert.h>

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
	//char* fragIncludesRaw;

	LoadFile(frag, fragShaderRaw[0]);

	char* fragShader[1];
	//fragShader[0] = _strdup("");

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

void Shader::HandleIncludes(char* in, char*& out)
{
	std::string in_s = std::string(in);

	// find the include line
	size_t pos = in_s.find("#include");
	while(pos != std::string::npos)
	{
		// get shader location
		size_t eol = in_s.find("\n", pos);
		size_t urlPos = in_s.find("\"", pos);
		assert(urlPos != std::string::npos);

		size_t fileNameSize = eol - (urlPos+1);

		char* fileName = (char*)malloc(fileNameSize-1);
		//strcpy_s(fileName, fileNameSize+1, in + urlPos);
		strncpy_s(fileName, fileNameSize-1, in + urlPos+1, fileNameSize-2);

		// clear the line
		in_s.erase(pos, eol - pos);

		// load the file
		char* file;
		LoadFile(fileName, file);

		// place the included file in
		in_s.insert(pos, file);

		// find next include
		pos = in_s.find("#include", pos);
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

