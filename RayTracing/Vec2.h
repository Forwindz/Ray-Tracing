#pragma once
#include "Precompile.h"
#include "Vector.h"
namespace rtm
{
	template <typename T, Feature features>
	class Vec<T, 2, features>
	{
	public:

		Vec() noexcept {};
		Vec(const Matrix<T, 2, 1, features>& a);
		Vec(const Vec<T, 2, features>& va) noexcept;
		explicit Vec(const Vec<T, 3, features>& vy) noexcept;
		explicit Vec(const Vec<T, 4, features>& xy) noexcept;
		Vec(const T& x, const T& y)noexcept;
		Vec(const T& all)noexcept;
		~Vec() {};
		//return m[v] with checking boundary
		template <typename IndiceType = int>
		inline T& at(const IndiceType v);

		//return m[v] without checking boundary
		template <typename IndiceType = int>
		inline T& operator[](const IndiceType v) { return m[v]; }

		template <typename IndiceType = int>
		inline const T& operator[](const IndiceType v)const { return m[v]; }

		//T&& operator
		union
		{
			struct
			{
				union { T x, r; };
				union { T y, g; };
			};
			T m[2];
		};

#define RTM_DEFINE_OPERATOR_SELF_OP_VEC2_AND_SCALAR(op) \
		constexpr inline Vec<T, 2, features>& operator op (const Vec<T, 2, features>& a) noexcept(noexcept(x op a.x))\
		{\
			x op a.x;\
			y op a.y;\
			return *this;\
		}\
		constexpr inline Vec<T, 2, features>& operator op (const T& v) noexcept(noexcept(x op v))\
		{\
			x op v;\
			y op v;\
			return *this;\
		}\

		RTM_DECLARE_OPERATORS_EQUAL_CALC(RTM_DEFINE_OPERATOR_SELF_OP_VEC2_AND_SCALAR);
#undef RTM_DEFINE_OPERATOR_SELF_OP_VEC2_AND_SCALAR
	};

	//define types
	typedef Vec<RtmGeneralType, 2>			Vec2;
	typedef Vec<float, 2>			Vec2f;
	typedef Vec<double, 2>			Vec2d;
	typedef Vec<long double, 2>			Vec2ld;
	typedef Vec<int, 2>			Vec2i;
	typedef Vec<unsigned int, 2>			Vec2ui;
	typedef Vec<short int, 2>			Vec2si;
	typedef Vec<unsigned short int, 2>			Vec2usi;
	typedef Vec<long int, 2>			Vec2li;
	typedef Vec<unsigned long int, 2>			Vec2uli;
	typedef Vec<long long, 2>			Vec2ll;
	typedef Vec<unsigned long long, 2>			Vec2ull;
	typedef Vec<char, 2>			Vec2c;
	typedef Vec<unsigned char, 2>			Vec2uc;
	typedef Vec<signed char, 2>			Vec2sc;
	typedef Vec<wchar_t, 2>			Vec2wc;

	//computing part
	//Vec2+Vec2
#define RTM_DEFINE_OPERATOR_VEC2_OP_VEC2(op) \
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const Vec<T, 2, features>& a, const Vec<T2, 2, features>& b) noexcept(noexcept(a.x op b.y))\
	{\
		return Vec<decltype(a.x op b.x), 2, features>(a.x op b.x, a.y op b.y);\
	}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC2_OP_VEC2);
#undef RTM_DEFINE_OPERATOR_VEC2_OP_VEC2

	//Vec2+scalar
#define RTM_DEFINE_OPERATOR_VEC2_OP_SCALAR(op) \
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const Vec<T, 2, features>& a, const T2& b) noexcept(noexcept(a.x op b))\
	{return Vec<decltype(a.x op b), 2, features>(a.x op b, a.y op b);}\
\
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const T2& b, const Vec<T, 2, features>& a) noexcept(noexcept(b op a.x))\
	{return Vec<decltype(b op a.x), 2, features>(b op a.x,b op a.y);}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC2_OP_SCALAR);
#undef RTM_DEFINE_OPERATOR_VEC2_OP_SCALAR

	template <typename T, typename T2, Feature features>
	constexpr auto dot(const Vec<T, 2, features>& a, const Vec<T2, 2, features>& b) noexcept(noexcept((a.m[0] * b.m[0])))
	{
		return a.x*b.x + a.y*b.y;
	}

	template <typename T, typename T2, Feature features>
	constexpr auto cross(const Vec<T, 2, features>& a, const Vec<T2, 3, features>& b) noexcept(noexcept((a.m[0] * b.m[0])))
	{
		return a.x*b.y - a.y*b.x;
	}

	template <typename T, Feature features>
	constexpr Vec<T, 2, features> pow(const Vec<T, 2, features>& c,const T ex) noexcept(noexcept(std::pow(c.m[0], 2.0)))
	{
		return { std::pow(c.x,ex),std::pow(c.y,ex) };
	}

	//-Vec2
	template<typename T, Feature features>
	constexpr inline Vec<T, 2, features> operator-(const Vec<T, 2, features>& a) noexcept(noexcept(-a.x))
	{
		return Vec<T, 2, features>(-a.x, -a.y, -a.z);
	}

	template<typename T, Feature features>
	inline Vec<T, 2, features>::Vec(const T& x, const T& y) noexcept
	{
		this->x = x;
		this->y = y;
	}

	template<typename T, Feature features>
	inline Vec<T, 2, features>::Vec(const Vec<T, 4, features>& xy) noexcept
	{
		this->x = xy.x;
		this->y = xy.y;
	}

	template<typename T, Feature features>
	inline Vec<T, 2, features>::Vec(const Vec<T, 3, features>& xy) noexcept
	{
		this->x = xy.x;
		this->y = xy.y;
	}

	template<typename T, Feature features>
	inline Vec<T, 2, features>::Vec(const T& all) noexcept
	{
		x = y = all;
	}

	template<typename T, Feature features>
	inline Vec<T, 2, features>::Vec(const Vec<T, 2, features>& va) noexcept
	{
		x = va.x;
		y = va.y;
	}
}