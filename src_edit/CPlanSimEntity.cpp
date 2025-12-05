#include "CPlanSimEntity.h"

CPlanSimEntity::CPlanSimEntity() {
  sprtSrc = NULL;
  X = Y = Z = 0.0f;

  Flags = PlanEntityflags::HOLLOW;

  movedir = 'D';
  intentdir = 'D';
  intentmove = false;
  ismoving = false;

  Move = 0.0f;
  MaxMove = 6.5f;
}

void CPlanSimEntity::OnLoad() {
  sprtSrc = CEntity::getSrcTexture(Entities::groups::GLOBAL);
  spriteR = CEntityData::getEntityDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
  hitboxR = CEntityData::getHitboxDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
}

void CPlanSimEntity::OnLoop() {

  Move = MaxMove * CFPS::FPSControl.GetSpeedFactor();

  // if the entity is currently moving,
  // handle the movement in progress first
  if (ismoving) OnMove();

  // handle intention (request) to move
  if (intentmove) {
    intentmove = false;
    // only process intent to move if not already moving
    if (!ismoving) {
      // update where the entity is facing/moving
      movedir = intentdir;
      // check if the entity can move to the destination tile
      // if it can, then start moving that way
      // ... check if the move can be made
      CPlanTileAtt* thisTile = CPlanArea::control.GetTileAttZ((int)(X), (int)(Y), (int)(Z));
      CPlanTileAtt* destTile = NULL;
      bool canMove = false;
      switch (movedir) {
        case 'D': {
          // can we leave this tile?
          if (thisTile->barrier & BAR_D || thisTile->barrier & BAR_OUT_D) break;
          // can we go to the tile downward?
          destTile = CPlanArea::control.GetTileAttZ((int)(X), (int)(Y + TILE_SIZE), (int)(Z));
          if (destTile->solid || destTile->barrier & BAR_U || destTile->barrier & BAR_IN_U) break;
          canMove = true;
          break;
        }
        case 'U': {
          if (thisTile->barrier & BAR_U || thisTile->barrier & BAR_OUT_U) break;
          destTile = CPlanArea::control.GetTileAttZ((int)(X), (int)(Y - TILE_SIZE), (int)(Z));
          if (destTile->solid || destTile->barrier & BAR_D || destTile->barrier & BAR_IN_D) break;
          canMove = true;
          break;
        }
        case 'L': {
          if (thisTile->barrier & BAR_L || thisTile->barrier & BAR_OUT_L) break;
          destTile = CPlanArea::control.GetTileAttZ((int)(X - TILE_SIZE), (int)(Y), (int)(Z));
          if (destTile->solid || destTile->barrier & BAR_R || destTile->barrier & BAR_IN_R) break;
          canMove = true;
          break;
        }
        case 'R': {
          if (thisTile->barrier & BAR_R || thisTile->barrier & BAR_OUT_R) break;
          destTile = CPlanArea::control.GetTileAttZ((int)(X + TILE_SIZE), (int)(Y), (int)(Z));
          if (destTile->solid || destTile->barrier & BAR_L || destTile->barrier & BAR_IN_L) break;
          canMove = true;
          break;
        }
      }
      // ... turn on ismoving if tile is open
      // ... move toward the open tile
      if (canMove) {
        ismoving = true;
        OnMove();
      }
    }
  }
}

void CPlanSimEntity::OnMove() {
  switch (movedir) {
    case 'D': {
      // this is the Y that the entity will have once this current move is done
      float destY = ((int)(Y / TILE_SIZE) + 1) * TILE_SIZE;
      if (Move > destY - Y) {
        // if the move is more than the difference between
        // the current Y and the destination Y, then this current move will
        // complete---subtract the moved distance from the total move allowed
        // this loop
        Move -= destY - Y;
        Y = destY;
        ismoving = false;
      } else {
        // otherwise just move the entity as far as possible in its current move
        Y += Move;
        Move = 0.0f;
      }
    } break;
    case 'U': {
      // this is the Y that the entity will have once this current move is done
      float destY = (int)(Y / TILE_SIZE) * TILE_SIZE;
      if (Move > Y - destY) {
        // if the move is more than the difference between
        // the current Y and the destination Y, then this current move will
        // complete---subtract the moved distance from the total move allowed
        // this loop
        Move -= Y - destY;
        Y = destY;
        ismoving = false;
      } else {
        // otherwise just move the entity as far as possible in its current move
        Y -= Move;
        Move = 0.0f;
      }
    } break;
    case 'L': {
      float destX = (int)(X / TILE_SIZE) * TILE_SIZE;
      if (Move > X - destX) {
        Move -= X - destX;
        X = destX;
        ismoving = false;
      } else {
        X -= Move;
        Move = 0.0f;
      }
    } break;
    case 'R': {
      float destX = ((int)(X / TILE_SIZE) + 1) * TILE_SIZE;
      if (Move > destX - X) {
        Move -= destX - X;
        X = destX;
        ismoving = false;
      } else {
        X += Move;
        Move = 0.0f;
      }
    } break;
    default: break;
  }
}

bool CPlanSimEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  SDL_Rect sprFrame = {spriteR.x, spriteR.y, spriteR.w, spriteR.h};
  return CSurface::OnDraw(sprtSrc, &sprFrame, &dstWinPos);
}

void CPlanSimEntity::OnCleanup() {

}
