#pragma once
#include "Precompile.h"
#include "Scene.h"
namespace rd
{

	class MaterialDielectric : public Material
	{
	public:
		MaterialDielectric(const rtm::Vec3& a = rtm::Vec3(0, 0, 0), const rtm::RtmGeneralType idxv = 1.0) :idx(idxv), albedo(a) {};
		virtual bool scatter(const rtm::Ray3& ray, const HitRecord& rec, rtm::Vec3& attenuation, rtm::Ray3& scatterRay) const;

		rtm::RtmGeneralType idx;
		rtm::Vec3 albedo;
	protected:
		bool refract(
			const rtm::Vec3& v,
			const rtm::Vec3& n,
			rtm::RtmGeneralType novert,
			rtm::Vec3& refracted
		) const;

		rtm::RtmGeneralType schlick(const rtm::RtmGeneralType cosv, const rtm::RtmGeneralType idx) const;
	};
}