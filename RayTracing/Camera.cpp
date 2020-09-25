#include "Precompile.h"
#include "Camera.h"

void rd::Camera::setTime(const rtm::Decimal begin, const rtm::Decimal end)
{
	timeBegin = begin;
	timeEnd = end;
}

void rd::Camera::setView(rtm::Vec3 view, rtm::Vec3 up)
{
	n = view;
	u = rtm::cross(view, up);
	v = rtm::cross(n, u);
}

void rd::Camera::rotateHorizonal(const rtm::Decimal hor)
{
	n = rtm::rotate(n, v, hor);
	setView(n, v);
}

void rd::Camera::rotateVertical(const rtm::Decimal ver)
{
	n = rtm::rotate(n, u, ver);
	setView(n, v);
}

void rd::Camera::update()
{
	const auto ratio = width / static_cast<rtm::Decimal>(height);
	halfHeight = std::tan(fov * static_cast<rtm::Decimal>(0.5))*zNear;
	halfWidth = halfHeight * ratio;
	pixelHeight = halfHeight * 2 / height;
	pixelWidth = halfWidth * 2 / width;
}

rtm::Vec2 rd::Camera::getPixelRange() const
{
	return rtm::Vec2(pixelWidth, pixelHeight);
}

rtm::Vec2 rd::Camera::getCenterPos(const int x, const int y) const
{
	return rtm::Vec2(
		x / static_cast<rtm::Decimal>(width) * 2 - 1,
		1 - y / static_cast<rtm::Decimal>(height) * 2
	);
}

rtm::Vec2 rd::Camera::getJitterPos() const
{
	return rtm::Vec2(pixelWidth*rtm::randCenter<rtm::Decimal>(), pixelHeight*rtm::randCenter<rtm::Decimal>());
}

rtm::Ray3 rd::Camera::getRayScreenPos(const int x, const int y) const
{
	auto&& pos = getCenterPos(x, y);
	return getRayCenterPos(pos.x, pos.y);
}

rtm::Ray3 rd::Camera::getRayCenterPos(const rtm::Decimal x, const rtm::Decimal y) const
{
	return rtm::Ray3{ rtm::normalize(y * halfHeight * v + x * halfWidth * u + zNear * n),pos };
}

rtm::Decimal rd::Camera::getTime() const
{
	return rtm::randRange(timeBegin, timeEnd);
}

rd::TimeRay rd::Camera::getTimeRayCenterPos(const rtm::Decimal x, const rtm::Decimal y) const
{
	return rd::TimeRay(getRayCenterPos(x, y), getTime());
}
