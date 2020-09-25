#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"
#include "Material.h"
namespace rd
{
	/*
	Ray t:		transport time
	Point p:	hit point
	Normal n:	normal at this point
	*/
	struct HitRecord
	{
		rtm::Decimal t;
		rtm::Vec3 p, normal;
		Hitable* hitObject;
	};

	class Hitable
	{
	public:
		/*
		Hitable() :matPtr(nullptr) {};
		Hitable(Material* material) :matPtr(material) {};
		Material *matPtr;
		virtual ~Hitable() {};*/
		/*
		ray:		input ray
		tMin,tMax:	limit t to [Min~tMax]
		record:		output hit result
		return:		wether the ray hit anything
		*/
		virtual bool rayHit(const rtm::Ray3& ray, rtm::Decimal tMin, rtm::Decimal tMax, HitRecord& record, rtm::Decimal time) = 0;
		// move the whole object along "movement"
		virtual void move(const rtm::Vec3& movement) {};
	};

	class BoundingVolume
	{
	public:
		virtual bool rayHit(const rtm::Ray3& ray, rtm::Decimal tMin, rtm::Decimal tMax) = 0;
	};
}