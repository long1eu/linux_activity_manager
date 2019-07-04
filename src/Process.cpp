//
// Created by Razvan Lung on 2019-07-04.
//

#include "Process.h"

void Process::setPid(int pid) { pid = pid; }
string Process::getPid() const { return pid; }

string Process::getProcess() {
  if (!ProcessParser::isPidExisting(pid))
    return "";

  mem = ProcessParser::getVmSize(pid);
  upTime = ProcessParser::getProcUpTime(pid);
  cpu = ProcessParser::getCpuPercent(pid);

  return pid + "   " + user + "   " + mem + "   " + cpu + "   " + upTime + "   "
      + cmd.substr(0, 50) + string(20, ' ');
}

std::string Process::getUser() const {
  return user;
}

std::string Process::getCmd() const {
  return cmd;
}

int Process::getCpu() const {
  return std::stoi(cpu);
}

int Process::getMem() const {
  return std::stoi(mem);
}
std::string Process::getUpTime() const {
  return upTime;
}
