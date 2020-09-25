#pragma once
#include "Precompile.h"
#include "Enums.h"
#include "Vector.h"
namespace rtm
{
	/*
		y = dt+o
	*/
	template<typename T, int vecLen, Feature features = Feature::none>
	class Ray
	{
	public:
		Vec<T, vecLen, features> d, o;
		Vec<T, vecLen, features> getPos(const T& t) const;
	};

	template<typename T, int vecLen, Feature features>
	inline Vec<T, vecLen, features> Ray<T, vecLen, features>::getPos(const T & t) const
	{
		return d * t + o;
	}

	typedef Ray<Decimal,		3>			Ray3;
	typedef Ray<float,				3>			Ray3f;
	typedef Ray<double,				3>			Ray3d;
	typedef Ray<long double,		3>			Ray3ld;
	typedef Ray<int,				3>			Ray3i;
	typedef Ray<unsigned int,		3>			Ray3ui;
	typedef Ray<short int,			3>			Ray3si;
	typedef Ray<unsigned short int, 3>			Ray3usi;
	typedef Ray<long int,			3>			Ray3li;
	typedef Ray<unsigned long int,	3>			Ray3uli;
	typedef Ray<long long,			3>			Ray3ll;
	typedef Ray<unsigned long long, 3>			Ray3ull;
	typedef Ray<char,				3>			Ray3c;
	typedef Ray<unsigned char,		3>			Ray3uc;
	typedef Ray<signed char,		3>			Ray3sc;
	typedef Ray<wchar_t,			3>			Ray3wc;

	typedef Ray<float,				4>			Ray4f;
	typedef Ray<double,				4>			Ray4d;
	typedef Ray<long double,		4>			Ray4ld;
	typedef Ray<int,				4>			Ray4i;
	typedef Ray<unsigned int,		4>			Ray4ui;
	typedef Ray<short int,			4>			Ray4si;
	typedef Ray<unsigned short int, 4>			Ray4usi;
	typedef Ray<long int,			4>			Ray4li;
	typedef Ray<unsigned long int,	4>			Ray4uli;
	typedef Ray<long long,			4>			Ray4ll;
	typedef Ray<unsigned long long, 4>			Ray4ull;
	typedef Ray<char,				4>			Ray4c;
	typedef Ray<unsigned char,		4>			Ray4uc;
	typedef Ray<signed char,		4>			Ray4sc;
	typedef Ray<wchar_t,			4>			Ray4wc;
}