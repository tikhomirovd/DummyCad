#pragma once

#if defined WIN32
# if defined EQUATION_EXPORTS
#   define Equation_EXPORT __declspec( dllexport )
# else
#   define Equation_EXPORT __declspec( dllimport )
# endif
#else
# define Equation_EXPORT
#endif
