#pragma once
#include "Precompile.h"
#include <climits>

namespace rtm
{
	template<typename T>
	inline T randCenter()
	{
		return (std::rand() / static_cast<T>(RAND_MAX) - static_cast<T>(0.5)) * static_cast<T>(2);
	}
	
	template<typename T>
	inline T rand0to1()
	{
		return std::rand() / static_cast<T>(RAND_MAX);
	}

	template<typename T>
	inline bool testPossible(const T v)
	{
		return v < rand0to1<T>();
	}

	inline rtm::Vec3 randomVec3()
	{
		return {
			randCenter<rtm::RtmGeneralType>(),
			randCenter<rtm::RtmGeneralType>(),
			randCenter<rtm::RtmGeneralType>()
		};
	}

	inline rtm::Vec3 randomUnitVec3()
	{
		rtm::RtmGeneralType radx = rtm::rand0to1<rtm::RtmGeneralType>()*3.14159265358979;		//0~360
		rtm::RtmGeneralType rady = rtm::randCenter<rtm::RtmGeneralType>()*3.14159265358979*0.5;	//-90~90
		return
		{
			std::cos(radx)*std::sin(rady),
			std::sin(radx)*std::sin(rady),
			std::cos(rady)
		};
	}

	template <typename T, Feature features = Feature::none>
	inline rtm::Vec<T, 3, features> reflect(const rtm::Vec<T, 3, features>&v, const rtm::Vec<T, 3, features>& n)
	{
		return v - 2 * rtm::dot(v, n)*n;
	}
}