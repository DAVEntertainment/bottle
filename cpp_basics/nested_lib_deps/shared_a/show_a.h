#pragma once

#ifdef DEMOA_EXPORT_API
    #define DEFA_API  extern "C" __declspec(dllexport)
#else
    #define DEFA_API  extern "C" __declspec(dllimport)
#endif

DEFA_API void show_a();

