#include "CMode.h"

app_module CMode::handle = APP_MODE_TITLE;

CMode::CMode() {
  //
}

void CMode::changeFlag(app_module flag) {
  handle = flag;
}

bool CMode::isFlagOn(app_module flag) {
  return (flag == handle);
}
