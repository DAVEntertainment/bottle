#pragma once

#ifdef DEMOB_EXPORT_API
    #define DEFB_API  extern "C" __declspec(dllexport)
#else
    #define DEFB_API  extern "C" __declspec(dllimport)
#endif

DEFB_API void show_b();
