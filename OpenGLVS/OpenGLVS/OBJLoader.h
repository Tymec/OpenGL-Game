#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/hash.hpp>
#include "Loader.h"

class OBJLoader
{
public:
	OBJLoader();
	Model* loadModel(const char* modelName, Loader* loader);
};

struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	bool operator==(const Vertex& other) const
	{
		return position == other.position && uv == other.uv && normal == other.normal;
	}
};

namespace std
{
	template<> struct hash<Vertex>
	{
		size_t operator()(Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.position) ^
					(hash<glm::vec2>()(vertex.uv) << 1)) >> 1) ^
					(hash<glm::vec3>()(vertex.normal) << 1);
		}
	};
}