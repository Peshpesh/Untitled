#include "CSimulate.h"

CSimulate CSimulate::control;

CSimulate::CSimulate() {
  status = INACTIVE;
}

bool CSimulate::OnInit() {
  //
}

simstate CSimulate::getStatus() {
  return status;
}

void CSimulate::stopSim() {
  status = INACTIVE;
}

void CSimulate::OnTerminate() {
  //
}
