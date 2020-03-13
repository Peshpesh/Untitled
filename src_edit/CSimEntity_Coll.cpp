#include "CSimEntity.h"

int CSimEntity::getVertDeflect(const double& NewX, const double& NewY) {
  // First, let's see what lies ahead in terms of the map.
  // These two conditional blocks handle sloping grounds.
  // If necessary, a deflection (push) amount is assigned to pushY.
  // This value is such that adding it to the intended Y position
  // will yield a valid Y position on the map (use this for entities,
  // tiles that might block movement, etc.). The pushY term is basically
  // a "correction" term in Y, which must be satisfied if this entity is to move
  // horizontally.
  int destXl = X + NewX + hitboxR.x;
  int destXr = destXl + hitboxR.w - 1;
	int srcYt = Y + hitboxR.y;
	int srcYb = srcYt + hitboxR.h - 1;

  int push_Y = 0;
  CTile* Tile = NULL;
  int Y_offset = 0; // offset of a position from the top of the containing tile
                    // OR, "where on the tile (in Y, from 0 to 31) is this point?"

  if (NewX > 0.0)	{ // Moving right
    if ((Tile = CArea::control.GetTile(destXr, srcYb)) == NULL) return 0;
    Y_offset = srcYb - ((srcYb / TILE_SIZE) * TILE_SIZE);
    if (Tile->CollID == SOLID_U_BL_MR || (Tile->CollID == SOLID_U_ML_TR && Y_offset < TILE_SIZE / 2)) {
      push_Y = CollGround(Tile->CollID, destXr % TILE_SIZE, Y_offset);
    }
    if (push_Y == 0) {
      if ((Tile = CArea::control.GetTile(destXr, srcYt)) == NULL) return 0;
      Y_offset = srcYt - ((srcYt / TILE_SIZE) * TILE_SIZE);
      if (Tile->CollID == SOLID_A_TL_MR || (Tile->CollID == SOLID_A_ML_BR && Y_offset >= TILE_SIZE / 2)) {
        push_Y = CollGround(Tile->CollID, destXr % TILE_SIZE, Y_offset);
      }
    }
  } else if (NewX < 0.0) {	// Moving left
    Y_offset = srcYb - ((srcYb / TILE_SIZE) * TILE_SIZE);
    if ((Tile = CArea::control.GetTile(destXl, srcYb)) == NULL) return 0;
    if (Tile->CollID == SOLID_U_ML_BR || (Tile->CollID == SOLID_U_TL_MR && Y_offset < TILE_SIZE / 2)) {
      push_Y = CollGround(Tile->CollID, destXl % TILE_SIZE, Y_offset);
    }
    if (push_Y == 0) {
      if ((Tile = CArea::control.GetTile(destXl, srcYt)) == NULL) return 0;
      Y_offset = srcYt - ((srcYt / TILE_SIZE) * TILE_SIZE);
      if (Tile->CollID == SOLID_A_ML_TR || (Tile->CollID == SOLID_A_BL_MR && Y_offset >= TILE_SIZE / 2)) {
        push_Y = CollGround(Tile->CollID, destXl % TILE_SIZE, Y_offset);
      }
    }
  }
  return push_Y;
}

int CSimEntity::getHorzDeflect(const double& NewX, const double& NewY) {
  // If the entity is to move vertically (i.e., as given from NewY),
  // will it have to be deflected horizontally due to steep slopes?

  // If necessary, a deflection (push) amount is assigned to push_X.
  // In other words, push_X represents the horizontal deflection required
  // if the entity is to move vertically as requested by NewY. Without the
  // deflection, the entity's hitbox would translate through a steep slope.

  // For now, let us only consider the deflection necessary for
  // entities of downward movement (i.e., ignoring steep-sloped ceilings)
  int push_X = 0;
  if (NewY > 0.0) { // moving down
    int srcXl = X + hitboxR.x;
    int srcXr = srcXl + hitboxR.w - 1;
    int destYt = Y + NewY + hitboxR.y;
    int destYb = destYt + hitboxR.h - 1;

    CTile* Tile = NULL;
    int X_tilerel = 0; // X relative to containing tile's X (left side)

    // check bottom-left corner of hitbox
    if ((Tile = CArea::control.GetTile(srcXl, destYb)) == NULL) return 0;
    X_tilerel = srcXl % TILE_SIZE;
    if ((Tile->CollID == SOLID_U_LT_MB && X_tilerel < TILE_SIZE / 2) || Tile->CollID == SOLID_U_MT_RB) {
      push_X = CollWall(Tile->CollID, X_tilerel, destYb % TILE_SIZE);
    }
    if (!push_X) { // check bottom-right corner of hitbox
      if ((Tile = CArea::control.GetTile(srcXr, destYb)) == NULL) return 0;
      X_tilerel = srcXr % TILE_SIZE;
      if ((Tile->CollID == SOLID_U_RT_MB && X_tilerel >= TILE_SIZE / 2) || Tile->CollID == SOLID_U_MT_LB) {
        push_X = CollWall(Tile->CollID, X_tilerel, destYb % TILE_SIZE);
      }
    }
  }
  return push_X;
}

// Returns true (non-zero) if the queried tile-relative X, Y intersect solid ground.
int CSimEntity::CollGround(const int& collID, const int& X_offset, const int& Y_offset) {
	bool solidabove = false;
	int Yo = 0;
	double slope = 0.5;

	switch (collID) {
		case SOLID_U_BL_MR:	Yo = TILE_SIZE - 1; 																				break;
		case SOLID_U_ML_TR:	Yo = (TILE_SIZE / 2) - 1; 																	break;
		case SOLID_U_TL_MR: 													slope = -0.5; 										break;
		case SOLID_U_ML_BR: Yo = TILE_SIZE / 2; 			slope = -0.5; 										break;
		case SOLID_A_BL_MR: Yo = TILE_SIZE - 1; 										solidabove = true; 	break;
		case SOLID_A_ML_TR:	Yo = (TILE_SIZE / 2) - 1; 							solidabove = true; 	break;
		case SOLID_A_TL_MR: 													slope = -0.5; solidabove = true; 	break;
		case SOLID_A_ML_BR: Yo = TILE_SIZE / 2; 			slope = -0.5; solidabove = true; 	break;
		default: break;
	}

	int Yl = Yo - (int)(slope * X_offset);
	int Ypush = 0;
	if (!solidabove && Y_offset >= Yl) {
		Ypush = Yl - Y_offset - 1;
	}
	else if (solidabove && Y_offset <= Yl) {
		Ypush = Yl - Y_offset + 1;
	}
	return Ypush;
}

int CSimEntity::CollWall(const int& collID, const int& X_offset, const int& Y_offset) {
	int slope = 2;
  int Xo = 0;
	switch (collID) {
		case SOLID_U_LT_MB:	slope = -slope;                     break;
		case SOLID_U_MT_RB: Xo = TILE_SIZE / 2; slope = -slope; break;
		case SOLID_U_RT_MB: Xo = TILE_SIZE - 1;                 break;
		case SOLID_U_MT_LB: Xo = (TILE_SIZE / 2) - 1;           break;
		default: break;
	}

  int X = Xo - (Y_offset / slope);
  int push_X = 0;
  if (slope < 0) {
    if (X_offset <= X) {
      push_X = X - X_offset + 1;
    }
  } else {
    if (X_offset >= X) {
      push_X = X - X_offset - 1;
    }
  }
	return push_X;
}

bool CSimEntity::CollTile(const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br) {
  CTile* Tile = CArea::control.GetTile(tilepos.x * TILE_SIZE, tilepos.y * TILE_SIZE);
  // Check if the collided tile is entirely solid.
  // If it is, entity can't move to destination.
  // if (Tile == NULL) SDL_Delay(1000);
  if (Tile == NULL || Tile->CollID == SOLID_ALL) return false;

  // Check if the collided tile is partially solid.
  // If it is, the entity MIGHT be able to move.
  bool retval = true;
  if (Tile->CollID != SOLID_NONE) {
    // Cases where colliding with a partially-filled tile
    // should prevent movement:
    // 1. The hitbox intersects with a half-filled tile (rectangle)
    // 2. The top of the hitbox intersects with the
    // 		"lowest height" of a sloping roof, or the bottom of a sloping floor
    // 3. The bottom of the hitbox intersects with the
    //		"highest height" of a sloping floor, or the top of a sloping roof
    // 4.	The left/right sides of the hitbox intersect with a
    //		sloped floor or roof
    // 5. The internal hitbox (non-side) somehow negotiates
    //		an intersection

    bool l_side = (tilepos.x == tl.x / TILE_SIZE);
    bool r_side = (tilepos.x == br.x / TILE_SIZE);
    bool t_side = (tilepos.y == tl.y / TILE_SIZE);
    bool b_side = (tilepos.y == br.y / TILE_SIZE);

    if (!(l_side || r_side || t_side || b_side)) retval = false;
    else {
      switch (Tile->CollID) {
        case SOLID_U_BL_MR: { // floor, +slope
          if (!b_side) retval = false;
          else if (br.y % TILE_SIZE >= TILE_SIZE / 2) {
            if (!r_side) retval = false;
            else if (CollGround(SOLID_U_BL_MR, br.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          }
          break;
        }
        case SOLID_U_ML_TR: { // floor, +slope
          if (!b_side || !r_side) retval = false;
          else if (CollGround(SOLID_U_ML_TR, br.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          break;
        }
        case SOLID_U_TL_MR: { // floor, -slope
          if (!b_side || !l_side) retval = false;
          else if (CollGround(SOLID_U_TL_MR, tl.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          break;
        }
        case SOLID_U_ML_BR: { // floor, -slope
          if (!b_side) retval = false;
          else if (br.y % TILE_SIZE >= TILE_SIZE / 2) {
            if (!l_side) retval = false;
            else if (CollGround(SOLID_U_ML_BR, tl.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          }
          break;
        }
        case SOLID_A_BL_MR: { // ceiling, +slope
          if (!t_side || !l_side) retval = false;
          else if (CollGround(SOLID_A_BL_MR, tl.x % TILE_SIZE, tl.y % TILE_SIZE)) retval = false;
          break;
        }
        case SOLID_A_ML_TR: { // ceiling, +slope
          if (!t_side) retval = false;
          else if (tl.y % TILE_SIZE < TILE_SIZE / 2) {
            if (!l_side) retval = false;
            else if (CollGround(SOLID_A_ML_TR, tl.x % TILE_SIZE, tl.y % TILE_SIZE)) retval = false;
          }
          break;
        }
        case SOLID_A_TL_MR: { // ceiling, -slope
          if (!t_side) retval = false;
          else if (tl.y % TILE_SIZE < TILE_SIZE / 2) {
            if (!r_side) retval = false;
            else if (CollGround(SOLID_A_TL_MR, br.x % TILE_SIZE, tl.y % TILE_SIZE)) retval = false;
          }
          break;
        }
        case SOLID_A_ML_BR: { // ceiling, -slope
          if (!t_side || !r_side) retval = false;
          else if (CollGround(SOLID_A_ML_BR, br.x % TILE_SIZE, tl.y % TILE_SIZE)) retval = false;
          break;
        }
        case SOLID_U_LT_MB: { // floor/wall, --slope
          if (!l_side) retval = false;
          else if (tl.x % TILE_SIZE < TILE_SIZE / 2) {
            if (!b_side) retval = false;
            else if (CollWall(SOLID_U_LT_MB, tl.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          }
          break;
        }
        case SOLID_U_MT_RB: { // floor/wall, --slope
          if (!l_side || !b_side) retval = false;
          else if (CollWall(SOLID_U_MT_RB, tl.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          break;
        }
        case SOLID_U_RT_MB: { // floor/wall, ++slope
          if (!r_side) retval = false;
          else if (br.x % TILE_SIZE >= TILE_SIZE / 2) {
            if (!b_side) retval = false;
            else if (CollWall(SOLID_U_RT_MB, br.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          }
          break;
        }
        case SOLID_U_MT_LB: { // floor/wall, ++slope
          if (!r_side || !b_side) retval = false;
          else if (CollWall(SOLID_U_MT_LB, br.x % TILE_SIZE, br.y % TILE_SIZE)) retval = false;
          break;
        }
        case SOLID_HALF_TH: {
          if (!t_side) retval = false;
          else if (tl.y % TILE_SIZE < TILE_SIZE / 2) retval = false;
          break;
        }
        case SOLID_HALF_BH: {
          if (!b_side) retval = false;
          else if (br.y % TILE_SIZE >= TILE_SIZE / 2) retval = false;
          break;
        }
        default: retval = false; break;
      }
    }
  }
  return retval;
}
