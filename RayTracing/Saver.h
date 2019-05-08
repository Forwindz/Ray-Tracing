#pragma once
#include "Precompile.h"
#include "globalTools.h"
namespace rd
{
#pragma pack(push,1)
	struct BitmapHeaderTag
	{
		char bfType[2];
		std::uint32_t bfSize;
		std::uint16_t bfReserved1;
		std::uint16_t bfReserved2;
		std::uint32_t bfOffBits;
	};
#pragma pack(pop)

	struct BitmapHeaderInfo
	{
		std::uint32_t biSize;
		std::int32_t biWidth;
		std::int32_t biHeight;
		std::uint16_t biPlanes;
		std::uint16_t biBitCount;
		std::uint32_t biCompression;
		std::uint32_t biSizeImage;
		std::int32_t biXPelsPerMeter;
		std::int32_t biYPelsPerMeter;
		std::uint32_t biClrUsed;
		std::uint32_t biClrImportant;
	};
	void saveBitmap(const std::string& fileName, const int width, const int height, const uchar* data);
}