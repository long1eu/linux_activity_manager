#pragma once

#include <string>
#include "ProcessParser.h"

using namespace std;

class Process {

 public:
  Process(const string &pid) {
    this->pid_ = pid;
    try {
      this->user_ = ProcessParser::getProcUser(pid);
      this->mem_ = ProcessParser::getVmSize(pid);
      this->cmd_ = ProcessParser::getCmd(pid);
      if (cmd_.empty()) {
        this->cmd_ = string(70, ' ');
      }
      this->up_time_ = ProcessParser::getProcUpTime(pid);
      this->cpu_ = ProcessParser::getCpuPercent(pid);
    }
    catch (exception &e) {
      throw e;
    }
  }
  void pid(int pid);
  string pid() const;
  string user() const;
  string cmd() const;
  int cpu() const;
  int mem() const;
  string up_time() const;
  string process();

 private:
  string pid_;
  string user_;
  string cmd_;
  string cpu_;
  string mem_;
  string up_time_;

};
