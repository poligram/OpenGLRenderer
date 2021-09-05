#pragma once
#include <mat4x4.hpp>
class Shader
{
public:
	Shader(const char* vertexLocation, const char* fragmentLocation);
	~Shader();

	void useProgram();

	unsigned int& getProgramID();

	//Uniforms
	void setUniformInt(const char* name, int value) const;
	void setUniformFloat(const char* name, float value) const;
	void setUniformBool(const char* name, bool value) const;
	void setUniformMat4(const char* name, glm::mat4 value) const;
private:
	unsigned int programID;
};

