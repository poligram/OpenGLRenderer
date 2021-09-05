#include "ShaderUtil.h"

#include <glad/glad.h>
#include "TextFileUtil.h"

unsigned int getShaderProgram(const char* vsLocation, const char* fsLocation)
{
	unsigned int vs = loadShader(vsLocation, GL_VERTEX_SHADER);
	unsigned int fs = loadShader(fsLocation, GL_FRAGMENT_SHADER);

	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("ERROR: Shader program link failure. %s\n", infoLog);
		exit(-1);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int loadShader(const char* location, unsigned int type)
{
	std::string sourceStr = readTextFile(location);
	const char* source = sourceStr.c_str();

	//printf("%s", source);

	unsigned int shader = glCreateShader(type);
	
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const char* nameShader = "";
		if (type == GL_VERTEX_SHADER) nameShader = "VertexShader";
		else if (type == GL_FRAGMENT_SHADER) nameShader = "FragmentShader";

		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Error: %s compile fail:", nameShader);
		printf("%s\n", infoLog);
		exit(-1);
	}

	return shader;
}

