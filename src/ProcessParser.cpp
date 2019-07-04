//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessParser.h"

vector<string> ProcessParser::GetPidList() {
  DIR *dir;
  // Basically, we are scanning /proc dir for all directories with numbers as their names
  // If we get valid check we store dir names in vector as list of machine pids
  vector<string> container;
  if (!(dir = opendir("/proc")))
    throw runtime_error(strerror(errno));

  while (dirent *dirp = readdir(dir)) {
    // is this a directory?
    if (dirp->d_type != DT_DIR)
      continue;
    // Is every character of the name a digit?
    if (all_of(dirp->d_name, dirp->d_name + strlen(dirp->d_name), [](char c) { return isdigit(c); })) {
      container.push_back(dirp->d_name);
    }
  }
  //Validating process of directory closing
  if (closedir(dir))
    throw runtime_error(strerror(errno));
  return container;
}

string ProcessParser::GetCmd(string pid) {
  try {
    string line;
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::cmdPath()));
    getline(stream, line);
    return line;
  }
  catch (runtime_error &e) {
    throw e;
  }
  catch (exception &e) {
    //Ignore this exception and return empty string
  }
  return string(70, ' ');
}

string ProcessParser::FetchValue(string &&path, int index) {
  try {
    ifstream stream = Util::getStream(path);
    string line;
    getline(stream, line);
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end);
    return values[index];
  }
  catch (exception &e) {
    throw e;
  }
}

vector<string> ProcessParser::FetchValues(string &&path, string searchString) {
  try {
    string line;
    ifstream stream = Util::getStream(path);
    while (getline(stream, line)) {
      if (line.compare(0, searchString.size(), searchString) == 0) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> values(beg, end);
        return values;
      }
    }
  }
  catch (exception &e) {
    throw e;
  }
  throw invalid_argument("Failed to find the search string.");
}

string ProcessParser::FetchValue(string &&path, int index, string searchString) {
  try {
    //TODO: Check if the index is in bounds
    return FetchValues(move(path), searchString)[index];
  }
  catch (exception &e) {
    throw e;
  }
  return "";
}

long int ProcessParser::GetSysUpTime() {
  try {
    return stoi(FetchValue(Path::basePath() + Path::upTimePath(), 0));
  }
  catch (invalid_argument &e) {
    //Ignore this exception
  }
  catch (exception &e) {
    throw e;
  }
  return 0;
}

string ProcessParser::GetProcUpTime(string pid) {
  try {
    return to_string(float(
        stof(FetchValue(Path::basePath() + pid + "/" + Path::statPath(), 13)) / sysconf(_SC_CLK_TCK)));
  }
  catch (runtime_error &e) {
    throw e;
  }
  catch (exception &e) {
    //Ignore the rest of the exceptions
  }
  return "";
}

int ProcessParser::GetNumberOfCores() {
  // Get the number of host cpu cores
  try {
    string result = FetchValue(Path::basePath() + "cpuinfo", 3, "cpu cores");
    if (result.size() != 0) {
      return stoi(result);
    }
  }
  catch (invalid_argument &e) {
    return 0;
  }
  catch (exception &e) {
    throw e;
  }
  return 0;
}

string ProcessParser::GetSysKernelVersion() {
  try {
    return FetchValue(Path::basePath() + Path::versionPath(), 2, "Linux version ");
  }
  catch (exception &e) {
    throw e;
  }
}

string ProcessParser::GetVmSize(string pid) {
  try {
    return to_string(stof(FetchValue(Path::basePath() + pid + Path::statusPath(), 1, "VmData")) / float(1024 * 1024));
  }
  catch (runtime_error &e) {
    throw e;
  }
  catch (exception &e) {
    //Ignore the error
  }
  return "0.0";
}

int ProcessParser::GetTotalNumberOfProcesses() {
  try {
    return stoi(FetchValue(Path::basePath() + Path::statPath(), 1, "processes"));
  }
  catch (invalid_argument &e) {
    return 0;
  }
  catch (exception &e) {
    throw e;
  }
}

int ProcessParser::GetNumberOfRunningProcesses() {
  try {
    return stoi(FetchValue(Path::basePath() + Path::statPath(), 1, "procs_running"));
  }
  catch (invalid_argument &e) {
    return 0;
  }
  catch (exception &e) {
    throw e;
  }
}

string ProcessParser::GetOSName() {
  try {
    string line = FetchValue("/etc/os-release", 0, "PRETTY_NAME") + FetchValue("/etc/os-release", 1, "PRETTY_NAME");
    size_t found = line.find("=") + 1;
    string result = line.substr(found);
    result.erase(remove(result.begin(), result.end(), '"'), result.end());
    return result;
  }
  catch (invalid_argument &e) {
    return 0;
  }
  catch (exception &e) {
    throw e;
  }
}

int ProcessParser::GetTotalThreads() {
  int result = 0;
  vector<string> _list = ProcessParser::GetPidList();
  for (const auto &pid:_list) {
    //getting every process and reading their number of their threads
    try {
      result += stoi(FetchValue(Path::basePath() + pid + Path::statusPath(), 1, "Threads"));
    }
    catch (exception &e) {
      continue;
    }
  }
  return result;
}

vector<string> ProcessParser::GetSysCpuPercent(string coreNumber) {
  // It is possible to use this method for selection of data for overall cpu or every core.
  // when nothing is passed "cpu" line is read
  // when, for example "0" is passed  -> "cpu0" -> data for first core is read
  try {
    return FetchValues(Path::basePath() + Path::statPath(), "cpu" + coreNumber);
  }
  catch (invalid_argument &e) {
    return vector<string>{};
  }
  catch (exception &e) {
    throw e;
  }
}

string ProcessParser::GetProcUser(string pid) {
  string result = "";
  try {
    result = FetchValue(Path::basePath() + pid + Path::statusPath(), 1, "Uid");

    ifstream stream = Util::getStream("/etc/passwd");
    string name = ("x:" + result);
    string line;
    // Searching for name of the user with selected UID
    while (getline(stream, line)) {
      if (line.find(name) != string::npos) {
        result = line.substr(0, line.find(":"));
        return result;
      }
    }
  }
  catch (runtime_error &e) {
    throw e;
  }

  catch (exception &e) {
    //  Don't forward the exception
  }
  return "";
}

string ProcessParser::GetCpuPercent(string pid) {
  string line;
  string value;
  float result;
  try {
    ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
    getline(stream, line);
    string str = line;
    istringstream buf(str);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end); // done!
    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = stof(ProcessParser::GetProcUpTime(pid));
    float stime = stof(values[14]);
    float cutime = stof(values[15]);
    float cstime = stof(values[16]);
    float starttime = stof(values[21]);
    float uptime = ProcessParser::GetSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    result = 100.0 * ((total_time / freq) / seconds);
  }
  catch (runtime_error &e) {
    throw e;
  }
  catch (exception &e) {
    //Ignore rest of the errors
  }

  return to_string(result);
}

float ProcessParser::GetSysActiveCpuTime(vector<string> values) {
  return (stof(values[kUser]) +
      stof(values[kNice]) +
      stof(values[kSystem]) +
      stof(values[kIrq]) +
      stof(values[kSoftIrq]) +
      stof(values[kSteal]) +
      stof(values[kGuest]) +
      stof(values[kGuestNice]));
}

float ProcessParser::GetSysIdleCpuTime(vector<string> values) {
  return (stof(values[kIdle]) + stof(values[kIoWait]));
}

float ProcessParser::GetSysRamPercent() {
  string line;
  string name1 = "MemAvailable:";
  string name2 = "MemFree:";
  string name3 = "Buffers:";

  string value;
  int result;
  float total_mem = 0;
  float free_mem = 0;
  float buffers = 0;
  try {
    ifstream stream = Util::getStream((Path::basePath() + Path::memInfoPath()));
    while (getline(stream, line)) {
      if (total_mem != 0 && free_mem != 0)
        break;
      if (line.compare(0, name1.size(), name1) == 0) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> values(beg, end);
        total_mem = stof(values[1]);
      }
      if (line.compare(0, name2.size(), name2) == 0) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> values(beg, end);
        free_mem = stof(values[1]);
      }
      if (line.compare(0, name3.size(), name3) == 0) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> values(beg, end);
        buffers = stof(values[1]);
      }
    }
  }
  catch (exception &e) {
    //Don't propogate, ignore the error
  }
  //calculating usage:
  return float(100.0 * (1 - (free_mem / (total_mem - buffers))));
}

string ProcessParser::PrintCpuStats(vector<string> values1, vector<string> values2) {
/*
Because CPU stats can be calculated only if you take measures in two different time,
this function has two parameters: two vectors of relevant values.
We use a formula to calculate overall activity of processor.
*/
  float activeTime = GetSysActiveCpuTime(values2) - GetSysActiveCpuTime(values1);
  float idleTime = GetSysIdleCpuTime(values2) - GetSysIdleCpuTime(values1);
  float totalTime = activeTime + idleTime;
  float result = 100.0 * (activeTime / totalTime);
  return to_string(result);
}

bool ProcessParser::IsPidExisting(string pid) {
  for (auto &exist_pid : GetPidList()) {
    if (exist_pid.compare(pid) == 0)
      return true;
  }
  return false;
}

