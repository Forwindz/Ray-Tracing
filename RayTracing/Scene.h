#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"
#include "Hitable.h"
namespace rd
{
	struct HitRecord;
	class Material;
	class Hitable;
	class Scene;

	class Scene: virtual public Hitable
	{
	public:
		~Scene();
		void addHitable(Hitable* hitable) { hitObj.emplace_back(hitable); };
		void removeHitable(Hitable* hitable);
		virtual bool rayHit(const rtm::Ray3& ray, rtm::Decimal tMin, rtm::Decimal tMax, HitRecord& record, rtm::Decimal time=0);
	protected:
		std::vector<Hitable*> hitObj;

	};
	
}