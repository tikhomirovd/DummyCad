#pragma once

#if defined WIN32
# if defined CURVE_EXPORTS
#   define Curve_EXPORT __declspec( dllexport )
# else
#   define Curve_EXPORT __declspec( dllimport )
# endif
#else
# define Curve_EXPORT
#endif
