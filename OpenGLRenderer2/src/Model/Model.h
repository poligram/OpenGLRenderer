#pragma once
#include "Mesh.h"
#include "RenderInfo.h"

class Model
{
public:
	Model(const Mesh& mesh, bool useNormals);
	~Model();

	void addData(const Mesh& mesh, bool useNormals);
	void deleteData();

	void genVAO();
	void addEBO(const std::vector<unsigned int>& indices);

	void addVBO(const std::vector<float>& data, int dimensions);
	void addVBO(const std::vector<glm::vec2>& data);
	void addVBO(const std::vector<glm::vec3>& data);

	void bindVAO() const;

	const RenderInfo& getRenderInfo() const;
	const unsigned int& getEBO() const;

private:
	RenderInfo renderInfo;
	unsigned int EBO;
	int vboCount;
	std::vector<unsigned int> buffers;
};

