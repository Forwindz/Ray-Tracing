#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"
namespace rd
{
	struct HitRecord;

	class Material
	{
	public:
		/*
		ray:			input ray
		rec:			input hit information
		attenuation:	output attenuation
		scatterRay:		output ray
		return:			return true if return a ray by scatterRay, otherwise scatterRay deliver nothing.
		*/
		virtual bool scatter(const rtm::Ray3& ray, const HitRecord& rec, rtm::Vec3& attenuation, rtm::Ray3& scatterRay) const = 0;
	};

	class MaterialManager
	{
	public:
		std::vector<Material*> materials;
		Material* addMaterial(Material* mat)
		{
			materials.emplace_back(mat);
			return mat;
		}
		~MaterialManager()
		{
			for (Material* m : materials)
			{
				delete m;
			}
		}
	protected:

	};
}