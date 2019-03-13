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

bool CSimEntity::CollTile(const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br) {
  CTile* Tile = CArea::control.GetTile(tilepos.x * TILE_SIZE, tilepos.y * TILE_SIZE);
  // Check if the collided tile is entirely solid.
  // If it is, entity can't move to destination.
  // if (Tile == NULL) SDL_Delay(1000);
  if (Tile == NULL || Tile->CollID == SOLID_ALL) return false;

  // Check if the collided tile is partially solid.
  // If it is, the entity MIGHT be able to move.
  if (Tile->CollID != SOLID_NONE) {
    // Cases where colliding with a partially-filled tile
    // should prevent movement:
    // 1. The top of the hitbox intersects with the
    // 		"lowest height" of a sloping roof, or the bottom of a sloping floor
    //    ->> This is handled by CollTile_top
    // 2. The bottom of the hitbox intersects with the
    //		"highest height" of a sloping floor, or the top of a sloping roof
    //    ->> This is handled by CollTile_bot
    // 3.	The left/right sides of the hitbox intersect with a
    //		sloped floor or roof
    // 4. The internal hitbox (non-side) somehow negotiates
    //		an intersection

    // Handling cases #3 and #4
    // There are no exceptions that allow the entity to move if
    // the colliding sector is not from the top or bottom of the hitbox.
    if ((tilepos.y != tl.y / TILE_SIZE) && (tilepos.y != br.y / TILE_SIZE)) return false;

    // Handling case #1:
    if (tilepos.y == tl.y / TILE_SIZE && !CollTile_top(Tile->CollID, tilepos, tl, br)) return false;

    // Handling case #2:
    if (tilepos.y == br.y / TILE_SIZE && !CollTile_bot(Tile->CollID, tilepos, tl, br)) return false;
  }
  return true;
}

bool CSimEntity::CollTile_top(const int& collID, const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br) {
  // If the current tile is associated with the top of the hitbox...
  if (collID == SOLID_A_ML_BR) {
    if (tilepos.x != br.x / TILE_SIZE) return false;
    else if (CollGround(collID, br.x % TILE_SIZE, tl.y % TILE_SIZE)) return false;
  }
  else if (collID == SOLID_A_BL_MR) {
    // These sloped roof tiles occupy space from Y = [16, 31] relative to
    // the tile.
    // This entity can't move to the destination. The lowest height of
    // the colliding tile is the bottom of the tile itself.
    if (tilepos.x != tl.x / TILE_SIZE) return false;
    else if (CollGround(collID, tl.x % TILE_SIZE, tl.y % TILE_SIZE)) return false;
  }
  else if (collID == SOLID_A_TL_MR) {
    // These sloped roof tiles occupy space from Y = [0, 15] relative to
    // the tile.
    // IF the top of the hitbox destination collides with the space
    // occupied by the sloping roof, then the entity cannot move to
    // the destination.
    if (tilepos.x != br.x / TILE_SIZE) {
      if (tl.y % TILE_SIZE < TILE_SIZE / 2) return false;
    }
    else if (CollGround(collID, br.x % TILE_SIZE, tl.y % TILE_SIZE)) return false;
  }
  else if (collID == SOLID_A_ML_TR) {
    // These sloped roof tiles occupy space from Y = [0, 15] relative to
    // the tile.
    // IF the top of the hitbox destination collides with the space
    // occupied by the sloping roof, then the entity cannot move to
    // the destination.
    if (tilepos.x != tl.x / TILE_SIZE) {
      if (tl.y % TILE_SIZE < TILE_SIZE / 2) return false;
    }
    else if (CollGround(collID, tl.x % TILE_SIZE, tl.y % TILE_SIZE)) return false;
  }
  else {
    // Hitbox top collides with a sloped floor. Maybe the tile's underside.
    if (tilepos.x != tl.x / TILE_SIZE && tilepos.x != br.x / TILE_SIZE) {
      if (collID == SOLID_U_ML_TR || collID == SOLID_U_TL_MR) return false;
      else {
        int Yrel = br.y - ((tl.y / TILE_SIZE) * TILE_SIZE);
        if (br.y - ((tl.y / TILE_SIZE) * TILE_SIZE) >= TILE_SIZE / 2) return false;
      }
    }
    else {
      int Yrel = br.y - ((tl.y / TILE_SIZE) * TILE_SIZE);
      if (tilepos.x == tl.x / TILE_SIZE) {
        if (CollGround(collID, tl.x % TILE_SIZE, Yrel)) return false;
      }
      if (tilepos.x == br.x / TILE_SIZE) {
        if (CollGround(collID, br.x % TILE_SIZE, Yrel)) return false;
      }
    }
  }
  return true;
}

bool CSimEntity::CollTile_bot(const int& collID, const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br) {
  // If the current tile is associated with the bottom of hitbox...
  if (collID == SOLID_U_ML_BR) {
    if (tilepos.x != tl.x / TILE_SIZE) {
      if (br.y % TILE_SIZE >= TILE_SIZE / 2) return false;
    }
    else if (CollGround(collID, tl.x % TILE_SIZE, br.y % TILE_SIZE)) return false;
  }
  else if (collID == SOLID_U_BL_MR) {
    if (tilepos.x != br.x / TILE_SIZE) {
      if (br.y % TILE_SIZE >= TILE_SIZE / 2) return false;
    }
    else if (CollGround(collID, br.x % TILE_SIZE, br.y % TILE_SIZE)) return false;
  }
  else if (collID == SOLID_U_TL_MR) {
    if (tilepos.x != tl.x / TILE_SIZE) return false;
    else if (CollGround(collID, tl.x % TILE_SIZE, br.y % TILE_SIZE)) return false;
  }
  else if (collID == SOLID_U_ML_TR) {
    if (tilepos.x != br.x / TILE_SIZE) return false;
    else if (CollGround(collID, br.x % TILE_SIZE, br.y % TILE_SIZE)) return false;
  }
  else {
    // Hitbox bottom collides with a sloped roof. Maybe the tile's top.
    if (tilepos.x != tl.x / TILE_SIZE && tilepos.x != br.x / TILE_SIZE) {
      if (collID == SOLID_A_ML_BR || collID == SOLID_A_BL_MR) return false;
      else if (br.y % TILE_SIZE < TILE_SIZE / 2) return false;
    }
    else {
      if (tilepos.x == tl.x / TILE_SIZE) {
        if (CollGround(collID, tl.x % TILE_SIZE, br.y % TILE_SIZE)) return false;
      }
      if (tilepos.x == br.x / TILE_SIZE) {
        if (CollGround(collID, br.x % TILE_SIZE, br.y % TILE_SIZE)) return false;
      }
    }
  }
  return true;
}
