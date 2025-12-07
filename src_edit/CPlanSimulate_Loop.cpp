#include "CPlanSimulate.h"

void CPlanSimulate::OnLoop(const SDL_Point& m) {
  if (status == pvmsimulator::PLACE) {
    SDL_Point p = CCamera::CameraControl.GetCamRelPoint(m);
    hero.X = ((p.x / TILE_SIZE) - (p.x < 0)) * TILE_SIZE;
    hero.Y = ((p.y / TILE_SIZE) - (p.y < 0)) * TILE_SIZE;
  } else if (status == pvmsimulator::ACTIVE) {
    hero.OnLoop();
  }
}
