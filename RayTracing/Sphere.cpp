#include "Precompile.h"
#include "Sphere.h"

bool rd::Sphere::rayHit(const rtm::Ray3 & ray, rtm::Decimal tMin, rtm::Decimal tMax, HitRecord & record, rtm::Decimal time)
{
	const rtm::Vec3 oc = ray.o - o;
	const rtm::Decimal b = 2 * rtm::dot(oc, ray.d);
	const rtm::Decimal c = rtm::dot(oc, oc) - r * r;
	const rtm::Decimal discriminant = b * b - 4 * c;
	if (discriminant > 0)
	{
		{
			const rtm::Decimal temp = (-b - std::sqrt(discriminant))*0.5;
			if (temp<tMax && temp>tMin)
			{
				record.t = temp;
				record.p = ray.getPos(record.t);
				record.normal = (record.p - o) / r;
				record.hitObject = this;
				return true;
			}
		}
		{
			const rtm::Decimal temp = (-b + std::sqrt(discriminant))*0.5;
			if (temp<tMax && temp>tMin)
			{
				record.t = temp;
				record.p = ray.getPos(record.t);
				record.normal = (record.p - o) / r;
				record.hitObject = this;
				return true;
			}
		}
	}

	return false;
}
