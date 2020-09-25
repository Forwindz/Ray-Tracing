#pragma once
#include "Precompile.h"
#include <climits>
#include <random>
namespace rtm
{
	namespace detail
	{
		static std::default_random_engine randEngine;
		template<typename T>
		static std::uniform_real_distribution<T> randrd(static_cast<T>(0), static_cast<T>(1));
	}

	template<typename T = rtm::Decimal>
	inline T rand0to1()
	{
		return detail::randrd<T>(detail::randEngine);
	}

	template<typename T>
	inline T randCenter()
	{
		return (rand0to1<T>() - static_cast<T>(0.5)) * static_cast<T>(2);
	}

	template<typename T>
	inline T randRange(const T minv, const T maxv)
	{
		return (maxv - minv)*rand0to1<T>() + minv;
	}

	template<typename T>
	inline bool testPossible(const T v)
	{
		return v < rand0to1<T>();
	}

	inline rtm::Vec3 randomVec3()
	{
		return {
			randCenter<rtm::Decimal>(),
			randCenter<rtm::Decimal>(),
			randCenter<rtm::Decimal>()
		};
	}

	inline rtm::Vec3 randomUnitVec3()
	{
		rtm::Decimal radx = rtm::rand0to1<rtm::Decimal>()*3.14159265358979;		//0~360
		rtm::Decimal rady = rtm::randCenter<rtm::Decimal>()*3.14159265358979*0.5;	//-90~90
		return
		{
			std::cos(radx)*std::sin(rady),
			std::sin(radx)*std::sin(rady),
			std::cos(rady)
		};
	}

	template <typename T>
	inline auto min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	inline auto max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template <typename T, Feature features = Feature::none>
	inline rtm::Vec<T, 3, features> vecMinEachDim(const rtm::Vec<T, 3, features>&a, const rtm::Vec<T, 3, features>& b)
	{
		return rtm::Vec<T, 3, features>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
	}

	template <typename T, Feature features = Feature::none>
	inline rtm::Vec<T, 3, features> vecMaxEachDim(const rtm::Vec<T, 3, features>&a, const rtm::Vec<T, 3, features>& b)
	{
		return rtm::Vec<T, 3, features>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
	}

	template <typename T, Feature features = Feature::none>
	inline rtm::Vec<T, 3, features> reflect(const rtm::Vec<T, 3, features>&v, const rtm::Vec<T, 3, features>& n)
	{
		return v - 2 * rtm::dot(v, n)*n;
	}
}