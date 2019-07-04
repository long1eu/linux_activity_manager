#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ProcessParser.h"
class SysInfo {
 private:
  vector<string> lastCpuStats;
  vector<string> currentCpuStats;
  vector<string> coresStats;
  vector<vector<string>> lastCpuCoresStats;
  vector<vector<string>> currentCpuCoresStats;
  string cpuPercent;
  float memPercent;
  string OSname;
  string kernelVer;
  long upTime;
  int totalProc;
  int runningProc;
  int threads;

 public:

  SysInfo() {
    /*
    Getting initial info about system
    Initial data for individual cores is set
    System data is set
    */
    try {
      this->getOtherCores(ProcessParser::getNumberOfCores());
      this->setLastCpuMeasures();
      this->setAttributes();
      this->OSname = ProcessParser::getOSName();
      this->kernelVer = ProcessParser::getSysKernelVersion();
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

};