#include "stdafx.h"
#include "CTexture.h"
#include "SOIL.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

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
#pragma pack(push,1)
struct BMPFileHeader {
	uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42
	uint32_t file_size{ 0 };               // Size of the file (in bytes)
	uint16_t reserved1{ 0 };               // Reserved, always 0
	uint16_t reserved2{ 0 };               // Reserved, always 0
	uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)
};

struct BMPInfoHeader {
	uint32_t size{ 0 };                      // Size of this header (in bytes)
	int32_t width{ 0 };                      // width of bitmap in pixels
	int32_t height{ 0 };                     // width of bitmap in pixels
	//       (if positive, bottom-up, with origin in lower left corner)
	//       (if negative, top-down, with origin in upper left corner)
	uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
	uint16_t bit_count{ 0 };                 // No. of bits per pixel
	uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
	uint32_t size_image{ 0 };                // 0 - for uncompressed images
	int32_t x_pixels_per_meter{ 0 };
	int32_t y_pixels_per_meter{ 0 };
	uint32_t colors_used{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
	uint32_t colors_important{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct BMPColorHeader {
	uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
	uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
	uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
	uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
	uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
	uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};

#pragma pack(pop)

void CHeightMap::Load(const std::string& file)
{
	BMPFileHeader file_header;
	BMPInfoHeader bmp_info_header;
	BMPColorHeader bmp_color_header;
	ifstream ifs(file, ios::binary);
	if (!ifs)
	{
		cout << "file not found" << endl;
		return;
	}
	ifs.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
	if (file_header.file_type != 0x4D42) {
		cout << "wrong format" << endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
	
	if (bmp_info_header.bit_count == 32)
	{
		ifs.read(reinterpret_cast<char*>(&bmp_color_header), sizeof(bmp_color_header));
	}

	Height = bmp_info_header.height;
	Width = bmp_info_header.width;

	ifs.seekg(file_header.offset_data, ios::beg);

	Data.resize(Height, vector<glm::vec3>(Width));

	glm::vec3 pixel;
	unsigned char color;

	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			
			ifs.read(reinterpret_cast<char*>(&color), sizeof(color));
			pixel.b = color;

			ifs.read(reinterpret_cast<char*>(&color), sizeof(color));
			pixel.r = color;

			ifs.read(reinterpret_cast<char*>(&color), sizeof(color));
			pixel.g = color;

			Data[Height - i - 1][j] = pixel;
		}
		//ifs.read(reinterpret_cast<char*>(&color), sizeof(color));
	}

	//for (auto& row : Data)
	//{
	//	for (const auto& pixel : row)
	//	{
	//		cout << setw(5) << 255 - (int)pixel.r << ' ';
	//	}
	//	cout << endl;
	//}
}

float CHeightMap::GetHeight(int x, int z)
{
	return 255 - Data[x][z].r;
}

void CCubeTexture::Load(const std::array<std::string, 6>& files)
{
	Coords = 3;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Texture);

	for (size_t i = 0; i < files.size(); i++)
	{
		unsigned char* image = SOIL_load_image(files[i].c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);
		if (!image)
		{
			std::cout << SOIL_last_result() << std::endl;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
