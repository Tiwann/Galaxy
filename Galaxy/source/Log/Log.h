#pragma once
#include <spdlog/spdlog.h>

#ifdef DEBUG
	#define LOG_TRACE(...)	Log::GetLogger()->trace(__VA_ARGS__); 
	#define LOG_INFO(...)	Log::GetLogger()->info(__VA_ARGS__); 
	#define LOG_WARN(...)	Log::GetLogger()->warn(__VA_ARGS__); 
	#define LOG_ERROR(...)	Log::GetLogger()->error(__VA_ARGS__); 
#else
	#define LOG_TRACE(...)
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
#endif

class Log
{
private:
	static std::shared_ptr<spdlog::logger> _coreLogger;
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return _coreLogger; }

};

