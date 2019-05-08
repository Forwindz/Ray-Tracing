#include "MaterialMetal.h"

bool rd::MaterialMetal::scatter(const rtm::Ray3 & ray, const HitRecord & rec, rtm::Vec3& attenuation, rtm::Ray3 & scatterRay) const
{
	scatterRay = { rtm::normalize(rtm::reflect(ray.d, rec.normal) + rtm::randomUnitVec3()*fuzz),ray.o };
	attenuation = albedo;
	return rtm::dot(scatterRay.d,rec.normal) > 0;
}
