#ifndef _C_LOCATION_H_
#define _C_LOCATION_H_

#include <string>

namespace location {
  enum {
    DEFAULT = 0,
    YRAI_HOME = 1,
    YRAI = 2,
    YRAI_OUTSKIRTS = 3,
  };
  const short num = 4;
  const char* const abbrname[] = {
    "default",
    "yraihome",
    "yrai",
    "yraiout",
  };
  const char* const fullname[] = {
    "The Debug Region",
    "Home",
    "Yrai",
    "Yrai -- Outskirts",
  };
};

class CLocation {
  CLocation();
public:
  static std::string getAbbrname(const int& location);
  static std::string getFullname(const int& location);
};

#endif
