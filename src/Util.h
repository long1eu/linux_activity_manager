#pragma once
#include <string>
#include <fstream>

using namespace std;

class Util {
 public:
  Util() = delete;

  static string convertToTime(long int input_seconds);
  static string getProgressBar(string percent);
  static ifstream getStream(string path);
};
