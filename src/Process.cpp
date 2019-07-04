#include "Process.h"

void Process::pid(int pid) {
  this->pid_ = pid;
}
string Process::pid() const {
  return this->pid_;
}

string Process::process() {
  if (!ProcessParser::isPidExisting(this->pid_))
    return "";
  this->mem_ = ProcessParser::getVmSize(this->pid_);
  this->up_time_ = ProcessParser::getProcUpTime(this->pid_);
  this->cpu_ = ProcessParser::getCpuPercent(this->pid_);

  return this->pid_ + "   " + this->user_ + "   " + this->mem_ + "   " + this->cpu_ + "   " + this->up_time_ + "   "
      + this->cmd_.substr(0, 50) + string(20, ' ');
}

string Process::user() const {
  return this->user_;
}

string Process::cmd() const {
  return this->cmd_;
}

int Process::cpu() const {
  return stoi(this->cpu_);
}

int Process::mem() const {
  return stoi(this->mem_);
}
string Process::up_time() const {
  return this->up_time_;
}
