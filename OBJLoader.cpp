#include "OBJLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h" 

OBJLoader::OBJLoader()
{	
}

Model* OBJLoader::loadModel(const char* modelName, Loader* loader) {
	char path[50];
	sprintf_s(path, 50, "res\\%s.obj", modelName);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path)) 
	{
		throw std::runtime_error(err);
	}

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

	for (const auto& shape : shapes) 
	{
		for (const auto& index : shape.mesh.indices) 
		{
			Vertex vertex = {};

			vertex.position = 
			{
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};
			vertex.uv = 
			{
				attrib.texcoords[2 * index.texcoord_index + 0],
				1 - attrib.texcoords[2 * index.texcoord_index + 1]
			};
			vertex.normal = 
			{
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};

			if (uniqueVertices.count(vertex) == 0)
			{

				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}
			indices.push_back(uniqueVertices[vertex]);
		}
	}

	std::vector<float> verticesVector;
	std::vector<float> normalsVector;
	std::vector<float> UVsVector;
	float maxY = 0;
	//TEMP
	float minY = 0;
	float minX = 0;
	float maxX = 0;
	float minZ = 0;
	float maxZ = 0;

	for (Vertex vertex : vertices) 
	{
		if (vertex.position.y > maxY) {
			maxY = vertex.position.y;
		}
		//TEMP
		if (vertex.position.y < minY) {
			minY = vertex.position.y;
		}
		if (vertex.position.x > maxX) {
			maxX = vertex.position.x;
		}
		if (vertex.position.x < minX) {
			minX = vertex.position.x;
		}
		if (vertex.position.z > maxZ) {
			maxZ = vertex.position.z;
		}
		if (vertex.position.z < minZ) {
			minZ = vertex.position.z;
		}

		verticesVector.push_back(vertex.position.x);
		verticesVector.push_back(vertex.position.y);
		verticesVector.push_back(vertex.position.z);

		normalsVector.push_back(vertex.normal.x);
		normalsVector.push_back(vertex.normal.y);
		normalsVector.push_back(vertex.normal.z);

		UVsVector.push_back(vertex.uv.x);
		UVsVector.push_back(vertex.uv.y);
	}
	Model* model = loader->load(verticesVector, UVsVector, normalsVector, indices);
	model->setHeight(maxY);
	model->setBounds(glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ));
	return model;
}