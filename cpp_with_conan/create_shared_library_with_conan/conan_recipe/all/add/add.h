#pragma once

#ifdef DEMO_EXPORT_API
    #define DEF_API  extern "C" __declspec(dllexport)
#else
    #define DEF_API  extern "C" __declspec(dllimport)
#endif

DEF_API int add(int, int);

