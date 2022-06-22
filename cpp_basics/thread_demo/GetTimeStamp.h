#pragma once
#include <cstdint>
#include <thread>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

static std::string GetTimeStamp()
{
    std::stringstream ss;
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    tm now_tm;

#if defined(_WIN32)
    localtime_s(&now_tm, &now_t);
#elif defined(MS_LINUX)
    localtime_r(&now_t, &now_tm);
#endif

    ss  << std::setfill('0') << std::setw(2) << now_tm.tm_hour
        << ":" << std::setfill('0') << std::setw(2) << now_tm.tm_min
        << ":" << std::setfill('0') << std::setw(2) << now_tm.tm_sec;

    auto tp = now.time_since_epoch();
    auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(tp)
        - std::chrono::duration_cast<std::chrono::seconds>(tp);
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();

    return ss.str();
}


