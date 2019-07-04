#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ProcessParser.h"
class SysInfo {

 public:

  SysInfo() {
    /*
    Getting initial info about system
    Initial data for individual cores is set
    System data is set
    */
    try {
      this->getOtherCores(ProcessParser::GetNumberOfCores());
      this->setLastCpuMeasures();
      this->setAttributes();
      this->os_name_ = ProcessParser::GetOSName();
      this->kernel_ver_ = ProcessParser::GetSysKernelVersion();
    }
    catch (exception &e) {
      throw e;
    }
  }
  void setAttributes();
  void setLastCpuMeasures();
  string getMemPercent() const;
  long getUpTime() const;
  string getThreads() const;
  string getTotalProc() const;
  string getRunningProc() const;
  string getKernelVersion() const;
  string getOSName() const;
  string getCpuPercent() const;
  void getOtherCores(int _size);
  void setCpuCoresStats();
  vector<string> getCoresStats() const;

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