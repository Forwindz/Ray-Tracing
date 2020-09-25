#include "AABB.h"
//slab method
bool rd::AABB::rayHit(const rtm::Ray3 & ray, rtm::Decimal tMin, rtm::Decimal tMax)
{
	for (int i = 0; i < 3; ++i)
	{
		const rtm::Decimal invD = 1 / ray.d[i];
		const rtm::Decimal t0 = (a[i] - ray.o[i])*invD;
		const rtm::Decimal t1 = (b[i] - ray.o[i])*invD;
		if (invD > 0)
		{
			tMin = std::max(t0, tMin);
			tMax = std::min(t1, tMax);
		}
		else
		{
			tMin = std::max(t1, tMin);
			tMax = std::min(t0, tMax);
		}
		if (tMax <= tMin)return false;
	}
	return true;
}

void rd::unionAABB(const AABB & a, const AABB & b, AABB & result)
{
	result.a = rtm::vecMinEachDim(a.a, b.a);
	result.b = rtm::vecMaxEachDim(a.b, b.b);
}

rd::AABB rd::unionAABB(const AABB & a, const AABB & b)
{
	AABB result;
	unionAABB(a, b, result);
	return result;
}
