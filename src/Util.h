//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once
#include <string>
#include <fstream>

using namespace std;

class Util {
 public:
  Util() = delete;

  static string ConvertToTime(long int input_seconds);
  static string GetProgressBar(string percent);
  static ifstream GetStream(string path);
};
