//
// Created by Razvan Lung on 2019-07-04.
//

#include "SysInfo.h"

void SysInfo::getOtherCores(int _size) {
//when number of cores is detected, vectors are modified to fit incoming data
  coresStats = std::vector<std::string>{};
  coresStats.resize(_size);
  lastCpuCoresStats = std::vector<std::vector<std::string>>{};
  lastCpuCoresStats.resize(_size);
  currentCpuCoresStats = std::vector<std::vector<std::string>>{};
  currentCpuCoresStats.resize(_size);
  for (int i = 0; i < _size; i++) {
    lastCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));
  }
}
void SysInfo::setLastCpuMeasures() {
  lastCpuStats = ProcessParser::getSysCpuPercent();
}
void SysInfo::setCpuCoresStats() {
// Getting data from files (previous data is required)
  for (int i = 0; i < currentCpuCoresStats.size(); i++) {
    currentCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));
  }
  for (int i = 0; i < currentCpuCoresStats.size(); i++) {
    // after acquirement of data we are calculating every core percentage of usage
    coresStats[i] = ProcessParser::PrintCpuStats(lastCpuCoresStats[i], currentCpuCoresStats[i]);
  }
  lastCpuCoresStats = currentCpuCoresStats;
}
void SysInfo::setAttributes() {
// getting parsed data
  memPercent = ProcessParser::getSysRamPercent();
  upTime = ProcessParser::getSysUpTime();
  totalProc = ProcessParser::getTotalNumberOfProcesses();
  runningProc = ProcessParser::getNumberOfRunningProcesses();
  threads = ProcessParser::getTotalThreads();
  currentCpuStats = ProcessParser::getSysCpuPercent();
  cpuPercent = ProcessParser::PrintCpuStats(lastCpuStats, currentCpuStats);
  lastCpuStats = currentCpuStats;
  setCpuCoresStats();

}
// Constructing string for every core data display
std::vector<std::string> SysInfo::getCoresStats() const {
  std::vector<std::string> result = std::vector<std::string>{};
  for (int i = 0; i < coresStats.size(); i++) {
    std::string temp = ("cpu" + to_string(i) + ": ");
    float check;
    if (!coresStats[i].empty())
      check = stof(coresStats[i]);
    if (!check || coresStats[i] == "nan") {
      return std::vector<std::string>();
    }
    temp += Util::getProgressBar(coresStats[i]);
    result.push_back(temp);
  }
  return std::move(result);
}
std::string SysInfo::getCpuPercent() const {
  return cpuPercent;
}
std::string SysInfo::getMemPercent() const {
  return to_string(memPercent);
}
long SysInfo::getUpTime() const {
  return upTime;
}
std::string SysInfo::getKernelVersion() const {
  return kernelVer;
}
std::string SysInfo::getTotalProc() const {
  return to_string(totalProc);
}
std::string SysInfo::getRunningProc() const {
  return to_string(runningProc);
}
std::string SysInfo::getThreads() const {
  return to_string(threads);
}
std::string SysInfo::getOSName() const {
  return OSname;
}
