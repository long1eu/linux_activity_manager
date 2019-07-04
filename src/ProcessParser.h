#pragma once

#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

#include "constants.h"
#include "util.h"

using namespace std;

class ProcessParser {
 private:
  static string fetchValue(string &&path, int index);
  static vector<string> fetchValues(string &&path, string searchString);
  static string fetchValue(string &&path, int index, string searchString);

 public:
  ProcessParser() = delete;
  ProcessParser(ProcessParser &) = delete;
  ProcessParser(ProcessParser &&) = delete;
  ~ProcessParser() = delete;

  static string getCmd(const string pid);
  static vector<string> getPidList();
  static std::string getVmSize(const string pid);
  static std::string getCpuPercent(const string pid);
  static long int getSysUpTime();
  static std::string getProcUpTime(const string pid);
  static string getProcUser(const string pid);
  static int getNumberOfCores();
  static vector<string> getSysCpuPercent(string coreNumber = "");
  static float getSysActiveCpuTime(vector<string> values);
  static float getSysIdleCpuTime(vector<string> values);
  static float getSysRamPercent();
  static string getSysKernelVersion();
  static int getTotalThreads();
  static int getTotalNumberOfProcesses();
  static int getNumberOfRunningProcesses();
  static string getOSName();
  static std::string PrintCpuStats(std::vector<std::string> values1, std::vector<std::string> values2);
  static bool isPidExisting(const string pid);

};
