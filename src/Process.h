//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <string>
#include <sstream>
#include "ProcessParser.h"

using namespace std;

class Process {

 public:
  Process(const string &pid) {
    pid_ = pid;
    try {
      user_ = ProcessParser::GetProcUser(pid);
      mem_ = ProcessParser::GetVmSize(pid);
      cmd_ = ProcessParser::GetCmd(pid);
      if (cmd_.empty()) {
        cmd_ = string(70, ' ');
      }
      up_time_ = ProcessParser::GetProcUpTime(pid);
      cpu_ = ProcessParser::GetCpuPercent(pid);
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
