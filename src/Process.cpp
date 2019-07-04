#include "Process.h"

void Process::pid(int pid) { pid_ = to_string(pid); }
string Process::pid() const { return pid_; }
string Process::user() const { return user_; }
string Process::cmd() const { return cmd_; }
int Process::cpu() const { return stoi(cpu_); }
int Process::mem() const { return stoi(mem_); }
string Process::up_time() const { return up_time_; }

string Process::process() {
  if (!ProcessParser::isPidExisting(pid_))
    return "";

  stringstream result;
  mem_ = ProcessParser::getVmSize(pid_);
  up_time_ = ProcessParser::getProcUpTime(pid_);
  cpu_ = ProcessParser::getCpuPercent(pid_);

  result << pid_ << "   " <<
         user_ << "   " <<
         mem_ << "   " <<
         cpu_ << "   " <<
         up_time_ << "   " <<
         cmd_.substr(0, 50) << string(20, ' ');
  return result.str();
}