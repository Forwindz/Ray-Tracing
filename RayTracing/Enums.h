#pragma once
#include "Precompile.h"
namespace rtm
{

	enum Feature
	{
		none = 0,
		features = 1
	};

//types
#ifdef RTM_LOW_PRECISION
	//TODO: half float need to be realized by hand
	//typedef RtmGeneralType short float
#else
	#ifdef RTM_HIGH_PRECISION
		typedef double RtmGeneralType;
	#else 
		#ifdef RTM_EXTREME_HIGH_PRECISION
			typedef long double RtmGeneralType;
		#else
			typedef float RtmGeneralType;
		#endif 
	#endif
#endif


#define RTM_DECLARE_OPERATORS_EQUAL_CALC(macroName);\
macroName(+=);\
macroName(-=);\
macroName(*=);\
macroName(/=);\

#define RTM_DECLARE_OPERATORS_EQUAL_BOOL(macroName);\
macroName(<<=);\
macroName(>>=);\
macroName(&=);\
macroName(&&=);\
macroName(|=);\
macroName(||=);\
macroName(^=);\

#define RTM_DECLARE_OPERATORS_EQUAL(macroName);\
RTM_DECLARE_OPERATORS_EQUAL_CALC(macroName);\
RTM_DECLARE_OPERATORS_EQUAL_BOOL(macroName);\

#define RTM_DECLARE_OPERATORS_TWO_CALC(macroName);\
macroName(+);\
macroName(-);\
macroName(*);\
macroName(/);\

#define RTM_DECLARE_OPERATORS_TWO_BOOL(macroName);\
macroName(<<);\
macroName(>>);\
macroName(&);\
macroName(&&);\
macroName(|);\
macroName(||);\
macroName(^);\

#define RTM_DECLARE_OPERATIONS_TWO(macroName);\
RTM_DECLARE_OPERATORS_TWO_CALC(macroName);\
RTM_DECLARE_OPERATORS_TWO_BOOL(macroName);\

}