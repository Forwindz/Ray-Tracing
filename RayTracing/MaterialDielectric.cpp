#include "MaterialDielectric.h"

bool rd::MaterialDielectric::scatter(const rtm::Ray3 & ray, const HitRecord & rec, rtm::Vec3 & attenuation, rtm::Ray3 & scatterRay) const
{
	const auto reflected = rtm::reflect(ray.d, rec.normal);
	attenuation = albedo;

	rtm::Vec3 outNormal;
	rtm::RtmGeneralType cosv, outIdx;
	const auto dotv = rtm::dot(ray.d, rec.normal);
	if ( dotv > 0)	//from inside to outside
	{
		outNormal = -rec.normal;
		outIdx = idx;
		cosv = outIdx * dotv;
	}
	else			//from outside to inside
	{
		outNormal = rec.normal;
		outIdx = 1 / idx;
		cosv = -outIdx * dotv;
	}

	rtm::RtmGeneralType refractProb;
	rtm::Vec3 refracted;
	if (refract(ray.d, outNormal, outIdx, refracted))
	{
		refractProb = schlick(cosv, idx);
	}
	else
	{
		refractProb = 1.0;
		scatterRay = { reflected,rec.p };
	}

	//need rewrite later
	if (rtm::testPossible(refractProb))
	{
		scatterRay = { reflected,rec.p };
	}
	else
	{
		scatterRay = { reflected,rec.p };
	}
	return true;
}

rtm::RtmGeneralType rd::MaterialDielectric::schlick(const rtm::RtmGeneralType cosv, const rtm::RtmGeneralType idx) const
{
	const auto r0 = (1 - idx) / (1 + idx);
	const auto r1 = r0 * r0;
	return r1 + (1 - r1)*std::pow(1 - cosv, 5);
}

bool rd::MaterialDielectric::refract(const rtm::Vec3 & v, const rtm::Vec3 & n, rtm::RtmGeneralType novert, rtm::Vec3 & refracted) const
{
	const auto dt = rtm::dot(v, n);
	const auto discriminant = 1 - novert * novert*(1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = novert * (v - n * dt) - n * std::sqrt(discriminant);
		return true;
	}
	return false;
}
