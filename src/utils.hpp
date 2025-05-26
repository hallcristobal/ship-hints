#pragma once

#if __APPLE__ && __MACH__
#include <mach-o/dyld.h>
#elif __unix__
#include <unistd.h>
#else
#error "Unsupported architecture"
#endif

#include <limits.h>
#include <string>
#include <vector>

#define ENUM_MACRO(name, ...)                                                  \
  typedef enum { __VA_ARGS__ } name;                                           \
  const std::vector<std::string> name##Strings =                               \
      Utils::split_string(std::string(#__VA_ARGS__));

namespace Utils {
std::string getExecutablePath();

std::vector<std::string> split_string(const std::string &str);

} // namespace Utils
