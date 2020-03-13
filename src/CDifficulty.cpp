#include "CDifficulty.h"

Difficulty CDiff::d = NORMAL;

CDiff::CDiff() {
  //
}

Difficulty CDiff::getDiff() {
  return d;
}

void CDiff::setDiff(const Difficulty& d) {
  if (CDiff::d != d) CDiff::d = d;
}
