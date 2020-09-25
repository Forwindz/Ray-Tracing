#pragma once
#include "Precompile.h"
#include "RayTracingMath.h"
#include "Scene.h"
namespace rd
{

	class Motion
	{
	public:
		Motion(const rtm::Decimal _timeBegin, const rtm::Decimal _timeEnd) :timeBegin(_timeBegin), timeEnd(_timeEnd) {};
		virtual ~Motion() {};
		rtm::Decimal timeBegin, timeEnd;
		virtual void applyObject(const rtm::Decimal curTime, Hitable& initObject) = 0;
	};

	class LinearMotion : virtual public Motion
	{
	public:
		LinearMotion(const rtm::Decimal _timeBegin, const rtm::Decimal _timeEnd, const rtm::Vec3 _from, const rtm::Vec3 _to)
			:Motion(_timeBegin, _timeEnd), from(_from), to(_to) {};
		virtual ~LinearMotion() {};
		rtm::Vec3 from, to;
		virtual void applyObject(const rtm::Decimal curTime, Hitable& initObject)
		{
			initObject.move((to - from)*curTime / (timeEnd - timeBegin));
		}
	};

	template <typename T>
	class MovingObject : virtual public Hitable
	{
	public:
		MovingObject(Motion* _motion, T* _object);
		virtual ~MovingObject();
		Motion* motion;
		T* object;
		virtual bool rayHit(const rtm::Ray3& ray, rtm::Decimal tMin, rtm::Decimal tMax, HitRecord& record, rtm::Decimal time = 0);
	protected:
		T tempObj;
	};

	template<typename T>
	inline MovingObject<T>::MovingObject(Motion * _motion, T * _object)
		:motion(_motion), object(_object)
	{
	}

	template<typename T>
	inline MovingObject<T>::~MovingObject()
	{
		delete motion;
		delete object;
	}

	template<typename T>
	inline bool MovingObject<T>::rayHit(const rtm::Ray3 & ray, rtm::Decimal tMin, rtm::Decimal tMax, HitRecord & record, rtm::Decimal time)
	{
		tempObj = T(*object); // shallow copy
		motion->applyObject(time, tempObj);
		return tempObj.rayHit(ray, tMin, tMax, record, time);
	}
}