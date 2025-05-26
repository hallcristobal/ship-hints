#include "utils.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <string>
#include <vector>

std::string Utils::getExecutablePath() {
  char buffer[PATH_MAX];
  uint32_t buffer_size = sizeof(buffer);
#if __APPLE__ && __MACH__
  if (_NSGetExecutablePath(buffer, &buffer_size) != 0) {
    std::cerr << "Unable to determine the current executable directory"
              << std::endl;
    exit(-1);
  }
#elif __unix__
  ssize_t len = readlink("/proc/self/exe", buffer, buffer_size - 1);
  if (len < 1) {
    std::cerr << "Unable to determine the current executable directory"
              << std::endl;
    exit(-1);
  }
  buffer[len] = '\0';
#endif
  return std::string(buffer);
}

std::vector<std::string> Utils::split_string(const std::string &str) {
  std::stringstream ss(str);
  std::string token;
  std::vector<std::string> result;
  while (ss >> token) {
    token.erase(std::remove_if(token.begin(), token.end(),
                               [](char c) { return c == ',' || c == ' '; }));
    result.push_back(token);
  }
  return result;
}

void Utils::log(const char *const caller, const char *const message,
                LogFlags flags) {
#ifdef DEBUG
  std::ostream *stream = flags & LogFlags::ERROR ? &std::cerr : &std::cout;
  *stream << "[" << caller << "] " << message << std::endl;
#endif
}
void Utils::log(const char *const caller, const std::string &message,
                LogFlags flags) {
#ifdef DEBUG
  Utils::log(caller, message.c_str(), flags);
#endif
}
