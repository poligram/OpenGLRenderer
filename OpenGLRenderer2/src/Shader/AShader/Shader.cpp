#include "Shader.h"
#include "../../Utilities/ShaderUtil.h"
#include "glad/glad.h"
#include <stdio.h>
#include <gtc/type_ptr.hpp>

Shader::Shader(const char* vertexLocation, const char* fragmentLocation)
{
	this->programID = getShaderProgram(vertexLocation, fragmentLocation);
}

Shader::~Shader()
{
	glDeleteProgram(this->programID);
}

void Shader::useProgram()
{
	glUseProgram(this->programID);
}

unsigned int& Shader::getProgramID()
{
	return this->programID;
}

void Shader::setUniformInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(this->programID, name), value);
}

void Shader::setUniformFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(this->programID, name), value);
}

void Shader::setUniformBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->programID, name), (int)value);
}

void Shader::setUniformMat4(const char* name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, GL_FALSE, glm::value_ptr(value));
}
