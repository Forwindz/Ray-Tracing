#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"

namespace rd
{
	class Camera
	{
	public:
		rtm::Vec3 pos;
		rtm::RtmGeneralType zNear, zFar, fov;
		int width, height;

		void setView(rtm::Vec3 view, rtm::Vec3 up);
		void rotateHorizonal(const rtm::RtmGeneralType hor);
		void rotateVertical(const rtm::RtmGeneralType ver);
		void update();
		rtm::Vec2 getPixelRange() const;
		rtm::Vec2 getCenterPos(const int x, const int y) const;
		inline rtm::Vec2 getPixelSize() const { return { pixelWidth,pixelHeight }; };
		rtm::Vec2 getJitterPos() const;
		rtm::Ray3 getRayScreenPos(const int x, const int y) const;
		rtm::Ray3 getRayCenterPos(const rtm::RtmGeneralType x, const rtm::RtmGeneralType y) const;
	protected:
		//right,up,watch
		rtm::Vec3 u, v, n;
		rtm::RtmGeneralType halfHeight,pixelHeight;
		rtm::RtmGeneralType halfWidth,pixelWidth;
	};
}