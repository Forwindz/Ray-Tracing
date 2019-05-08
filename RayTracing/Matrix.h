#pragma once
#include "Precompile.h"
#include "Enums.h"
#include "Vector.h"
#include "globalTools.h"
namespace rtm
{
	template <typename T, int vecLen, Feature features>
	class Vector;

	template<typename T, int yLen, int xLen, Feature features = Feature::none>
	class Matrix
	{
	public:

		Matrix() {};
		Matrix(std::initializer_list<T>&& t);
		Matrix(std::initializer_list<std::initializer_list<T>>&& t);

		Matrix(const Matrix<T, yLen, xLen, features>& v);
		Matrix(Matrix<T, yLen, xLen, features>&& v);

		template<typename IndiceType>
		Vec<T, xLen, features>& operator[](const IndiceType ind);
		template<typename IndiceType>
		const Vec<T, xLen, features>& operator[](const IndiceType ind)const;
		template<typename IndiceType>
		Vec<T, yLen, features> col(const IndiceType ind);
		template<typename IndiceType>
		Vec<T, xLen, features> row(const IndiceType ind);
		//with check
		template<typename IndiceType>
		T& at(const IndiceType x, const IndiceType y);

		Matrix<T, xLen, yLen, features> t();

		constexpr inline int cols() noexcept { return xLen; };
		constexpr inline int rows() noexcept { return yLen; };
		constexpr inline int elements() noexcept { return yLen * xLen; };

#define RTM_DEFINE_OPERATOR_SELF_MAT_OP_SCALAR(op)\
		constexpr inline Matrix<T, yLen, xLen, features>& operator op (const T& b)\
		{\
			const T* selfMaxPtr = reinterpret_cast<T*>(&m) + elements();\
			for (T* selfElementPtr = reinterpret_cast<T*>(&m); selfElementPtr < selfMaxPtr; ++selfElementPtr) \
				(*selfElementPtr) op b;\
			return *this;\
		}

		RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_SELF_MAT_OP_SCALAR);
#undef RTM_DEFINE_OPERATOR_SELF_MAT_OP_SCALAR

#define RTM_DEFINE_OPERATOR_SELF_MAT_OP_MAT(op)\
		inline auto operator op (const Matrix<T, yLen, xLen, features>& b)\
		{\
			const T* selfMaxPtr = reinterpret_cast<T*>(&m) + elements(); \
			T* bElementPtr = reinterpret_cast<T*>(&b);\
			T* selfElementPtr = reinterpret_cast<T*>(&m);\
			for (;selfElementPtr < selfMaxPtr; ++selfElementPtr, ++bElementPtr)\
				(*selfElementPtr) op (*bElementPtr);\
			return *this;\
		}\

		RTM_DEFINE_OPERATOR_SELF_MAT_OP_MAT(+=);
		RTM_DEFINE_OPERATOR_SELF_MAT_OP_MAT(-=);
#undef RTM_DEFINE_OPERATOR_SELF_MAT_OP_MAT
			
		/*
			  xLen
		Vec ---------
		Vec --------- yLen
		Vec ---------
		*/
		Vec<T, xLen, features> m[yLen];
	};

	typedef Matrix<RtmGeneralType, 4, 4> Mat4x4;
	typedef Matrix<RtmGeneralType, 4, 4> Mat4;
	typedef Matrix<RtmGeneralType, 4, 3> Mat4x3;
	typedef Matrix<RtmGeneralType, 3, 4> Mat3x4;
	typedef Matrix<RtmGeneralType, 4, 2> Mat4x2;
	typedef Matrix<RtmGeneralType, 2, 4> Mat2x4;
	typedef Matrix<RtmGeneralType, 3, 3> Mat3x3;
	typedef Matrix<RtmGeneralType, 3, 3> Mat3;
	typedef Matrix<RtmGeneralType, 3, 2> Mat3x2;
	typedef Matrix<RtmGeneralType, 2, 3> Mat2x3;
	typedef Matrix<RtmGeneralType, 2, 2> Mat2x2;
	typedef Matrix<RtmGeneralType, 2, 2> Mat2;

	template<typename T, int yLen, int xLen, Feature features>
	std::ostream& operator<< (std::ostream& output, Matrix<T, yLen, xLen, features>& c)
	{
		return output << std::move(c);
	}

	template<typename T, int yLen, int xLen, Feature features>
	std::ostream& operator<< (std::ostream& output, Matrix<T, yLen, xLen, features>&& c)
	{
		output << "Matrix(" << yLen << ", " << xLen << ")\n" << "[\n";
		for (auto i = 0; i < yLen - 1; ++i)
		{
			output << c[i] << ",\n";
		}
		output << c[yLen - 1] << "\n]\n";
		return output;
	}

	template<typename T, int yLen, int xLen, Feature features>
	template<typename IndiceType>
	inline Vec<T, xLen, features>& Matrix<T, yLen, xLen, features>::operator[](const IndiceType ind)
	{
		return m[ind];
	}

	template<typename T, int yLen, int xLen, Feature features>
	template<typename IndiceType>
	inline const Vec<T, xLen, features>& Matrix<T, yLen, xLen, features>::operator[](const IndiceType ind) const
	{
		return m[ind];
	}

	template<typename T, int yLen, int xLen, Feature features>
	template<typename IndiceType>
	inline Vec<T, yLen, features> Matrix<T, yLen, xLen, features>::col(const IndiceType ind)
	{
		Vec<T, yLen, features> a;
		for (auto i = 0; i < yLen; ++i)
		{
			a[ind] = m[i][ind];
		}
		return a;
	}

	template<typename T, int yLen, int xLen, Feature features>
	template<typename IndiceType>
	inline Vec<T, xLen, features> Matrix<T, yLen, xLen, features>::row(const IndiceType ind)
	{
		return m[ind];
	}

	template<typename T, int yLen, int xLen, Feature features>
	template<typename IndiceType>
	inline T & Matrix<T, yLen, xLen, features>::at(const IndiceType x, const IndiceType y)
	{
		runtimeAssert(x >= 0 && y >= 0 && x < xLen && y < yLen, "Wrong Index for this Matrix");
		return m[y][x];
	}

	/*
		xLen	    zLen		zLen
		ooo			oooo		oooo	
		ooo yLen *	oooo xLen =	oooo yLen
					oooo

		TODO: better algorithm
	*/
	template<typename T, typename T2, int yLen, int xLen, int zLen, Feature features>
	inline auto operator*(const Matrix<T, yLen, xLen, features>& a, const Matrix<T2, xLen, zLen, features>& b)
	{
		Matrix<decltype(a[0][0] * b[0][0]), yLen, zLen, features> result;
		for (auto i = 0; i < yLen; ++i)
		{
			for (auto j = 0; j < zLen; ++j)
			{
				result[i][j] = a[i][0] * b[0][j];
				for (auto k = 1; k < xLen; ++k)
					result[i][j] += a[i][k] * b[k][j];
			}
		}
		return result;
	}

	//	Matrix +-*/ Scalar
#define RTM_DEFINE_OPERATOR_MAT_OP_SCALAR(op)\
	template<typename T, typename T2, int yLen, int xLen, int zLen, Feature features>  \
	inline auto operator op (const Matrix<T, yLen, xLen, features>& a, const T2& b)	   \
	{																				   \
		Matrix<decltype(a[0][0] op b), yLen, xLen, features> result;				   \
		const auto* aMaxPtr = &a + a.elements();									   \
		auto* aElementPtr = &a;														   \
		auto* resultElementPtr = &result;											   \
		for (; aElementPtr < aMaxPtr; ++aElementPtr, ++resultElementPtr)			   \
		{																			   \
			(*resultElementPtr) = (*aElementPtr) op b;								   \
		}																			   \
		return result;																   \
	}																				   \
	template<typename T, typename T2, int yLen, int xLen, int zLen, Feature features>  \
	inline auto operator op (const T2& b, const Matrix<T, yLen, xLen, features>& a)	   \
	{																				   \
		Matrix<decltype(b op a[0][0]), yLen, xLen, features> result;				   \
		const auto* aMaxPtr = &a + a.elements();									   \
		auto* aElementPtr = &a;														   \
		auto* resultElementPtr = &result;											   \
		for (; aElementPtr < aMaxPtr; ++aElementPtr, ++resultElementPtr)			   \
		{																			   \
			(*resultElementPtr) = b op (*aElementPtr);								   \
		}																			   \
		return result;																   \
	}																				   \

	RTM_DECLARE_OPERATORS_TWO_CALC(RTM_DEFINE_OPERATOR_MAT_OP_SCALAR);
#undef RTM_DEFINE_OPERATOR_MAT_OP_SCALAR

	//Mat +- Mat
#define RTM_DEFINE_OPERATOR_MAT_OP_MAT(op)\
	template<typename T, typename T2, int yLen, int xLen, int zLen, Feature features>\
	inline auto operator op (const Matrix<T, yLen, xLen, features>& a, const Matrix<T2, yLen, xLen, features>& b)\
	{\
		Matrix<decltype(a[0][0] op b[0][0]), yLen, xLen, features> result;\
		const T* aMaxPtr = reinterpret_cast<T*>(&a) + a.elements(); \
		T* aElementPtr = reinterpret_cast<T*>(&a);\
		T* bElementPtr = reinterpret_cast<T*>(&b);\
		T* resultElementPtr = reinterpret_cast<T*>(&result);\
		for (;aElementPtr < aMaxPtr; ++aElementPtr, ++bElementPtr, ++resultElementPtr)\
			(*resultElementPtr) = (*aElementPtr) op (*bElementPtr);\
		return *this;\
	}\

	RTM_DEFINE_OPERATOR_MAT_OP_MAT(+);
	RTM_DEFINE_OPERATOR_MAT_OP_MAT(-);
#undef RTM_DEFINE_OPERATOR_MAT_OP_MAT

	//Mat * Mat, compute by each element
	template<typename T, typename T2, int yLen, int xLen, int zLen, Feature features>
	inline auto mul(const Matrix<T, yLen, xLen, features>& a, const Matrix<T2, yLen, xLen, features>& b)
	{
		Matrix<decltype(a[0][0] * b[0][0]), yLen, xLen, features> result;
		const T* aMaxPtr = reinterpret_cast<T*>(&a) + a.elements(); 
		T* aElementPtr = reinterpret_cast<T*>(&a);
		T* bElementPtr = reinterpret_cast<T*>(&b);
		T* resultElementPtr = reinterpret_cast<T*>(&result);
		for (;aElementPtr < aMaxPtr; ++aElementPtr, ++bElementPtr, ++resultElementPtr)
			(*resultElementPtr) = (*aElementPtr) * (*bElementPtr);
		return *this;
	}

	//Mat / Mat, compute by each element
	template<typename T, typename T2, int yLen, int xLen, int zLen, Feature features>
	inline auto div(const Matrix<T, yLen, xLen, features>& a, const Matrix<T2, yLen, xLen, features>& b)
	{
		Matrix<decltype(a[0][0] * b[0][0]), yLen, xLen, features> result;
		const T* aMaxPtr = reinterpret_cast<T*>(&a) + a.elements();
		T* aElementPtr = reinterpret_cast<T*>(&a);
		T* bElementPtr = reinterpret_cast<T*>(&b);
		T* resultElementPtr = reinterpret_cast<T*>(&result);
		for (;aElementPtr < aMaxPtr; ++aElementPtr, ++bElementPtr, ++resultElementPtr)
			(*resultElementPtr) = (*aElementPtr) / (*bElementPtr);
		return *this;
	}

	template<typename T, int yLen, int xLen, Feature features>
	inline Matrix<T, yLen, xLen, features>::Matrix(std::initializer_list<T>&& t)
	{
		const T* selfMaxPtr = reinterpret_cast<T*>(&m) + elements(); 
		T* selfElementPtr = reinterpret_cast<T*>(&m);
		auto d = t.begin();
		for (; d != t.end(); ++selfElementPtr, ++d) 
			(*selfElementPtr) = *d;
	}

	template<typename T, int yLen, int xLen, Feature features>
	inline Matrix<T, yLen, xLen, features>::Matrix(std::initializer_list<std::initializer_list<T>>&& t)
	{
		const T* selfMaxPtr = reinterpret_cast<T*>(&m) + elements();
		T* selfElementPtr = reinterpret_cast<T*>(&m);
		for (auto& t2 : t)
		{
			auto d = t2.begin();
			for (; d != t2.end(); ++selfElementPtr, ++d)
				(*selfElementPtr) = *d;
		}
	}

	template<typename T, int yLen, int xLen, Feature features>
	inline Matrix<T, yLen, xLen, features>::Matrix(const Matrix<T, yLen, xLen, features>& v)
	{
		memcpy_s(this, sizeof(Matrix<T, yLen, xLen, features>), &v, sizeof(Matrix<T, yLen, xLen, features>));
	}

	template<typename T, int yLen, int xLen, Feature features>
	inline Matrix<T, yLen, xLen, features>::Matrix(Matrix<T, yLen, xLen, features>&& v)
	{
		memcpy_s(this, sizeof(Matrix<T, yLen, xLen, features>), &v, sizeof(Matrix<T, yLen, xLen, features>));
	}

	template<typename T, int yLen, int xLen, Feature features>
	inline Matrix<T, xLen, yLen, features> Matrix<T, yLen, xLen, features>::t()
	{
		Matrix<T, xLen, yLen, features> a;
		const auto len = elements();
		for (auto i = 0; i < yLen; ++i)
		{
			for (auto j = 0; j < xLen; ++j)
			{
				a[i][j] = m[j][i];
			}
		}
		return a;
	}

}