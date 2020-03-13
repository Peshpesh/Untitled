#include "CEntity.h"

void CEntity::OnMove(float MoveX, float MoveY) {
	Jumper = false;
	if (MoveX == 0 && MoveY == 0) return;
	// bool CanMove = true;

	// resolutions of pathfinders (in pixels)
	double NewX = 0;
	double NewY = 0;
	double Slope = 0;

	// Normalize movement by speed of the program loop
	// Ex: GSF = 1 for FPS = targetFPS. GSF < 1.0 when
	// the program runs at FPS > targetFPS.
	MoveX *= CFPS::FPSControl.GetSpeedFactor();
	MoveY *= CFPS::FPSControl.GetSpeedFactor();

	if (MoveX != 0) {
		if (MoveX >= 0) NewX = CFPS::FPSControl.GetSpeedFactor();
		else NewX = -CFPS::FPSControl.GetSpeedFactor();
	}
	if (MoveY != 0) {
		if (MoveY >= 0) NewY = CFPS::FPSControl.GetSpeedFactor();
		else NewY = -CFPS::FPSControl.GetSpeedFactor();
	}
	if (MoveX != 0 && MoveY != 0) {
		Slope = MoveY / MoveX;
		if (Slope < 0) Slope = -Slope;
		if (Slope > 1.0) {
			NewX /= Slope;
		}
		else {
			NewY *= Slope;
		}
	}

	while (true)
	{
		// if (Flags & ENTITY_FLAG_GHOST)
		// {
		// 	// We don't care about collisions, but we need to send events to other entities
		// 	PosValid((int)(X + NewX), (int)(Y + NewY), true);
		// 	X += NewX;
		// 	Y += NewY;
		// }

		Translate(NewX, NewY);

		MoveX -= NewX;
		MoveY -= NewY;
		if (NewX > 0 && MoveX < 0) NewX = 0;
		if (NewX < 0 && MoveX > 0) NewX = 0;
		if (NewY > 0 && MoveY < 0) NewY = 0;
		if (NewY < 0 && MoveY > 0) NewY = 0;
		if (MoveX == 0) NewX = 0;
		if (MoveY == 0) NewY = 0;
		if (MoveX == 0 && MoveY == 0) break;
		if (NewX == 0 && NewY == 0) break;
	}
}

void CEntity::Translate(double NewX, double NewY) {
	// NOTE: NewX, NewY params should be <= 1.0.
	int destXl = X + NewX + hitboxR.x;
	int destYt = Y + NewY + hitboxR.y;
	int destXr = destXl + hitboxR.w - 1;
	int destYb = destYt + hitboxR.h - 1;
	int srcXl = X + hitboxR.x;
	int srcYt = Y + hitboxR.y;
	int srcXr = srcXl + hitboxR.w - 1;
	int srcYb = srcYt + hitboxR.h - 1;
	// int pushY = 0;
	Grounded = false;
  int push_Y = getVertDeflect(NewX, NewY);

	// Now, let's see if the destination hitbox will collide with
	// something that will stop this entity.
	if (push_Y != 0) {
		if (CheckPathXY(destXl, destXr, srcYt + push_Y, srcYb + push_Y)) {
			// The entity can move in X and Y. The entity is being "pushed"
			// in Y by a sloping surface, which means that we also have checked
			// for stoppages in the Y direction and found none.
			X += NewX;
			Y += push_Y;
			if (push_Y < 0) {
				Jumper = true;
				Grounded = true;
				if (NewY > 0)	SpeedY = 0;
			}	else {
				if (NewY < 0)	SpeedY = 0;
			}
		}	else {
			// The entity CANNOT move in X. The queried movement in X
			// required a change in Y, so we must check if the entity can move in only Y
			// now that it is apparent it cannot move in X.
			SpeedX = 0;
			if (CheckPathXY(srcXl, srcXr, destYt, destYb)) Y += NewY;
			else {
				SpeedY = 0;
				if (NewY > 0) {
					Jumper = true;
					Grounded = true;
				}
			}
		}
	}	else {
		// If there is no push in Y, then we can just check for
		// if movement is possible in X, and then in Y.
		if (CheckPathXY(destXl, destXr, srcYt, srcYb)) X += NewX;
		else SpeedX = 0;

		if (CheckPathXY(srcXl, srcXr, destYt, destYb)) {
      Y += NewY;
    }	else {
			SpeedY = 0;
			if (NewY > 0) {
				Jumper = true;
				Grounded = true;
			}
		}
	}
}

bool CEntity::CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb) {
	bool pathclear = true;
  SDL_Point topleft = {destXl, destYt};
  SDL_Point botright = {destXr, destYb};
	for (int i = 0; i < EntityList.size(); i++) {
		if (CollEntity(EntityList[i], topleft, botright) && pathclear) {
			pathclear = false;
		}
	}
  if (!pathclear) return false;
	for (int tY = destYt / TILE_SIZE; tY <= destYb / TILE_SIZE; tY++) {
		for (int tX = destXl / TILE_SIZE; tX <= destXr / TILE_SIZE; tX++) {
      SDL_Point tilepos = {tX, tY};
      if (!CollTile(tilepos, topleft, botright)) return false;
    }
	}
	return true;
}
