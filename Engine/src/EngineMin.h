#pragma once

#ifdef ENGINE_EXPORTS

#define MY_API __declspec(dllexport)

#else

#define MY_API __declspec(dllimport)

#endif 
