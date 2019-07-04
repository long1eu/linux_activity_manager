//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessContainer.h"

int ProcessContainer::refreshList() {
  std::vector<std::string> pidList = ProcessParser::getPidList();
  _list.clear();
  for (int i = 0; i < pidList.size(); i++) {
    try {
      Process proc(pidList[i]);
      _list.push_back(proc);
    }
    catch (exception &e) {
      pidList.erase(pidList.begin() + i);
    }
  }
  return _list.size();
}
std::string ProcessContainer::printList() {
  std::string result = "";
  for (int i = 0; i < _list.size(); i++) {
    result += _list[i].getProcess();
  }
  return result;
}
std::vector<std::vector<std::string>> ProcessContainer::getList() {
  std::vector<std::vector<std::string>> values;
  std::vector<std::string> stringifiedList;
  for (int i = 0; i < ProcessContainer::_list.size(); i++) {
    stringifiedList.push_back(ProcessContainer::_list[i].getProcess());
  }
  int lastIndex = 0;
  for (int i = 0; i < stringifiedList.size(); i++) {
    if (i % 10 == 0 && i > 0) {
      std::vector<std::string> sub(&stringifiedList[i - 10], &stringifiedList[i]);
      values.push_back(sub);
      lastIndex = i;
    }
    if (i == (ProcessContainer::_list.size() - 1) && (i - lastIndex) < 10) {
      std::vector<std::string> sub(&stringifiedList[lastIndex], &stringifiedList[i + 1]);
      values.push_back(sub);
    }
  }
  return std::move(values);
}

std::vector<std::string> ProcessContainer::getList(int pageNumber) {
  std::vector<std::string> stringifiedList;
  const int start = pageNumber * PROCESS_LIST_SIZE;
  for (int i = start; i < ProcessContainer::_list.size() && i < start + PROCESS_LIST_SIZE; i++) {
    stringifiedList.push_back(ProcessContainer::_list[i].getProcess());
  }
  return std::move(stringifiedList);

}

