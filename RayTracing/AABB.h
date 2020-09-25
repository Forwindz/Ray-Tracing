#pragma once
#include "Precompile.h"
#include "Hitable.h"
#include "Ray.h"
namespace rd
{
	class AABB : virtual public BoundingVolume
	{
	public:
		rtm::Vec3 a,b;//small, big
		AABB() {}
		AABB(const rtm::Vec3& _min, const rtm::Vec3& _max) :a(_min), b(_max) {};
		virtual bool rayHit(const rtm::Ray3& ray, rtm::Decimal tMin, rtm::Decimal tMax);
	};

	void unionAABB(const AABB& a,const AABB& b, AABB& result);
	AABB unionAABB(const AABB& a,const AABB& b);

}