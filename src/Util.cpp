//
// Created by Razvan Lung on 2019-07-04.
//

#include "Util.h"

string Util::ConvertToTime(long int input_seconds) {
  long minutes = input_seconds / 60;
  long hours = minutes / 60;
  long seconds = int(input_seconds % 60);
  minutes = int(minutes % 60);
  string result = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
  return result;
}

string Util::GetProgressBar(string percent) {

  string result = "0%% ";
  int _size = 50;
  int boundaries;
  try {
    boundaries = (stof(percent) / 100) * _size;
  } catch (...) {
    boundaries = 0;
  }

  for (int i = 0; i < _size; i++) {
    if (i <= boundaries) {
      result += "|";
    } else {
      result += " ";
    }
  }

  result += " " + percent.substr(0, 5) + " /100%%";
  return result;
}

ifstream Util::GetStream(string path) {
  ifstream stream{};
  stream.open(path, ifstream::in);
  if (!stream && !stream.is_open()) {
    stream.close();
    throw runtime_error("Non - existing PID");
  }
  return move(stream);
}
