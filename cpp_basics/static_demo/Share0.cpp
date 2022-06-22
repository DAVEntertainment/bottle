#include "Common.h"

uint64_t GetStaticPointerFromShare0()
{
    auto p = reinterpret_cast<void*>(&FuncStatic);
    return reinterpret_cast<uint64_t>(p);
}

uint64_t GetInlinePointerFromShare0()
{
    auto p = reinterpret_cast<void*>(&FuncInline);
    return reinterpret_cast<uint64_t>(p);
}
