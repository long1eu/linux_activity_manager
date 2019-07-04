
#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "Process.h"

class ProcessContainer {

 public:
  ProcessContainer() {
    RefreshList();
  }

  int RefreshList();
  string PrintList();
  vector<vector<string>> GetList();
  vector<string> GetList(int page_number);

 private:
  vector<Process> list_{};
};
