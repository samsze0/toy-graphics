#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// #define TRACE(logger, ...) logger.GetLogger()->trace(__VA_ARGS__)
// #define INFO(logger, ...) logger.GetLogger()->info(__VA_ARGS__)
// #define WARN(logger, ...) logger.GetLogger()->warn(__VA_ARGS__)
// #define ERROR(logger, ...) logger.GetLogger()->error(__VA_ARGS__)
// #define FATAL(logger, ...) logger.GetLogger()->fatal(__VA_ARGS__)

#define TRACE(...) Logger::logger->trace(__VA_ARGS__)
#define INFO(...) Logger::logger->info(__VA_ARGS__)
#define WARN(...) Logger::logger->warn(__VA_ARGS__)
#define ERROR(...) Logger::logger->error(__VA_ARGS__)
#define FATAL(...) Logger::logger->fatal(__VA_ARGS__)

class Logger {
private:
  // std::shared_ptr<spdlog::logger> logger;
  // std::string name;
public:
  static std::shared_ptr<spdlog::logger> logger;
  static std::string name;
public:
  // Logger(const std::string& name);
  // Logger(std::string&& name);  // rvalue ref (temporary obj)

  // For const smart pointer, see
  // https://stackoverflow.com/questions/17793333/difference-between-const-shared-ptrt-and-shared-ptrconst-t
  // however info, warn, error etc are not const methods
  // std::shared_ptr<const spdlog::logger> GetLogger() const;

  // std::shared_ptr<spdlog::logger> GetLogger();

  static void Init();
};