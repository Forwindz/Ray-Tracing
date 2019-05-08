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
			rtm::RtmGeneralType r_ = static_cast<rtm::RtmGeneralType>(1),
			Material* material = new MaterialLambertian(rtm::Vec3(1, 1, 1))) 
			:o(o_), r(r_), Hitable(material) {};

		rtm::Vec3 o;
		rtm::RtmGeneralType r;

		virtual bool rayHit(const rtm::Ray3& ray, rtm::RtmGeneralType tMin, rtm::RtmGeneralType tMax, HitRecord& record);

	protected:

	};
}