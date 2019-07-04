#pragma once

#include <string>
#include "ProcessParser.h"

using namespace std;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 private:
  string pid;
  string user;
  string cmd;
  string cpu;
  string mem;
  string upTime;

 public:
  Process(string pid) {
    this->pid = pid;
    try {
      this->user = ProcessParser::getProcUser(pid);
      this->mem = ProcessParser::getVmSize(pid);
      this->cmd = ProcessParser::getCmd(pid);
      if (cmd.empty()) {
        this->cmd = string(70, ' ');
      }
      this->upTime = ProcessParser::getProcUpTime(pid);
      this->cpu = ProcessParser::getCpuPercent(pid);
    }
    catch (exception &e) {
      throw e;
    }
  }
  void setPid(int pid);
  string getPid() const;
  string getUser() const;
  string getCmd() const;
  int getCpu() const;
  int getMem() const;
  string getUpTime() const;
  string getProcess();
};
