#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Galaxy {
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T]: %v%$");
		GetLogger() = spdlog::stdout_color_st("LOG");
		GetLogger()->set_level(spdlog::level::trace);
	}
}
