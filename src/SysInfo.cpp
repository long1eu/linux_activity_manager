//
// Created by Razvan Lung on 2019-07-04.
//

#include "SysInfo.h"

void SysInfo::GetOtherCores(int _size) {
//when number of cores is detected, vectors are modified to fit incoming data
  cores_stats_ = vector<string>{};
  cores_stats_.resize(_size);
  last_cpu_cores_stats = vector<vector<string>>{};
  last_cpu_cores_stats.resize(_size);
  current_cpu_cores_stats_ = vector<vector<string>>{};
  current_cpu_cores_stats_.resize(_size);
  for (int i = 0; i < _size; i++) {
    last_cpu_cores_stats[i] = ProcessParser::GetSysCpuPercent(to_string(i));
  }
}

void SysInfo::SetLastCpuMeasures() {
  last_cpu_stats_ = ProcessParser::GetSysCpuPercent();
}
void SysInfo::setCpuCoresStats() {
// Getting data from files (previous data is required)
  for (int i = 0; i < current_cpu_cores_stats_.size(); i++) {
    current_cpu_cores_stats_[i] = ProcessParser::GetSysCpuPercent(to_string(i));
  }
  for (int i = 0; i < current_cpu_cores_stats_.size(); i++) {
    // after acquirement of data we are calculating every core percentage of usage
    cores_stats_[i] = ProcessParser::PrintCpuStats(last_cpu_cores_stats[i], current_cpu_cores_stats_[i]);
  }
  last_cpu_cores_stats = current_cpu_cores_stats_;
}

void SysInfo::SetAttributes() {
  mem_percent_ = ProcessParser::GetSysRamPercent();
  up_time_ = ProcessParser::GetSysUpTime();
  total_proc_ = ProcessParser::GetTotalNumberOfProcesses();
  running_proc_ = ProcessParser::GetNumberOfRunningProcesses();
  threads_ = ProcessParser::GetTotalThreads();
  current_cpu_stats_ = ProcessParser::GetSysCpuPercent();
  cpu_percent_ = ProcessParser::PrintCpuStats(last_cpu_stats_, current_cpu_stats_);
  last_cpu_stats_ = current_cpu_stats_;
  setCpuCoresStats();
}

// Constructing string for every core data display
vector<string> SysInfo::getCoresStats() const {
  vector<string> result = vector<string>{};
  for (int i = 0; i < cores_stats_.size(); i++) {
    string temp = ("cpu" + to_string(i) + ": ");
    float check;
    if (!cores_stats_[i].empty())
      check = stof(cores_stats_[i]);
    if (!check || cores_stats_[i] == "nan") {
      return vector<string>();
    }
    temp += Util::getProgressBar(cores_stats_[i]);
    result.push_back(temp);
  }
  return move(result);
}

string SysInfo::getCpuPercent() const { return cpu_percent_; }
string SysInfo::getMemPercent() const { return to_string(mem_percent_); }
long SysInfo::getUpTime() const { return up_time_; }
string SysInfo::getKernelVersion() const { return kernel_ver_; }
string SysInfo::getTotalProc() const { return to_string(total_proc_); }
string SysInfo::getRunningProc() const { return to_string(running_proc_); }
string SysInfo::getThreads() const { return to_string(threads_); }
string SysInfo::getOSName() const { return os_name_; }
