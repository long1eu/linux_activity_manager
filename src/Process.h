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
    pid = pid;
    try {
      user = ProcessParser::getProcUser(pid);
      mem = ProcessParser::getVmSize(pid);
      cmd = ProcessParser::getCmd(pid);
      if (cmd.empty()) {
        cmd = string(70, ' ');
      }
      upTime = ProcessParser::getProcUpTime(pid);
      cpu = ProcessParser::getCpuPercent(pid);
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
