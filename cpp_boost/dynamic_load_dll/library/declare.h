#pragma once

#ifdef DEMO_EXPORT_API
    #define DEF_API __declspec(dllexport)
#else
    #define DEF_API __declspec(dllimport)
#endif

DEF_API int add(int, int);

