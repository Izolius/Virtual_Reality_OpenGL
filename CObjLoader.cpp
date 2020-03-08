#include "stdafx.h"
#include "CObjLoader.h"
#include <cstdio>
#include "OBJ_Loader.h"

CGLObject* CObjLoader::Load(const std::string& FileName)
{
	objl::Loader Loader;
	bool loadout = Loader.LoadFile(FileName);
	if (!loadout)
	{
		std::cout << "failed to load " + FileName << std::endl;
		throw new std::exception(("failed to load " + FileName).c_str());
	}


	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	temp_vertices.reserve(Loader.LoadedVertices.size());
	temp_uvs.reserve(Loader.LoadedVertices.size());
	temp_normals.reserve(Loader.LoadedVertices.size());

	for (auto& Vertex : Loader.LoadedVertices)
	{
		auto& Pos = Vertex.Position;
		temp_vertices.push_back({ Pos.X, Pos.Y, Pos.Z });
		temp_uvs.push_back({ Vertex.TextureCoordinate.X,Vertex.TextureCoordinate.Y });
		auto& Norm = Vertex.Normal;
		temp_normals.push_back({ Norm.X, Norm.Y, Norm.Z });
	}
	

	CGLObject* result = new CGLObject();
	result->SetVertices(std::move(temp_vertices));
	result->SetIndices(std::move(Loader.LoadedIndices));
	result->SetUVs(std::move(temp_uvs));
	return result;
}
