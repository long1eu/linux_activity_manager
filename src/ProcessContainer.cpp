//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessContainer.h"

int ProcessContainer::RefreshList() {
  vector<string> pid_list = ProcessParser::getPidList();
  list_.clear();
  for (int i = 0; i < pid_list.size(); i++) {
    try {
      Process proc(pid_list[i]);
      list_.push_back(proc);
    }
    catch (exception &e) {
      pid_list.erase(pid_list.begin() + i);
    }
  }
  return list_.size();
}

string ProcessContainer::PrintList() {
  stringstream result;

  for (Process &i : list_) {
    result << i.process();
  }

  return result.str();
}

vector<vector<string>> ProcessContainer::GetList() {
  vector<vector<string>> values;
  vector<string> list;
  for (auto &i : ProcessContainer::list_) {
    list.emplace_back(i.process());
  }

  int lastIndex = 0;
  for (int i = 0; i < list.size(); i++) {
    if (i % 10 == 0 && i > 0) {
      vector<string> sub(&list[i - 10], &list[i]);
      values.emplace_back(sub);
      lastIndex = i;
    }
    if (i == (ProcessContainer::list_.size() - 1) && (i - lastIndex) < 10) {
      vector<string> sub(&list[lastIndex], &list[i + 1]);
      values.push_back(sub);
    }
  }

  return move(values);
}

vector<string> ProcessContainer::GetList(int page_number) {
  vector<string> list;
  const int start = page_number * PROCESS_LIST_SIZE;
  for (int i = start; i < ProcessContainer::list_.size() && i < start + PROCESS_LIST_SIZE; i++) {
    list.push_back(ProcessContainer::list_[i].process());
  }
  return move(list);

}

