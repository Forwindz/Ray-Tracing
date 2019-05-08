#include "Sphere.h"

bool rd::Sphere::rayHit(const rtm::Ray3 & ray, rtm::RtmGeneralType tMin, rtm::RtmGeneralType tMax, HitRecord & record)
{
	const rtm::Vec3 oc = ray.o - o;
	const rtm::RtmGeneralType b = 2 * rtm::dot(oc, ray.d);
	const rtm::RtmGeneralType c = rtm::dot(oc, oc) - r * r;
	const rtm::RtmGeneralType discriminant = b * b - 4 * c;
	if (discriminant > 0)
	{
		{
			const rtm::RtmGeneralType temp = (-b - std::sqrt(discriminant))*0.5;
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
			const rtm::RtmGeneralType temp = (-b + std::sqrt(discriminant))*0.5;
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
