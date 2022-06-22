#pragma once
#include <cstdint>
#include <thread>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

// int var = 10; // fatal error LNK1169: one or more multiply defined symbols found
static int var = 10;

// void Func() {} // fatal error LNK1169: one or more multiply defined symbols found
static void FuncStatic() {}
inline void FuncInline() {}

uint64_t GetStaticPointerFromShare0();
uint64_t GetStaticPointerFromShare1();

uint64_t GetInlinePointerFromShare0();
uint64_t GetInlinePointerFromShare1();
