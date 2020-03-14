#pragma once
class CGLMesh;
class CObjLoader
{
public:
	static CGLMesh* Load(const std::string& file);
	static CGLMesh* LoadCube();
};

