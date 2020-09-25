#pragma once
#include "Precompile.h"
#include "Vector.h"
namespace rtm
{
	template <typename T, Feature features>
	class Vec<T, 4, features>
	{
	public:

		Vec()noexcept {};
		Vec(const Matrix<T, 4, 1, features>& a);
		Vec(const Vec<T, 4, features>& va)noexcept;
		Vec(const T& x, const T& y, const T& z, const T& w)noexcept;
		Vec(const Vec<T, 3, features>& xyz, const T& w)noexcept;
		Vec(const T& x, const Vec<T, 3, features>& yzw)noexcept;
		Vec(const T& x, const T& y, const Vec<T, 2, features>& zw)noexcept;
		Vec(const T& x, const Vec<T, 2, features>& yz, const T& w)noexcept;
		Vec(const Vec<T, 2, features>& xy, const T& z, const T& w)noexcept;
		Vec(const Vec<T, 2, features>& xy, const Vec<T, 2, features>& zw)noexcept;
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
				union { T z, b; };
				union { T w, a; };
			};
			T m[4];
		};

#define RTM_DEFINE_OPERATOR_SELF_OP_VEC4_AND_SCALAR(op) \
		constexpr inline Vec<T, 4, features>& operator op (const Vec<T, 4, features>& a) noexcept(noexcept(x op a.x))\
		{\
			x op a.x;\
			y op a.y;\
			z op a.z;\
			w op a.w;\
			return *this;\
		}\
		constexpr inline Vec<T, 4, features>& operator op (const T& v) noexcept(noexcept(x op v))\
		{\
			x op v;\
			y op v;\
			z op v;\
			w op v;\
			return *this;\
		}\

		RTM_DECLARE_OPERATORS_EQUAL_CALC(RTM_DEFINE_OPERATOR_SELF_OP_VEC4_AND_SCALAR);
#undef RTM_DEFINE_OPERATOR_SELF_OP_VEC4_AND_SCALAR
	};
	//define types
	typedef Vec<Decimal,		4>			Vec4;
	typedef Vec<float,				4>			Vec4f;
	typedef Vec<double,				4>			Vec4d;
	typedef Vec<long double,		4>			Vec4ld;
	typedef Vec<int,				4>			Vec4i;
	typedef Vec<unsigned int,		4>			Vec4ui;
	typedef Vec<short int,			4>			Vec4si;
	typedef Vec<unsigned short int, 4>			Vec4usi;
	typedef Vec<long int,			4>			Vec4li;
	typedef Vec<unsigned long int,	4>			Vec4uli;
	typedef Vec<long long,			4>			Vec4ll;
	typedef Vec<unsigned long long, 4>			Vec4ull;
	typedef Vec<char,				4>			Vec4c;
	typedef Vec<unsigned char,		4>			Vec4uc;
	typedef Vec<signed char,		4>			Vec4sc;
	typedef Vec<wchar_t,			4>			Vec4wc;

	//computing part
	//Vec4+Vec4
#define RTM_DEFINE_OPERATOR_VEC4_OP_VEC4(op) \
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const Vec<T, 4, features>& a, const Vec<T2, 4, features>& b) noexcept(noexcept(a.x op b.y))\
	{\
		return Vec<decltype(a.x op b.x), 4, features>(a.x op b.x, a.y op b.y, a.z op b.z, a.w op b.w);\
	}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC4_OP_VEC4);
#undef RTM_DEFINE_OPERATOR_VEC4_OP_VEC4

	//Vec4+scalar
#define RTM_DEFINE_OPERATOR_VEC4_OP_SCALAR(op) \
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const Vec<T, 4, features>& a, const T2& b) noexcept(noexcept(a.x op b))\
	{return Vec<decltype(a.x op b), 4, features>(a.x op b, a.y op b, a.z op b, a.w op b);}\
\
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const T2& b, const Vec<T, 4, features>& a) noexcept(noexcept(b op a.x))\
	{return Vec<decltype(b op a.x), 4, features>(b op a.x, b op a.y, b op a.z, b op a.w);}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC4_OP_SCALAR);
#undef RTM_DEFINE_OPERATOR_VEC4_OP_SCALAR

	template <typename T, typename T2, Feature features>
	constexpr auto dot(const Vec<T, 4, features>& a, const Vec<T2, 4, features>& b) noexcept(noexcept((a.m[0] * b.m[0])))
	{
		return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
	}

	template <typename T, Feature features>
	constexpr Vec<T, 4, features> pow(const Vec<T, 4, features>& c, const T ex) noexcept(noexcept(std::pow(c.m[0], 2.0)))
	{
		return { std::pow(c.x,ex),std::pow(c.y,ex),std::pow(c.z,ex),std::pow(c.w,ex) };
	}

	//-Vec4
	template<typename T, Feature features>
	constexpr inline Vec<T, 4, features> operator-(const Vec<T, 4, features>& a) noexcept(noexcept(-a.x))
	{
		return Vec<T, 4, features>(-a.x, -a.y, -a.z, -a.w);
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const T& x, const T& y, const T& z, const T& w) noexcept
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const Vec<T, 3, features>& xyz, const T & w) noexcept
	{
		this->x = xyz.x;
		this->y = xyz.y;
		this->z = xyz.z;
		this->w = w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const T & x, const Vec<T, 3, features>& yzw) noexcept
	{
		this->x = x;
		this->y = yzw.y;
		this->z = yzw.z;
		this->w = yzw.w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const T & x, const T & y, const Vec<T, 2, features>& zw) noexcept
	{
		this->x = x;
		this->y = y;
		this->z = zw.z;
		this->w = zw.w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const T & x, const Vec<T, 2, features>& yz, const T & w) noexcept
	{
		this->x = x;
		this->y = yz.y;
		this->z = yz.z;
		this->w = w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const Vec<T, 2, features>& xy, const T & z, const T & w) noexcept
	{
		this->x = xy.x;
		this->y = xy.y;
		this->z = z;
		this->w = w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const Vec<T, 2, features>& xy, const Vec<T, 2, features>& zw) noexcept
	{
		this->x = xy.x;
		this->y = xy.y;
		this->z = zw.z;
		this->w = zw.w;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const T& all) noexcept
	{
		x = y = z = w = all;
	}

	template<typename T, Feature features>
	inline Vec<T, 4, features>::Vec(const Vec<T, 4, features>& va) noexcept
	{
		x = va.x;
		y = va.y;
		z = va.z;
		w = va.w;
	}
}