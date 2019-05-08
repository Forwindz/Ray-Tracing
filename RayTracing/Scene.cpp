#include "Scene.h"

rd::Scene::~Scene()
{
	for (Hitable* a : hitObj)
	{
		delete a;
	}
}

void rd::Scene::removeHitable(Hitable * hitable)
{
	auto result = std::find(hitObj.begin(), hitObj.end(), hitable);
	if (hitObj.end() != result)
	{
		hitObj.erase(result);
	}
}

bool rd::Scene::rayHit(const rtm::Ray3 & ray, rtm::RtmGeneralType tMin, rtm::RtmGeneralType tMax, HitRecord & record)
{
	HitRecord hr;
	bool hitSomething = false;
	double currentT = tMax;
	for (auto& x : hitObj)
	{
		if (x->rayHit(ray, tMin, tMax, hr))
		{
			hitSomething = true;
			if (hr.t < currentT)
			{
				record = hr;
				currentT = hr.t;
			}
		}
	}
	return hitSomething;
}
