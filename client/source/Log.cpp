#include "Log.h"

namespace revel
{

Log::Log()
{
}

void
Log::set_log_file(const std::string &filename)
{

}


//std::chrono::time_point<std::chrono::system_clock>
//Log::s_StartTime = std::chrono::system_clock::now();

StopWatch
Log::s_Time = StopWatch();

} // ::revel
