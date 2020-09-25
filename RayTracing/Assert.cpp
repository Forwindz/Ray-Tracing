#include "Precompile.h"
#include "Assert.h"

void runtimeAssert(const bool condition, const std::string & errorInfo)
{
#ifdef _DEBUG
	if (!condition)
	{
		std::cout << "ERROR: " << errorInfo << "\n";
		throw std::runtime_error(errorInfo.c_str());
	}
#endif
}
