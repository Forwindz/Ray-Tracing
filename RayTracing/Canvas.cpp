#include "Canvas.h"

rd::Canvas::Canvas(const int width, const int height)
{
	changeSize(width, height);
}

rd::Canvas::Canvas(Canvas && canvas)
{
	mWidth = canvas.mWidth;
	mHeight = canvas.mHeight;
	mData = canvas.mData;
	canvas.mData = nullptr;
}

rd::Canvas::~Canvas()
{
	if (mData != nullptr)delete[] mData;
}

void rd::Canvas::fillColor(const rtm::Vec3 & color)
{
	std::fill(mData, mData + mWidth * mHeight, color);
}

void rd::Canvas::saveBMP(const std::string & fileName)
{
	if (mData == nullptr)
	{
		std::string s = "ERROR: try to save empty bitmap " + fileName;
		std::cout << s << "\n";
		throw std::exception(s.c_str());
	}
	//convert to uchar
	rtm::Vec3uc* bitData = new rtm::Vec3uc[mWidth*mHeight];
	for (auto i = 0; i < mWidth*mHeight; i++)
	{
		auto org = mData[i] * 255 + 0.5;
		//RGB float -> BGR uchar
		bitData[i] = rtm::Vec3uc(
			static_cast<uchar>(org.b),
			static_cast<uchar>(org.g),
			static_cast<uchar>(org.r));
	}
	try
	{
		rd::saveBitmap(fileName, mWidth, mHeight, reinterpret_cast<uchar*>(bitData));
	}
	catch (const std::exception& e)
	{
		if (bitData != nullptr) delete[] bitData;
		throw e;
	}

	delete[] bitData;
}

void rd::Canvas::changeSize(const int width, const int height)
{
	if (mData != nullptr)
		delete[] mData;
	mWidth = width;
	mHeight = height;
	mData = new rtm::Vec3[width*height];
}

rtm::Vec3 * rd::Canvas::operator[](const int indices)
{
	return mData + indices * mWidth;
}

rtm::Vec3 & rd::Canvas::at(const int x, const int y)
{
	runtimeAssert(x >= 0 && y >= 0 && x < mWidth&&y < mHeight, "Wrong Index");
	return mData[mWidth*y + x];
}
