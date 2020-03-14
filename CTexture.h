#pragma once
#include <string>
class CTexture
{
public:
	GLuint Texture = -1;
	int Coords = 2;
	int Width, Height;
	void Load(const std::string& file);
};

class CHeightMap
{
public:
	int32_t Width, Height;
	std::vector<std::vector<glm::vec3>> Data;
	void Load(const std::string& file);
	float GetHeight(int x, int z);
};

class CCubeTexture : public CTexture
{
public:
	void Load(const std::array<std::string,6>& files);
};
