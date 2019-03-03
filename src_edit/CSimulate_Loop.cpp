#include "CSimulate.h"

void CSimulate::OnLoop(const SDL_Point* m) {
  if (status == PLACE) {
    SDL_Point p = CCamera::CameraControl.GetCamRelPoint(*m);
    hero.X = p.x;
    hero.Y = p.y;
  } else if (status == ACTIVE) {
    hero.OnLoop();
  }
}
