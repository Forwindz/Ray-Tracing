#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"
#include "globalTools.h"
#include "Saver.h"

namespace rd
{
	class Canvas
	{
	public:
		Canvas(const int width = 1280, const int height = 720);
		Canvas(Canvas&& canvas);
		~Canvas();

		void fillColor(const rtm::Vec3& color);
		void saveBMP(const std::string& fileName);
		void changeSize(const int width, const int height);

		constexpr inline int getWidth()const { return mWidth; }
		constexpr inline int getHeight()const { return mHeight; }

		//no check
		rtm::Vec3* operator[](const int indices);
		//check boundary
		rtm::Vec3& at(const int x, const int y);
	protected:

		int mWidth;
		int mHeight;
		rtm::Vec3* mData = nullptr;
		
	};
}