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
#include "Util.h"

using namespace std;

class ProcessParser {

 public:
  ProcessParser() = delete;

  static string GetCmd(const string &pid);
  static vector<string> GetPidList();
  static string GetVmSize(const string &pid);
  static string GetCpuPercent(const string &pid);
  static long int GetSysUpTime();
  static string GetProcUpTime(const string &pid);
  static string GetProcUser(const string &pid);
  static int GetNumberOfCores();
  static vector<string> GetSysCpuPercent(const string &coreNumber = "");
  static float GetSysActiveCpuTime(vector<string> values);
  static float GetSysIdleCpuTime(vector<string> values);
  static float GetSysRamPercent();
  static string GetSysKernelVersion();
  static int GetTotalThreads();
  static int GetTotalNumberOfProcesses();
  static int GetNumberOfRunningProcesses();
  static string GetOSName();
  static string PrintCpuStats(const vector<string> &values1, const vector<string> &values2);
  static bool IsPidExisting(const string &pid);

 private:
  static string FetchValue(string &&path, int index);
  static vector<string> FetchValues(string &&path, const string &searchString);
  static string FetchValue(string &&path, int index, string search_string);
};
