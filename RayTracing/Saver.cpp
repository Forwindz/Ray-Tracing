#include "Precompile.h"
#include "Saver.h"

void rd::saveBitmap(const std::string & fileName, const int width, const int height, const uchar * data)
{
	std::ofstream os;
	os.open(fileName, std::ios::binary | std::ios::out);
	if (!os.is_open())
	{
		std::string&& s = "Cannot open " + fileName;
		std::cout << "ERROR:" << s << "\n";
		throw std::exception(s.c_str());
	}

	BitmapHeaderTag tag;
	BitmapHeaderInfo info;
	tag.bfType[0] = 'B';
	tag.bfType[1] = 'M';
	tag.bfSize = static_cast<std::uint32_t>(sizeof(uchar) * width * height * 3 + sizeof(tag) + sizeof(info));
	tag.bfReserved1 = tag.bfReserved2 = 0;
	tag.bfOffBits = sizeof(tag) + sizeof(info);

	info.biSize = sizeof(BitmapHeaderInfo);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biBitCount = sizeof(uchar) * 3 * 8;
	info.biCompression = 0;
	info.biSizeImage = width * height * 3;
	info.biXPelsPerMeter = 0;
	info.biYPelsPerMeter = 0;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	os.write(reinterpret_cast<char*>(&tag), sizeof(tag));
	os.write(reinterpret_cast<char*>(&info), sizeof(info));
	os.write(reinterpret_cast<const char*>(data), sizeof(uchar) * width * height * 3);

	os.close();
}
