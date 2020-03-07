#include "stdafx.h"
#include "CTexture.h"
#include "SOIL.h"
#include <iostream>

void CTexture::Load(const std::string& file)
{
	unsigned char* image = SOIL_load_image(file.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);
	if (!image)
	{
		std::cout << SOIL_last_result() << std::endl;
	}
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
