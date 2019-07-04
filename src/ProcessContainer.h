
#pragma once

#include <vector>
#include <string>
#include "Process.h"

class ProcessContainer {

 private:
  std::vector<Process> _list{};
 public:
  ProcessContainer() {
    this->refreshList();
  }
  int refreshList();
  std::string printList();
  std::vector<std::vector<std::string>> getList();
  std::vector<std::string> getList(int pageNumber);
};
