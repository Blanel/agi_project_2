#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstring>

#include "StopWatch.h"

namespace revel
{

#ifdef _WIN32
    #define FILE_SHORT (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define FILE_SHORT (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define R_LOG_INFO(l) do { std::stringstream ss; \
    ss << "[" << Log::clock().elapsed_time() << "] " \
       << FILE_SHORT << "::" << __LINE__ << "\t" << l; Log::info(ss.str()); } while(false)

#define R_LOG_ERR(l) do { std::stringstream ss; \
    ss << "[" << Log::clock().elapsed_time() << "] " \
       << FILE_SHORT << "::" << __LINE__ << "\t" << l; Log::err(ss.str()); } while(false)

class Log
{
    //static std::ofstream* s_pLogFile;
    static std::chrono::time_point<std::chrono::system_clock> s_StartTime;

    static StopWatch s_Time;

public:
    Log();

    static const StopWatch& clock() { return s_Time; }

    static void set_log_file(const std::string& filename);

    static void info(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }

    static void warn(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }

    static void err(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }
};

}

#endif // LOG_H
