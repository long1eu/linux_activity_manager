
#pragma once

#include <vector>
#include <string>
#include "Process.h"

class ProcessContainer {

 private:
  vector<Process> _list{};
 public:
  ProcessContainer() {
    this->refreshList();
  }
  int refreshList();
  string printList();
  vector<vector<string>> getList();
  vector<string> getList(int pageNumber);
};
