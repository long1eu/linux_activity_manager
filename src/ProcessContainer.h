
#pragma once

#include <vector>
#include <string>
#include "Process.h"

class ProcessContainer {

 public:
  ProcessContainer() {
    refreshList();
  }

  int refreshList();
  string printList();
  vector<vector<string>> getList();
  vector<string> getList(int pageNumber);

 private:
  vector<Process> _list{};
};
