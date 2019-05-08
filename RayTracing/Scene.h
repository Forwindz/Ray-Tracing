#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"

namespace rd
{
	struct HitRecord;
	class Material;
	class Hitable;
	class Scene;

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

	class Hitable
	{
	public:
		Hitable() :matPtr(nullptr) {};
		Hitable(Material* material) :matPtr(material) {};
		Material *matPtr;
		~Hitable() { if (matPtr != nullptr)delete matPtr; };
		/*
		ray:		input ray
		tMin,tMax:	limit t to [Min~tMax]
		record:		output hit result
		return:		wether the ray hit anything
		*/
		virtual bool rayHit(const rtm::Ray3& ray, rtm::RtmGeneralType tMin, rtm::RtmGeneralType tMax, HitRecord& record) = 0;
	};

	class Scene: virtual public Hitable
	{
	public:
		~Scene();
		void addHitable(Hitable* hitable) { hitObj.emplace_back(hitable); };
		void removeHitable(Hitable* hitable);
		virtual bool rayHit(const rtm::Ray3& ray, rtm::RtmGeneralType tMin, rtm::RtmGeneralType tMax, HitRecord& record);
	protected:
		std::vector<Hitable*> hitObj;

	};

	/*
	Ray t:		transport time
	Point p:	hit point
	Normal n:	normal at this point
	*/
	struct HitRecord
	{
		rtm::RtmGeneralType t;
		rtm::Vec3 p, normal;
		Hitable* hitObject;
	};

	
}