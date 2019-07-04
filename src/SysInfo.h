//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ProcessParser.h"

class SysInfo {

 public:
  SysInfo() {
    try {
      GetOtherCores(ProcessParser::GetNumberOfCores());
      SetLastCpuMeasures();
      SetAttributes();
      os_name_ = ProcessParser::GetOSName();
      kernel_ver_ = ProcessParser::GetSysKernelVersion();
    }
    catch (exception &e) {
      throw e;
    }
  }

  void SetAttributes();
  void SetLastCpuMeasures();
  void GetOtherCores(int _size);
  void setCpuCoresStats();
  vector<string> GetCoresStats() const;

  string mem_percent() const;
  long up_time() const;
  string threads() const;
  string total_proc() const;
  string running_proc() const;
  string kernel_ver() const;
  string os_name() const;
  string cpu_percent() const;

 private:
  vector<string> last_cpu_stats_;
  vector<string> current_cpu_stats_;
  vector<string> cores_stats_;
  vector<vector<string>> last_cpu_cores_stats;
  vector<vector<string>> current_cpu_cores_stats_;
  string cpu_percent_;
  float mem_percent_;
  string os_name_;
  string kernel_ver_;
  long up_time_;
  int total_proc_;
  int running_proc_;
  int threads_;
};