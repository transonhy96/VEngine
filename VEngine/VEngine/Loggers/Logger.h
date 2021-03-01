#pragma once
#include "../Config.h"
#include <memory>
#include "spdlog/spdlog.h"

namespace V {
	class V_API Logger
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}



#define  V_CORE_ERROR(...)  ::V::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define  V_CORE_WARN(...)   ::V::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define  V_CORE_INFO(...)   ::V::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define  V_CORE_TRACE(...)  ::V::Logger::GetCoreLogger()->trace(__VA_ARGS__)


#define  V_ERROR(...)  ::V::Logger::GetClientLogger()->error(__VA_ARGS__)
#define  V_WARN(...)   ::V::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define  V_INFO(...)   ::V::Logger::GetClientLogger()->info(__VA_ARGS__)
#define  V_TRACE(...)  ::V::Logger::GetClientLogger()->trace(__VA_ARGS__)

