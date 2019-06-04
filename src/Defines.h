#pragma once

#if defined WIN32
# if defined INTERSECTION_EXPORTS
#   define Intersection_EXPORT __declspec( dllexport )
# else
#   define Intersection_EXPORT __declspec( dllimport )
# endif
#else
# define Intersection_EXPORT
#endif
