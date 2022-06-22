#include "Common.h"

uint64_t GetStaticPointerFromShare1()
{
    auto p = reinterpret_cast<void*>(&FuncStatic);
    return reinterpret_cast<uint64_t>(p);
}

uint64_t GetInlinePointerFromShare1()
{
    auto p = reinterpret_cast<void*>(&FuncInline);
    return reinterpret_cast<uint64_t>(p);
}
