#include "CError.h"

CError CError::handler;

CError::CError() {
  errFile = "error.0.log";
}

bool CError::OnInit() {
  // Cycle logs back. Existing log indices increase by 1.
  // The oldest log is deleted.
  for (int i = NUMLOGS - 1; i > 0; i--) {
    std::string newname = "error." + CUtil::intToStr(i)   + ".log";
    std::string oldname = "error." + CUtil::intToStr(i-1) + ".log";

    FILE* ef = fopen(oldname.c_str(), "r");
    if (ef != NULL) {
      // If the the log exists, remove any existing destination file
      // and replace it with the log
      fclose(ef);
      remove(newname.c_str());
      rename(oldname.c_str(), newname.c_str());
    } else {
      // If the the log doesn't exist, then make a new one
      // at the destination
      FILE* ef = fopen(newname.c_str(), "w");
      fclose(ef);
    }
  }
  FILE* ef = fopen(errFile.c_str(), "w");
  fclose(ef);

  return true;
}

void CError::ReportSDLErr(const char* preinfo) {
  printf("%s -> %s\n", preinfo, SDL_GetError());

  // record error to log for review
  FILE* ef = fopen(errFile.c_str(), "a");
  fprintf(ef, "%s -> %s\n", preinfo, SDL_GetError());
  fclose(ef);

  SDL_ClearError();
}

void CError::ReportErr(const char* info) {
  printf("%s\n", info);

  // record error to log for review
  FILE* ef = fopen(errFile.c_str(), "a");
  fprintf(ef, "%s\n", info);
  fclose(ef);
}
