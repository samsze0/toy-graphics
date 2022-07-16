#include "logger.h"
#include <spdlog/spdlog.h>

Logger::Logger(const std::string& name)
  : name(name) {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  this->logger = spdlog::stdout_color_mt(name);
  this->logger->set_level(spdlog::level::trace);
}

// Logger::Logger(std::string&& name)
//   : name(std::move(name)) {
//   this->logger = spdlog::stdout_color_mt(name);
// }

// std::shared_ptr<const spdlog::logger> Logger::GetLogger() const {
//   return this->logger;
// }

std::shared_ptr<spdlog::logger> Logger::GetLogger() {
  return this->logger;
}