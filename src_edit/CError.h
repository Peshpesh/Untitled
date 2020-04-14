#ifndef _C_ERROR_H_
#define _C_ERROR_H_

#include <SDL.h>
#include <stdio.h>
#include <string>

#include "CUtil.h"

class CError {
public:
  static CError handler;

private:
  CError();
  const short NUMLOGS = 5;
  std::string errFile;

public:
  bool OnInit();
  void ReportSDLErr(const char* preinfo);
  void ReportErr(const char* info);
};
#endif
