#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
std::string now_iso8601() {
  using std::chrono::system_clock;
  const auto now = system_clock::now();
  const std::time_t t = system_clock::to_time_t(now);
  std::tm tm{};
#if defined(_WIN32)
  gmtime_s(&tm, &t);
#else
  gmtime_r(&t, &tm);
#endif
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
  return oss.str();
}

void emit(const char *level, const std::string &msg) {
  std::cerr << now_iso8601() << " [" << level << "] " << msg << "\n";
}
} // namespace

namespace logging {
void info(const std::string &msg) { emit("INFO", msg); }
void warn(const std::string &msg) { emit("WARN", msg); }
void error(const std::string &msg) { emit("ERROR", msg); }
} // namespace logging
