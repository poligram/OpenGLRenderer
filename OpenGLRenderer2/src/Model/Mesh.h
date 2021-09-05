#pragma once
#include <vector>
#include <vec3.hpp>
#include <vec2.hpp>

struct Mesh
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
};