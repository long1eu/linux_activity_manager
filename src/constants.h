#include <string>
using namespace std;

const int PROCESS_LIST_SIZE = 10;

enum CPUStates {
  kUser = 1,
  kNice,
  kSystem,
  kIdle,
  kIoWait,
  kIrq,
  kSoftIrq,
  kSteal,
  kGuest,
  kGuestNice
};

class Path {

 public:
  Path() = delete;
  static string basePath() { return "/proc/"; }
  static string cmdPath() { return "/cmdline"; }
  static string statusPath() { return "/status"; }
  static string statPath() { return "stat"; }
  static string upTimePath() { return "uptime"; }
  static string memInfoPath() { return "meminfo"; }
  static string versionPath() { return "version"; }
};
