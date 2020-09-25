#pragma once
#include "Precompile.h"
#include "Enums.h"
namespace rtm
{
	template<typename T, int yLen, int xLen, Feature features>
	class Matrix;

	template <typename T,int vecLen,Feature features=Feature::none>
	class Vec
	{
	public:

		Vec()noexcept {};
		Vec(const Matrix<T, vecLen, 1, features>& a);
		Vec(std::initializer_list<T>&& t);
		Vec(const std::initializer_list<T>& t);
		Vec(const Vec<T, vecLen, features>& va);
		~Vec() {};
		//return m[v] with checking boundary
		template <typename IndiceType=int>
		inline T& at(const IndiceType v);

		//return m[v] without checking boundary
		template <typename IndiceType=int>
		constexpr inline T& operator[](const IndiceType v){return m[v];}

		template <typename IndiceType = int>
		inline const T& operator[](const IndiceType v)const { return m[v]; }

		T m[vecLen];
		
#define RTM_DEFINE_OPERATOR_SELF_OP_VEC_AND_SCALAR(op) \
		constexpr inline Vec<T, vecLen, features>& operator op (const Vec<T, vecLen, features>& a) noexcept(noexcept(m[0] op a.m[0]))\
		{\
			for (auto i = 0; i < vecLen; i++)\
			{\
				m[i] op a.m[i];\
			}\
			return *this;\
		}\
		constexpr inline Vec<T, vecLen, features>& operator op (const T& v) noexcept(noexcept(m[0] op v))\
		{\
			for (auto i = 0; i < vecLen; i++)\
			{\
				m[i] op v;\
			}\
			return *this;\
		}\

		RTM_DECLARE_OPERATORS_EQUAL_CALC(RTM_DEFINE_OPERATOR_SELF_OP_VEC_AND_SCALAR);
#undef RTM_DEFINE_OPERATOR_SELF_OP_VEC_AND_SCALAR
	};

	//define types

	template<int vecLen>
	using Vec_dt	=	Vec<Decimal,vecLen>;
	template<int vecLen>
	using Vecf		=	Vec<float,vecLen>;
	template<int vecLen>
	using Vecd		=	Vec<double,vecLen>;
	template<int vecLen>
	using Vecld		=	Vec<long double,vecLen>;
	template<int vecLen>
	using Veci		=	Vec<int,vecLen>;
	template<int vecLen>
	using Vecui		=	Vec<unsigned int,vecLen>;
	template<int vecLen>
	using Vecsi		=	Vec<short int,vecLen>;
	template<int vecLen>
	using Vecusi	=	Vec<unsigned short int, vecLen>;
	template<int vecLen>
	using Vecli		=	Vec<long int,vecLen>;
	template<int vecLen>
	using Veculi	=	Vec<unsigned long int,vecLen>;
	template<int vecLen>
	using Vecll		=	Vec<long long,vecLen>;
	template<int vecLen>
	using Vecull	=	Vec<unsigned long long, vecLen>;
	template<int vecLen>
	using Vecc		=	Vec<char,vecLen>;
	template<int vecLen>
	using Vecuc		=	Vec<unsigned char,vecLen>;
	template<int vecLen>
	using Vecsc		=	Vec<signed char,vecLen>;
	template<int vecLen>
	using Vecwc		=	Vec<wchar_t,vecLen>;


	//define functions
	template <typename T, int vecLen, Feature features>
	std::ostream& operator<< (std::ostream& output, Vec<T, vecLen, features>&& c);

	template <typename T, int vecLen, Feature features>
	std::ostream& operator<< (std::ostream& output, Vec<T, vecLen, features>& c);

	template <typename T, int vecLen, Feature features>
	constexpr T length(const Vec<T, vecLen, features>& c) noexcept(noexcept(std::sqrt(c.m[0] * c.m[0])));

	template <typename T, typename T2, int vecLen, Feature features>
	constexpr auto dot(const Vec<T, vecLen, features>& a, const Vec<T2, vecLen, features>& b) noexcept(noexcept((a.m[0] * b.m[0])));

	template <typename T, int vecLen, Feature features>
	constexpr Vec<T, vecLen, features> normalize(const Vec<T, vecLen, features>& c) noexcept(noexcept(c / length<T, vecLen, features>(c)));

	template <typename T, int vecLen, Feature features>
	constexpr Vec<T, vecLen, features> pow(const Vec<T, vecLen, features>& c, const T ex) noexcept(noexcept(std::pow(c.m[0], 2.0)));

	//computing part
	//Vec+Vec
#define RTM_DEFINE_OPERATOR_VEC_OP_VEC(op) \
	template<typename T, typename T2, int vecLen, Feature features>\
	constexpr inline auto operator op (const Vec<T, vecLen, features>& a, const Vec<T2, vecLen, features>& b) noexcept(noexcept(a.m[0] op b.m[0]))\
	{\
		Vec<decltype(a.m[0] + b.m[0]), vecLen, features> c;\
		for (auto i = 0; i < vecLen; i++)\
		{\
			c[i] = a.m[i] op a.m[i];\
		}\
		return std::move(c);\
	}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC_OP_VEC);
#undef RTM_DEFINE_OPERATOR_VEC_OP_VEC

	//Vec+scalar
	//scalar+Vec
#define RTM_DEFINE_OPERATOR_VEC_OP_SCALAR(op) \
	template<typename T, typename T2, int vecLen, Feature features>\
	constexpr inline auto operator op (const Vec<T, vecLen, features>& a, const T2& b) noexcept(noexcept(a.m[0] op b))\
	{\
		Vec<decltype(a.m[0] op b), vecLen, features> c;\
		for (auto i = 0; i < vecLen; i++)\
		{\
			c[i] = a.m[i] op b;\
		}\
		return std::move(c);\
	}\
\
	template<typename T, typename T2, int vecLen, Feature features>\
	constexpr inline auto operator op (const T2& b, const Vec<T, vecLen, features>& a) noexcept(noexcept(b op a.m[0]))\
	{\
		Vec<decltype(b op a.m[0]), vecLen, features> c;\
		for (auto i = 0; i < vecLen; i++)\
		{\
			c[i] = b op a.m[i];\
		}\
		return std::move(c);\
	}\

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_VEC_OP_SCALAR);
#undef RTM_DEFINE_OPERATOR_VEC_OP_SCALAR

	//-Vec
	template<typename T, int vecLen, Feature features>
	constexpr inline Vec<T, vecLen, features> operator-(const Vec<T, 3, features>& a) noexcept(noexcept(-a.x))
	{
		Vec<T, vecLen, features> c;
		for (auto i = 0; i < vecLen; i++)
		{
			c[i] = -a.m[i]; 
		}
		return c;
	}


	//realize
	template <typename T, int vecLen, Feature features>
	std::ostream& operator<< (std::ostream& output, Vec<T, vecLen, features>& c)
	{
		return output << std::move(c);
	}

	template<typename T, int vecLen, Feature features>
	constexpr T length(const Vec<T, vecLen, features>& c) noexcept(noexcept(std::sqrt(c.m[0] * c.m[0])))
	{
		return static_cast<T>(std::sqrt(dot(c, c)));
	}

	template<typename T, typename T2, int vecLen, Feature features>
	constexpr auto dot(const Vec<T, vecLen, features>& a, const Vec<T2, vecLen, features>& b) noexcept(noexcept((a.m[0] * b.m[0])))
	{
		auto result = a.m[0] * b.m[0];
		for (auto i = 1; i < vecLen; ++i)
		{
			result += a.m[i] * b.m[i];
		}
		return result;
	}

	template<typename T, int vecLen, Feature features>
	constexpr Vec<T, vecLen, features> normalize(const Vec<T, vecLen, features>& c) noexcept(noexcept(c / length<T, vecLen, features>(c)))
	{
		return c / length(c);
	}

	template<typename T, int vecLen, Feature features>
	constexpr Vec<T, vecLen, features> pow(const Vec<T, vecLen, features>& c, const T ex) noexcept(noexcept(std::pow(c.m[0], 2.0)))
	{
		Vec<T, vecLen, features> result = c;
		for (auto i = 0; i < vecLen; ++i)
		{
			result.m[i] = std::pow(c.m[i], ex);
		}
		return result;
	}

	template <typename T, int vecLen, Feature features>
	std::ostream& operator<< (std::ostream& output, Vec<T, vecLen, features>&& c)
	{
		output << "[ ";
		constexpr int vecLenm1 = vecLen - 1;
		for (auto i = 0; i < vecLenm1; ++i)
		{
			output << c[i] << ",\t ";
		}
		output << c[vecLenm1] << " ]";
		return output;
	}

	template<typename T, int vecLen, Feature features>
	inline Vec<T, vecLen, features>::Vec(const Matrix<T, vecLen, 1, features>& a)
	{
		memcpy_s(&m, sizeof(T)*vecLen, &a.m, sizeof(T)*vecLen);
	}

	template<typename T, int vecLen, Feature features>
	inline Vec<T, vecLen, features>::Vec(std::initializer_list<T>&& t)
	{
		int i = 0;
		for (const T& v:t)
		{
			m[i] = v;
			++i;
		}
	}
	
	template<typename T, int vecLen, Feature features>
	inline Vec<T, vecLen, features>::Vec(const std::initializer_list<T>& t)
	{
		int i = 0;
		for (const T& v : t)
		{
			m[i] = v;
			++i;
		}
	}

	template<typename T, int vecLen, Feature features>
	inline Vec<T, vecLen, features>::Vec(const Vec<T, vecLen, features>& va)
	{
		memcpy_s(&m, sizeof(T)*vecLen, &va.m, sizeof(T)*vecLen);
	}

	template<typename T, int vecLen, Feature features>
	template<typename IndiceType>
	inline T & Vec<T, vecLen, features>::at(const IndiceType v)
	{
		static_assert(v >= 0 && v < vecLen, "Out of boundary");
#ifdef _DEBUG
		assert(v >= 0 && v < vecLen);
#endif // _DEBUG
		return m[v];
	}

	
}