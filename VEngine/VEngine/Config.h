#pragma once

#ifdef  V_PLATFORM_WINDOWS
# ifdef V_BUILD_DLL
#  define V_API __declspec(dllexport)
# else
#  define V_API __declspec(dllimport)
# endif
#else
# error "Platform currently not supported"
#endif