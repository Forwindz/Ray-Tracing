#pragma once
#include "Precompile.h"
#include "Scene.h"
namespace rd
{
	class MaterialMetal : public Material
	{
	public:
		MaterialMetal(
			const rtm::Vec3& a = rtm::Vec3(0, 0, 0),
			const rtm::Decimal fuz = 0.0f)
			:albedo(a), fuzz(fuz) {};
		virtual bool scatter(const rtm::Ray3& ray, const HitRecord& rec, rtm::Vec3& attenuation, rtm::Ray3& scatterRay) const;

		rtm::Vec3 albedo;
		rtm::Decimal fuzz;
	};
}