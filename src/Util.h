#pragma once
#include <string>
#include <fstream>

class Util {
 public:
  Util() = delete;

  static std::string convertToTime(long int input_seconds);
  static std::string getProgressBar(std::string percent);
  static std::ifstream getStream(std::string path);
};
