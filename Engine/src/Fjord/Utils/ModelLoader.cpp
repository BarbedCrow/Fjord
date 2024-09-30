#include "fjordpch.h"

#include "ModelLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace Fjord
{
	// Helper function to get the number of faces using a specific vertex
	static size_t GetNumberOfFacesUsingVertex(size_t vertexIndex, const std::vector<uint32_t>& indices)
	{
		size_t count = 0;
		for (size_t i = 0; i < indices.size(); ++i) {
			if (indices[i] == vertexIndex) {
				++count;
			}
		}
		return count;
	}

	bool ModelLoader::LoadObj(const char* path, std::vector<glm::vec3>& oVertices, std::vector<uint32_t>& oIndices, std::vector<glm::vec2>& oUvs, std::vector<glm::vec3>& oNormals)
	{
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "Error opening OBJ file: " << path << std::endl;
			return false;
		}

		std::vector<glm::vec3> tempVertices;
		std::vector<glm::vec2> tempUvs;
		std::vector<glm::vec3> tempNormals;

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string type;
			iss >> type;

			if (type == "v") {
				glm::vec3 vertex;
				iss >> vertex.x >> vertex.y >> vertex.z;
				tempVertices.push_back(vertex);
			}
			else if (type == "vt") {
				glm::vec2 uv;
				iss >> uv.x >> uv.y;
				// uv.y = 1.f - uv.y;
				tempUvs.push_back(uv);
			}
			else if (type == "vn") {
				glm::vec3 normal;
				iss >> normal.x >> normal.y >> normal.z;
				tempNormals.push_back(normal);
			}
			else if (type == "f") {
				std::vector<int> vertexIndices, uvIndices, normalIndices;
				int index;
				while (iss >> index) {
					vertexIndices.push_back(index - 1);
					iss.ignore(1); // Skip '/'
					iss >> index;
					uvIndices.push_back(index - 1);
					iss.ignore(1); // Skip '/'
					iss >> index;
					normalIndices.push_back(index - 1);
				}

				for (size_t i = 0; i < vertexIndices.size(); ++i) {
					oIndices.push_back(oVertices.size());
					oVertices.push_back(tempVertices[vertexIndices[i]]);
					oUvs.push_back(tempUvs[uvIndices[i]]);
					oNormals.push_back(tempNormals[normalIndices[i]]);
				}
			}
		}

		file.close();

		// Calculate interpolated normals
		for (size_t i = 0; i < oVertices.size(); ++i) {
			glm::vec3 interpolatedNormal(0.0f);
			for (size_t j = 0; j < oIndices.size(); ++j) {
				if (oIndices[j] == i) {
					interpolatedNormal += oNormals[j];
				}
			}
			interpolatedNormal /= GetNumberOfFacesUsingVertex(i, oIndices);
			oNormals[i] = glm::normalize(interpolatedNormal);
		}

		return true;
	}
}
