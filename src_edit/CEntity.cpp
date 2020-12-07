#include "CEntity.h"

std::vector<EntityTexInfo> CEntity::textureList;
std::vector<CEntity>       CEntity::entityList;
std::vector<CPlanEntity>   CEntity::entList_back;
std::vector<CPlanEntity>   CEntity::entList_front;
const bool* CEntity::planview = NULL;

namespace {
  const SDL_Point* hb_nocol = &palette::green;
  const SDL_Point* hb_col   = &palette::red;
  const std::string io_path = "../data/maps/";
  const std::string io_ext = ".ent";
  const std::string io_ext_pv = ".pve";
}

CEntity::CEntity(int group, int entity, const SDL_Point* m) {
  sprtSrc   = getSrcTexture(group);
  group_ID  = group;
  entity_ID = entity;
  srcR      = CEntityData::getEntityDims(group, entity);
  hitR      = CEntityData::getHitboxDims(group, entity);
  // dstP      = CCamera::CameraControl.GetCamRelPoint(*m);
  dstP      = *m;
  coll      = false;
}

bool CEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(dstP);
  return CSurface::OnDraw(sprtSrc, &srcR, &dstWinPos);
}

bool CEntity::OnRenderHitbox() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(dstP);
  SDL_Rect dstR = {dstWinPos.x + hitR.x, dstWinPos.y + hitR.y, hitR.w, hitR.h};
  return CAsset::drawBox(&dstR, coll ? hb_col : hb_nocol);
}

bool CEntity::Collides(const SDL_Point& oP, const SDL_Rect& oR) {
  // positions of sides of hitbox passed into function
  int oXl = oP.x + oR.x;
  int oXr = oXl + oR.w - 1;
  int oYt = oP.y + oR.y;
  int oYb = oYt + oR.h - 1;

  // positions of sides of hitbox from THIS entity
  int Xl = dstP.x + hitR.x;
  int Xr = Xl + hitR.w - 1;
  int Yt = dstP.y + hitR.y;
  int Yb = Yt + hitR.h - 1;

  if (Yb < oYt) return false;
  if (oYb < Yt) return false;
  if (Xr < oXl) return false;
  if (oXr < Xl) return false;

  return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

CPlanEntity::CPlanEntity(int group, int entity, const int& X, const int& Y, const short& Z) {
  sprtSrc   = CEntity::getSrcTexture(group);
  group_ID  = group;
  ID        = entity;
  srcR      = CEntityData::getEntityDims(group, entity);
  hitR      = CEntityData::getHitboxDims(group, entity);
  coll      = false;
  this->X   = X;
  this->Y   = Y;
  this->Z   = Z;

  Y_base    = Y + srcR.h;
  // SDL_Point dstP = CCamera::CameraControl.GetCamRelPoint(*m);
  // Y_base = CEntityData::getYBase(group_ID, decor_ID, Y, tempScn.srcR.h);
}

bool CPlanEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  dstWinPos.y -= (Z * TILE_SIZE);
  return CSurface::OnDraw(sprtSrc, &srcR, &dstWinPos);
}

bool CPlanEntity::OnRenderHitbox() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  dstWinPos.y -= (Z * TILE_SIZE);
  SDL_Rect dstR = {dstWinPos.x + hitR.x, dstWinPos.y + hitR.y, hitR.w, hitR.h};
  return CAsset::drawBox(&dstR, coll ? hb_col : hb_nocol);
}

bool CPlanEntity::Collides(const SDL_Point& oP, const SDL_Rect& oR) {
  // positions of sides of hitbox passed into function
  int oXl = oP.x + oR.x;
  int oXr = oXl  + oR.w - 1;
  int oYt = oP.y + oR.y;
  int oYb = oYt  + oR.h - 1;

  // positions of sides of hitbox from THIS entity
  int Xl = X  + hitR.x;
  int Xr = Xl + hitR.w - 1;
  int Yt = Y  + hitR.y;
  int Yb = Yt + hitR.h - 1;

  if (Yb < oYt) return false;
  if (oYb < Yt) return false;
  if (Xr < oXl) return false;
  if (oXr < Xl) return false;

  return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool CEntity::OnInit() {
  entityList.clear();
  entList_back.clear();
  entList_front.clear();
  purgeStaleTextures();
  textureList.clear();

  if (loadTexInfo(Entities::groups::GLOBAL) == NULL) {
    return false;
  }

  return true;
}

void CEntity::CheckCollide() {
  if (!*planview) {
    for (int i = 0; i < entityList.size(); i++) entityList[i].coll = false;

    for (int i = 0; i < entityList.size(); i++) {
      if (!entityList[i].coll) {
        for (int j = 0; j < entityList.size(); j++) {
          if (i == j) continue;
          if (entityList[i].Collides(entityList[j].dstP, entityList[j].hitR)) {
            entityList[i].coll = true;
            entityList[j].coll = true;
            break;
          }
        }
      }
    }
  } else {
    for (int i = 0; i < entList_back.size(); i++)  entList_back[i].coll  = false;
    for (int i = 0; i < entList_front.size(); i++) entList_front[i].coll = false;

    // Check each background entity
    for (int i = 0; i < entList_back.size(); i++) {
      if (!entList_back[i].coll) {
        for (int j = 0; j < entList_back.size(); j++) {
          if (i == j) continue;
          if (entList_back[i].Z != entList_back[j].Z) continue;
          SDL_Point dstP;
          dstP.x = entList_back[j].X;
          dstP.y = entList_back[j].Y;
          if (entList_back[i].Collides(dstP, entList_back[j].hitR)) {
            entList_back[i].coll = true;
            entList_back[j].coll = true;
          }
        }
        // Check is background entities collide with foreground (prob shouldn't happen)
        for (int j = 0; j < entList_front.size(); j++) {
          if (entList_back[i].Z != entList_front[j].Z) continue;
          SDL_Point dstP;
          dstP.x = entList_front[j].X;
          dstP.y = entList_front[j].Y;
          if (entList_back[i].Collides(dstP, entList_front[j].hitR)) {
            entList_back[i].coll  = true;
            entList_front[j].coll = true;
          }
        }
      }
    }

    // Check each foreground entity
    for (int i = 0; i < entList_front.size(); i++) {
      if (!entList_front[i].coll) {
        for (int j = 0; j < entList_front.size(); j++) {
          if (i == j) continue;
          if (entList_front[i].Z != entList_front[j].Z) continue;
          SDL_Point dstP;
          dstP.x = entList_front[j].X;
          dstP.y = entList_front[j].Y;
          if (entList_front[i].Collides(dstP, entList_front[j].hitR)) {
            entList_front[i].coll = true;
            entList_front[j].coll = true;
          }
        }
      }
    }
  }
}

bool CEntity::OnLoad(const char* fname) {
  std::string filePath = "";
  if (!*planview) filePath = io_path + fname + io_ext;
  else /*......*/ filePath = io_path + fname + io_ext_pv;

  FILE* FileHandle = fopen(filePath.c_str(), "rb");

  if (FileHandle == NULL)  {
    CInform::InfoControl.pushInform("---CENTITY.OnLoad---\nfailed to open file");
    return false;
  }

  entityList.clear();
  entList_back.clear();
  entList_front.clear();

  if (!*planview) {
    int N;
    fread(&N, sizeof(int), 1, FileHandle);
    for (int i = 0; i < N; i++) {
      // read entity info
      int entry[4];
      fread(entry, sizeof(int), sizeof(entry)/sizeof(entry[0]), FileHandle);
      const int group_ID = entry[0];
      if (!isTextureLoaded(group_ID)) loadTexInfo(group_ID);
      const int entity_ID = entry[1];
      const SDL_Point dstP = {entry[2], entry[3]};
      CEntity newEntity(group_ID, entity_ID, &dstP);
      entityList.push_back(newEntity);
    }
  } else {
    int N_back, N_front;
    fread(&N_back,  sizeof(int), 1, FileHandle);
    fread(&N_front, sizeof(int), 1, FileHandle);

    for (int i = 0; i < N_back + N_front; i++) {
      int group, ID, X, Y;
      short Z;
      fread(&group, sizeof(int),   1, FileHandle);
      fread(&ID,    sizeof(int),   1, FileHandle);
      fread(&X,     sizeof(int),   1, FileHandle);
      fread(&Y,     sizeof(int),   1, FileHandle);
      fread(&Z,     sizeof(short), 1, FileHandle);

      if (!isTextureLoaded(group)) loadTexInfo(group);

      CPlanEntity tempEnt(group, ID, X, Y, Z);

      if (i < N_back) entList_back.push_back(tempEnt);
      else entList_front.push_back(tempEnt);
    }
  }

  fclose(FileHandle);
  return true;
}

bool CEntity::OnSave(const char* fname) {
  std::string filePath = "";
  if (!*planview) filePath = io_path + fname + io_ext;
  else /*......*/ filePath = io_path + fname + io_ext_pv;
  FILE* FileHandle = fopen(filePath.c_str(), "wb");

  if (FileHandle == NULL)  {
    CInform::InfoControl.pushInform("---CENTITY.OnSave---\nfailed to open new file");
    return false;
  }

  if (!*planview) {
    const int N = entityList.size();
    fwrite(&N, sizeof(int), 1, FileHandle);
    for (int i = 0; i < entityList.size(); i++) {
      // Output entity info
      int entry[] = {
        entityList[i].group_ID,
        entityList[i].entity_ID,
        entityList[i].dstP.x,
        entityList[i].dstP.y
      };
      fwrite(entry, sizeof(int), sizeof(entry)/sizeof(entry[0]), FileHandle);
    }
  } else {
    const int N_back  = entList_back.size();
    const int N_front = entList_front.size();

    fwrite(&N_back,  sizeof(int), 1, FileHandle);
    fwrite(&N_front, sizeof(int), 1, FileHandle);

    for (int i = 0; i < N_back; i++) {
      fwrite(&entList_back[i].group_ID,  sizeof(int),   1, FileHandle);
      fwrite(&entList_back[i].ID,        sizeof(int),   1, FileHandle);
      fwrite(&entList_back[i].X,         sizeof(int),   1, FileHandle);
      fwrite(&entList_back[i].Y,         sizeof(int),   1, FileHandle);
      fwrite(&entList_back[i].Z,         sizeof(short), 1, FileHandle);
    }

    for (int i = 0; i < N_front; i++) {
      fwrite(&entList_front[i].group_ID, sizeof(int),   1, FileHandle);
      fwrite(&entList_front[i].ID,       sizeof(int),   1, FileHandle);
      fwrite(&entList_front[i].X,        sizeof(int),   1, FileHandle);
      fwrite(&entList_front[i].Y,        sizeof(int),   1, FileHandle);
      fwrite(&entList_front[i].Z,        sizeof(short), 1, FileHandle);
    }
  }

  fclose(FileHandle);
  return true;
}

bool CEntity::isGroupUsed(const int& group) {
  for (int i = 0; i < entityList.size(); i++) {
    if (group == entityList[i].group_ID) return true;
  }
  return false;
}

bool CEntity::isEntityUsed(const int& group, const int& entity) {
  for (int i = 0; i < entityList.size(); i++) {
    if (group == entityList[i].group_ID && entity == entityList[i].entity_ID) return true;
  }
  return false;
}

bool CEntity::isTextureLoaded(const int& group) {
  for (int i = 0; i < textureList.size(); i++) {
    if (group == textureList[i].group_ID) return true;
  }
  return false;
}

SDL_Texture* CEntity::getSrcTexture(const int& group) {
  for (int i = 0; i < textureList.size(); i++) {
    if (group == textureList[i].group_ID) {
      return textureList[i].img;
    }
  }
  return NULL;
}

SDL_Texture* CEntity::loadTexInfo(const int& group) {
  if (isTextureLoaded(group)) return getSrcTexture(group);

  SDL_Texture* entity_tex = NULL;
  entity_tex = CEntityData::loadSrcTexture(group);

  if (entity_tex != NULL) {
    EntityTexInfo newInfo;
    newInfo.group_ID = group;
    newInfo.img = entity_tex;
    textureList.push_back(newInfo);
  }
  return entity_tex;
}

void CEntity::updateHitboxes(const int& group, const int& entity) {
  for (int i = 0; i < entityList.size(); i++) {
    if (group == entityList[i].group_ID && entity == entityList[i].entity_ID) {
      entityList[i].hitR = CEntityData::getHitboxDims(group, entity);
    }
  }
}

void CEntity::purgeStaleTextures() {
  for (int i = textureList.size() - 1; i >= 0; i--)
  {
    if (!isGroupUsed(textureList[i].group_ID))
    {
      SDL_DestroyTexture(textureList[i].img);
      textureList.erase(textureList.begin() + i);
    }
  }
}
