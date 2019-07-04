//
// Created by Razvan Lung on 2019-07-04.
//

#include "Process.h"

void Process::setPid(int pid) {
  this->pid = pid;
}
string Process::getPid() const {
  return this->pid;
}

string Process::getProcess() {
  if (!ProcessParser::isPidExisting(this->pid))
    return "";
  this->mem = ProcessParser::getVmSize(this->pid);
  this->upTime = ProcessParser::getProcUpTime(this->pid);
  this->cpu = ProcessParser::getCpuPercent(this->pid);

  return this->pid + "   " + this->user + "   " + this->mem + "   " + this->cpu + "   " + this->upTime + "   "
      + this->cmd.substr(0, 50) + string(20, ' ');
}

std::string Process::getUser() const {
  return this->user;
}

std::string Process::getCmd() const {
  return this->cmd;
}

int Process::getCpu() const {
  return std::stoi(this->cpu);
}

int Process::getMem() const {
  return std::stoi(this->mem);
}
std::string Process::getUpTime() const {
  return this->upTime;
}
