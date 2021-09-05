#include "Model.h"

#include <glad/glad.h>
#include <glfw3.h>

Model::Model(const Mesh& mesh, bool useNormals)
{
	this->addData(mesh, useNormals);
}

Model::~Model()
{
	this->deleteData();
}

void Model::addData(const Mesh& mesh, bool useNormals)
{
	this->genVAO();
	
	this->addVBO(mesh.vertices);
	this->addVBO(mesh.texCoords);

	if (useNormals)
	{
		this->addVBO(mesh.normals);
	}

	this->addEBO(mesh.indices);
}

void Model::deleteData()
{
	if (this->renderInfo.vao)
	{
		glDeleteVertexArrays(1, &this->renderInfo.vao);
	}
	if (this->buffers.size() > 0)
	{
		glDeleteBuffers(static_cast<GLsizei>(this->buffers.size()),
			this->buffers.data());
	}

	this->buffers.clear();

	this->vboCount = 0;
	this->renderInfo.vao = 0;
	this->renderInfo.indicesCount = 0;
}

void Model::genVAO()
{
	if (renderInfo.vao != 0)
	{
		this->deleteData();
	}

	glGenVertexArrays(1, &this->renderInfo.vao);
	glBindVertexArray(this->renderInfo.vao);
}

void Model::addEBO(const std::vector<unsigned int>& indices)
{
	this->renderInfo.indicesCount = static_cast<unsigned int>(indices.size());

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	this->EBO = EBO;
}

void Model::addVBO(const std::vector<float>& data, int dimensions)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(static_cast<unsigned int>(this->vboCount), dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(static_cast<GLuint>(this->vboCount++));

	this->buffers.push_back(VBO);
}

void Model::addVBO(const std::vector<glm::vec2>& data)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(static_cast<unsigned int>(this->vboCount), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(static_cast<GLuint>(this->vboCount++));

	this->buffers.push_back(VBO);
}

void Model::addVBO(const std::vector<glm::vec3>& data)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(static_cast<unsigned int>(this->vboCount), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(static_cast<GLuint>(this->vboCount++));

	this->buffers.push_back(VBO);
}

void Model::bindVAO() const
{
	glBindVertexArray(this->renderInfo.vao);
}

const RenderInfo& Model::getRenderInfo() const
{
	return this->renderInfo;
}

const unsigned int& Model::getEBO() const
{
	return this->EBO;
}
