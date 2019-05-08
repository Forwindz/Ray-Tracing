#pragma once
#include "Precompile.h"
#include "Scene.h"
namespace rd
{

	class MaterialLambertian : public Material
	{
	public:
		MaterialLambertian(const rtm::Vec3& a = rtm::Vec3(0, 0, 0)) :albedo(a) {};;
		virtual bool scatter(const rtm::Ray3& ray, const HitRecord& rec, rtm::Vec3& attenuation, rtm::Ray3& scatterRay) const;

		rtm::Vec3 albedo;
	};
}