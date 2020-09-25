#include "Precompile.h"
#include "MaterialLambertian.h"

bool rd::MaterialLambertian::scatter(const rtm::Ray3 & ray, const HitRecord & rec, rtm::Vec3& attenuation, rtm::Ray3 & scatterRay) const
{
	scatterRay = { rtm::normalize(rec.normal + rtm::randomUnitVec3()),rec.p };
	attenuation = albedo;
	return true;
}
