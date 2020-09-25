#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"
#include "TimeRay.h"
namespace rd
{
	class Camera
	{
	public:
		rtm::Vec3 pos;
		rtm::Decimal zNear, zFar, fov;
		int width, height;
		rtm::Decimal timeBegin, timeEnd;
		void setTime(const rtm::Decimal begin, const rtm::Decimal end);
		void setView(rtm::Vec3 view, rtm::Vec3 up);
		void rotateHorizonal(const rtm::Decimal hor);
		void rotateVertical(const rtm::Decimal ver);
		void update();
		rtm::Vec2 getPixelRange() const;
		rtm::Vec2 getCenterPos(const int x, const int y) const;
		inline rtm::Vec2 getPixelSize() const { return { pixelWidth,pixelHeight }; };
		rtm::Vec2 getJitterPos() const;
		rtm::Ray3 getRayScreenPos(const int x, const int y) const;
		rtm::Ray3 getRayCenterPos(const rtm::Decimal x, const rtm::Decimal y) const;
		rtm::Decimal getTime() const;
		rd::TimeRay getTimeRayCenterPos(const rtm::Decimal x, const rtm::Decimal y) const;
	protected:
		//right,up,watch
		rtm::Vec3 u, v, n;
		rtm::Decimal halfHeight,pixelHeight;
		rtm::Decimal halfWidth,pixelWidth;
	};
}