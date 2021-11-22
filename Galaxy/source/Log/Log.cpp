#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


std::shared_ptr<spdlog::logger> Log::_coreLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T]: %v%$");
	GetLogger() = spdlog::stdout_color_st("LOG");
	GetLogger()->set_level(spdlog::level::trace);
}
