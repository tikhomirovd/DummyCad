#pragma once

#ifdef Intersection_EXPORTS
  #define Intersection_EXPORT __declspec(dllexport)
#else
  #define Intersection_EXPORT __declspec(dllimport)
#endif
