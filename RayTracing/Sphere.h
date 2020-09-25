#pragma once
#include "Precompile.h"
#include "MaterialLambertian.h"
#include "Scene.h"

namespace rd
{
	class Sphere: public Hitable
	{
	public:
		Sphere(){};
		Sphere(
			rtm::Vec3 o_,
			rtm::Decimal r_ = static_cast<rtm::Decimal>(1),
			Material* material = new MaterialLambertian(rtm::Vec3(1, 1, 1))) 
			:o(o_), r(r_), matPtr(material) {};
		rtm::Vec3 o;
		rtm::Decimal r;
		Material *matPtr;
		virtual bool rayHit(const rtm::Ray3& ray, rtm::Decimal tMin, rtm::Decimal tMax, HitRecord& record, rtm::Decimal time = 0);
		virtual void move(const rtm::Vec3& movement) { o += movement; };
	protected:

	};
}