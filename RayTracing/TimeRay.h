#pragma once
#include "Precompile.h"
#include "Ray.h"

namespace rd
{
	struct TimeRay
	{
		TimeRay() {};
		TimeRay(const rtm::Ray3 _r, const rtm::Decimal _t) :r(_r), t(_t) {};
		rtm::Ray3 r;//ray
		rtm::Decimal t;//time
	};
}
