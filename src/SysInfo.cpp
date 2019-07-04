//
// Created by Razvan Lung on 2019-07-04.
//

#include "SysInfo.h"

void SysInfo::getOtherCores(int _size) {
//when number of cores is detected, vectors are modified to fit incoming data
  coresStats = vector<string>{};
  coresStats.resize(_size);
  lastCpuCoresStats = vector<vector<string>>{};
  lastCpuCoresStats.resize(_size);
  currentCpuCoresStats = vector<vector<string>>{};
  currentCpuCoresStats.resize(_size);
  for (int i = 0; i < _size; i++) {
    lastCpuCoresStats[i] = ProcessParser::GetSysCpuPercent(to_string(i));
  }
}

void SysInfo::setLastCpuMeasures() {
  lastCpuStats = ProcessParser::GetSysCpuPercent();
}
void SysInfo::setCpuCoresStats() {
// Getting data from files (previous data is required)
  for (int i = 0; i < currentCpuCoresStats.size(); i++) {
    currentCpuCoresStats[i] = ProcessParser::GetSysCpuPercent(to_string(i));
  }
  for (int i = 0; i < currentCpuCoresStats.size(); i++) {
    // after acquirement of data we are calculating every core percentage of usage
    coresStats[i] = ProcessParser::PrintCpuStats(lastCpuCoresStats[i], currentCpuCoresStats[i]);
  }
  lastCpuCoresStats = currentCpuCoresStats;
}

void SysInfo::setAttributes() {
  memPercent = ProcessParser::GetSysRamPercent();
  upTime = ProcessParser::GetSysUpTime();
  totalProc = ProcessParser::GetTotalNumberOfProcesses();
  runningProc = ProcessParser::GetNumberOfRunningProcesses();
  threads = ProcessParser::GetTotalThreads();
  currentCpuStats = ProcessParser::GetSysCpuPercent();
  cpuPercent = ProcessParser::PrintCpuStats(lastCpuStats, currentCpuStats);
  lastCpuStats = currentCpuStats;
  setCpuCoresStats();
}

// Constructing string for every core data display
vector<string> SysInfo::getCoresStats() const {
  vector<string> result = vector<string>{};
  for (int i = 0; i < coresStats.size(); i++) {
    string temp = ("cpu" + to_string(i) + ": ");
    float check;
    if (!coresStats[i].empty())
      check = stof(coresStats[i]);
    if (!check || coresStats[i] == "nan") {
      return vector<string>();
    }
    temp += Util::getProgressBar(coresStats[i]);
    result.push_back(temp);
  }
  return move(result);
}

string SysInfo::getCpuPercent() const { return this->cpuPercent; }
string SysInfo::getMemPercent() const { return to_string(this->memPercent); }
long SysInfo::getUpTime() const { return this->upTime; }
string SysInfo::getKernelVersion() const { return this->kernelVer; }
string SysInfo::getTotalProc() const { return to_string(this->totalProc); }
string SysInfo::getRunningProc() const { return to_string(this->runningProc); }
string SysInfo::getThreads() const { return to_string(this->threads); }
string SysInfo::getOSName() const { return this->OSname; }
