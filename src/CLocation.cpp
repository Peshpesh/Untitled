#include "CLocation.h"

CLocation::CLocation() {
  //
}

std::string CLocation::getAbbrname(const int& location) {
  if (location < 0 || location >= location::num) {
    return "";
  }
  return location::abbrname[location];
}

std::string CLocation::getFullname(const int& location) {
  if (location < 0 || location >= location::num) {
    return "";
  }
  return location::fullname[location];
}
