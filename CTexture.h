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

