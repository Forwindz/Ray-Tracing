#pragma once
#include "Precompile.h"
#include "Vector.h"
namespace rtm
{
	template <typename T, Feature features>
	class Vec<T, 3, features>
	{
	public:

		Vec()noexcept {};
		Vec(const Matrix<T, 3, 1, features>& a);
		Vec(const Vec<T, 3, features>& va)noexcept;
		Vec(const Vec<T, 2, features>& xy, const T& z)noexcept;
		Vec(const T& x, const Vec<T, 2, features>& yz)noexcept;
		explicit Vec(const Vec<T, 4, features>& xyz)noexcept;
		Vec(const T& x, const T& y, const T& z)noexcept;
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
			};
			T m[3];
		};

#define RTM_DEFINE_OPERATOR_SELF_OP_VEC3_AND_SCALAR(op) \
		constexpr inline Vec<T, 3, features>& operator op (const Vec<T, 3, features>& a) noexcept(noexcept(x op a.x))\
		{\
			x op a.x;\
			y op a.y;\
			z op a.z;\
			return *this;\
		}\
		constexpr inline Vec<T, 3, features>& operator op (const T& v) noexcept(noexcept(x op v))\
		{\
			x op v;\
			y op v;\
			z op v;\
			return *this;\
		}\

		RTM_DECLARE_OPERATORS_EQUAL_CALC(RTM_DEFINE_OPERATOR_SELF_OP_VEC3_AND_SCALAR);
#undef RTM_DEFINE_OPERATOR_SELF_OP_VEC3_AND_SCALAR
	};

	//define types
	typedef Vec<RtmGeneralType,		3>			Vec3;
	typedef Vec<float,				3>			Vec3f;
	typedef Vec<double,				3>			Vec3d;
	typedef Vec<long double,		3>			Vec3ld;
	typedef Vec<int,				3>			Vec3i;
	typedef Vec<unsigned int,		3>			Vec3ui;
	typedef Vec<short int,			3>			Vec3si;
	typedef Vec<unsigned short int, 3>			Vec3usi;
	typedef Vec<long int,			3>			Vec3li;
	typedef Vec<unsigned long int,	3>			Vec3uli;
	typedef Vec<long long,			3>			Vec3ll;
	typedef Vec<unsigned long long, 3>			Vec3ull;
	typedef Vec<char,				3>			Vec3c;
	typedef Vec<unsigned char,		3>			Vec3uc;
	typedef Vec<signed char,		3>			Vec3sc;
	typedef Vec<wchar_t,			3>			Vec3wc;

	//computing part
	//Vec3+Vec3
#define RTM_DEFINE_OPERATOR_VEC3_OP_VEC3(op) \
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const Vec<T, 3, features>& a, const Vec<T2, 3, features>& b) noexcept(noexcept(a.x op b.y))\
	{\
		return Vec<decltype(a.x op b.x), 3, features>(a.x op b.x, a.y op b.y, a.z op b.z);\
	}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC3_OP_VEC3);
#undef RTM_DEFINE_OPERATOR_VEC3_OP_VEC3

	//Vec3+scalar
#define RTM_DEFINE_OPERATOR_VEC3_OP_SCALAR(op) \
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const Vec<T, 3, features>& a, const T2& b) noexcept(noexcept(a.x op b))\
	{return Vec<decltype(a.x op b), 3, features>(a.x op b, a.y op b, a.z op b);}\
\
	template<typename T, typename T2, Feature features>\
	constexpr inline auto operator op (const T2& b, const Vec<T, 3, features>& a) noexcept(noexcept(b op a.x))\
	{return Vec<decltype(b op a.x), 3, features>(b op a.x,b op a.y,b op a.z);}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC3_OP_SCALAR);
#undef RTM_DEFINE_OPERATOR_VEC3_OP_SCALAR

	template <typename T, typename T2, Feature features>
	constexpr auto dot(const Vec<T, 3, features>& a, const Vec<T2, 3, features>& b) noexcept(noexcept((a.m[0] * b.m[0])))
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	template <typename T, typename T2, Feature features>
	constexpr auto cross(const Vec<T, 3, features>& a, const Vec<T2, 3, features>& b) noexcept(noexcept((a.m[0] * b.m[0])))
	{
		return Vec<decltype(a.x*b.x), 3, features>(
			a.y*b.z - a.z*b.y,
			a.z*b.x - a.x*b.z,
			a.x*b.y - a.y*b.x
			);
	}

	template <typename T, Feature features>
	constexpr Vec<T, 3, features> pow(const Vec<T, 3, features>& c, const T ex) noexcept(noexcept(std::pow(c.m[0],2.0)))
	{
		return { std::pow(c.x,ex),std::pow(c.y,ex),std::pow(c.z,ex) };
	}

	//https://blog.csdn.net/zsq306650083/article/details/8773996
	template <typename T, Feature features>
	constexpr auto rotate(const Vec<T, 3, features>& a, const Vec<T, 3, features>& axis, const T rad) noexcept(noexcept((a[0] * axis[0] + std::cos(rad))))
	{
		const T c = std::cos(rad);
		const T s = std::sin(rad);
		const T c1 = 1 - c;
		const T xy = axis.x*axis.y;
		const T yz = axis.z*axis.y;
		const T xz = axis.z*axis.x;
		return Vec<T, 3, features>
			(
				(axis.x*axis.x*c1 + c)*a.x +
				(xy*c1 + axis.z*s)*a.y + 
				(xz*c1 - axis.y*s)*a.z,

				(xy*c1 - axis.z*s)*a.x +
				(axis.y*axis.y*c1 + c)*a.y +
				(yz*c1 + axis.x*s)*a.z,

				(xz*c1 + axis.y*s)*a.x +
				(yz*c1 - axis.x*s)*a.y +
				(axis.z*axis.z*c1 + c)*a.z
			);

	}

	//-Vec3
	template<typename T, Feature features>
		constexpr inline Vec<T, 3, features> operator-(const Vec<T, 3, features>& a) noexcept(noexcept(-a.x))
	{
		return Vec<T, 3, features>(-a.x, -a.y, -a.z); 
	}

	template<typename T, Feature features>
	inline Vec<T, 3, features>::Vec(const T& x, const T& y, const T& z) noexcept
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	template<typename T, Feature features>
	inline Vec<T, 3, features>::Vec(const Vec<T, 4, features>& xyz) noexcept
	{
		this->x = xyz.x;
		this->y = xyz.y;
		this->z = xyz.z;
	}

	template<typename T, Feature features>
	inline Vec<T, 3, features>::Vec(const Vec<T, 2, features>& xy, const T& z) noexcept
	{
		this->x = xy.x;
		this->y = xy.y;
		this->z = z;
	}

	template<typename T, Feature features>
	inline Vec<T, 3, features>::Vec(const T& x, const Vec<T, 2, features>& yz) noexcept
	{
		this->x = x;
		this->y = yz.y;
		this->z = yz.z;
	}

	template<typename T, Feature features>
	inline Vec<T, 3, features>::Vec(const T& all) noexcept
	{
		x = y = z = all;
	}

	template<typename T, Feature features>
	inline Vec<T, 3, features>::Vec(const Vec<T, 3, features>& va) noexcept
	{
		x = va.x;
		y = va.y;
		z = va.z;
	}
}