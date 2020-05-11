#include "CTileset.h"

CTileset CTileset::TSControl;

namespace {
  // full canvas dimensions
  const short canv_w = 350;
  const short canv_h = 200;
  const short canv_x = (WWIDTH - canv_w) / 2;
  const short canv_y = (WHEIGHT - canv_h) / 2;
  const SDL_Rect canv = {canv_x,canv_y,canv_w,canv_h};

  const short buff_w = 10;  // buffer width
  const short buff_h = 10;  // buffer height
  const short bstrsiz = 2;  // button stroke size
  const short cstrsiz = 3;  // canvas stroke size

  // information dimensions
  const short info_w = 250;
  const short info_h = 30;
  const short info_x = canv_x + ((canv_w - info_w) / 2);
  const short info_y = canv_y + buff_h;
  const SDL_Rect infoBox = {info_x,info_y,info_w,info_h};
  const char* const mainInfo = "NOTE\n\
                                --------------------\n\
                                Successfully changing the active \
                                tileset will not reset the working area.\
                                Old tile IDs will be carried over.";

  // selected tileset fullname display dimensions
  const short select_w = canv_w - (cstrsiz * 4);
  const short select_h = 15;
  const short select_x = canv_x + (cstrsiz * 2);
  const short select_y = info_y + info_h + buff_h;
  const SDL_Rect selectBox       = {select_x,select_y,select_w,select_h};
  const SDL_Point* selectBoxCol  = &palette::white;
  const SDL_Color* selectTextCol = &rgb::dark_red;

  // option (and list) dimensions
  const short opt_w = 80;
  const short opt_h = 15;
  const short opt_cols = 3;
  const short opt_rows = 3;
  const short optlist_w = (opt_w * opt_cols) + (buff_w * (opt_cols - 1));
  const short optlist_h = (opt_h * opt_rows) + (buff_h * (opt_rows - 1));
  const short optlist_x = canv_x + (canv_w - optlist_w) / 2;
  const short optlist_y = select_y + select_h + (buff_h * 2);

  // decision dimensions
  const short dec_w         = 60;
  const short dec_h         = 15;
  const short n_dec         = 2;  // number of decisions
  const short dec_buff      = (canv_w - (dec_w * n_dec)) / (n_dec + 1);
  const short dec_y         = optlist_y + optlist_h + (buff_h * 2);
  const short ok_x          = canv_x + dec_buff;
  const short cancel_x      = ok_x + dec_w + dec_buff;
  const SDL_Rect okBox      = {ok_x,dec_y,dec_w,dec_h};
  const SDL_Rect cancelBox  = {cancel_x,dec_y,dec_w,dec_h};
  const char* const oktext     = "OK";
  const char* const canceltext = "Cancel";

  const SDL_Point* canvCol      = &palette::black;
  const SDL_Point* optCol       = &palette::black;
  const SDL_Point* optHovCol    = &palette::light_indigo;
  const SDL_Point* activeCol    = &palette::dark_green;
  const SDL_Point* selectCol    = &palette::dark_red;
  const SDL_Point* bCol         = &palette::white;
  const SDL_Color* textCol      = &rgb::white;
  const char* const ts_path = "../res_edit/tile/";
  const char* const extension = ".png";

  const char* const inform[] = {
    "Cancelled.\nNo changes were made.",
    "Tileset changed successfully.\nThe area was reset.",
    "You are already using that tileset!\nNo changes were made.",
    "Failed to load tileset.\nNo changes were made.",
    "The requested tileset ID was not found.\nNo changes were made."
  };
  enum {
    I_CANCEL = 0,
    I_CHANGE,
    I_SAME,
    I_FAIL,
    I_NOTFOUND,
  };
}

CTileset::CTileset() {
  active_ID = -1;
  select_ID = Tileset_ID::TS_DEFAULT;
  succ = false;
  tileset = grid_tileset = type_tileset = coll_tileset = NULL;
  ts_w = ts_h = 0;
  grid_w = grid_h = 0;
  type_w = type_h = 0;
  coll_w = coll_h = 0;
  type_alpha = 215;
  coll_alpha = 55;
}

bool CTileset::OnInit() {
  using namespace Tileset_ID;

  if ((grid_tileset = CSurface::OnLoad("../res_edit/fillgrid.png")) == NULL) {
    return false;
  }

  CAsset::queryTileDims(grid_tileset, grid_w, grid_h);

  if ((type_tileset = CSurface::OnLoad("../res_edit/types.png")) == NULL) {
    return false;
  }

  SDL_SetTextureAlphaMod(type_tileset, type_alpha);
  CAsset::queryTileDims(type_tileset, type_w, type_h);

  if ((coll_tileset = CSurface::OnLoad("../res_edit/slopes.png")) == NULL) {
    return false;
  }

  SDL_SetTextureAlphaMod(coll_tileset, coll_alpha);
  CAsset::queryTileDims(coll_tileset, coll_w, coll_h);

  return changeTileset();
}

void CTileset::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CTileset::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_ESCAPE: {
      CInterrupt::removeFlag(INTRPT_CHANGE_TS);
      succ = false;
      pushInform(I_CANCEL);
      break;
    }
    default: break;
  }
}

void CTileset::OnLButtonDown(int mX, int mY) {
  SDL_Point mouse = {mX, mY};
  if (pickTileset(mouse)) return;
  if (SDL_PointInRect(&mouse, &okBox)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_TS);
    changeTileset();
  } else if (SDL_PointInRect(&mouse, &cancelBox)) {
    succ = false;
    pushInform(I_CANCEL);
    CInterrupt::removeFlag(INTRPT_CHANGE_TS);
  }
}

bool CTileset::pickTileset(const SDL_Point& m) {
  SDL_Rect optBox;
  optBox.w = opt_w;
  optBox.h = opt_h;

  for (int j=0; j < opt_rows; j++) {
    optBox.y = optlist_y + (j * (optBox.h + buff_h));
    for (int i=0; i < opt_cols; i++) {
      int ID = i + j * opt_cols;
      if (ID < Tileset_ID::num) {
        optBox.x = optlist_x + (i * (optBox.w + buff_w));
        if (SDL_PointInRect(&m, &optBox)) {
          select_ID = ID;
          return true;
        }
      } else return false;
    }
  }
  return false;
}

bool CTileset::OnRender(const SDL_Point* m) {
  using namespace Tileset_ID;

  Font::FontControl.SetFont(FONT_MINI);
  CAsset::drawStrBox(&canv, cstrsiz, canvCol, bCol);
  Font::NewCenterWrite(mainInfo, &infoBox, textCol);

  CAsset::drawBoxFill(&selectBox, selectBoxCol);
  std::string selectLine = fullname[select_ID] + " map selected";
  Font::NewCenterWrite(selectLine.c_str(), &selectBox, selectTextCol);

  drawOptions(m);

  CAsset::drawStrBox(&okBox, bstrsiz, SDL_PointInRect(m, &okBox) ? optHovCol : optCol, bCol);
  Font::NewCenterWrite(oktext, &okBox, textCol);

  CAsset::drawStrBox(&cancelBox, bstrsiz, SDL_PointInRect(m, &cancelBox) ? optHovCol : optCol, bCol);
  Font::NewCenterWrite(canceltext, &cancelBox, textCol);

  return true;
}

void CTileset::drawOptions(const SDL_Point* m) {
  using namespace Tileset_ID;

  SDL_Rect optBox;
  optBox.w = opt_w;
  optBox.h = opt_h;

  for (int j=0; j < opt_rows; j++) {
    optBox.y = optlist_y + (j * (optBox.h + buff_h));
    for (int i=0; i < opt_cols; i++) {
      int ID = i + j * opt_cols;
      if (ID < num) {
        optBox.x = optlist_x + (i * (optBox.w + buff_w));

        SDL_Point col = *optCol;
        if (ID == active_ID) col = *activeCol;
        else if (ID == select_ID) col = *selectCol;
        else if (SDL_PointInRect(m, &optBox)) col = *optHovCol;

        CAsset::drawStrBox(&optBox, bstrsiz, &col, bCol);
        Font::NewCenterWrite(name[ID].c_str(), &optBox, textCol);
      } else return;
    }
  }
}

SDL_Rect CTileset::getTileSrcR(const int& ID) {
  SDL_Rect srcR = {0, 0, 0, 0};
  if (ID < 0) return srcR;

  srcR.x = (ID % ts_w) * TILE_SIZE;
  srcR.y = (ID / ts_w) * TILE_SIZE;
  srcR.w = srcR.h = TILE_SIZE;

  return srcR;
}

std::string CTileset::getFileName() {
  return Tileset_ID::name[active_ID];
}

std::string CTileset::getFilePath() {
  using namespace Tileset_ID;
  std::string filepath = ts_path + name[active_ID] + extension;
  return filepath;
}

short CTileset::getFileID(const std::string& fname) {
  using namespace Tileset_ID;
  short i = 0;
  while (i < num) {
    if (fname == name[i]) break;
    i++;
  }
  if (i == num) i = -1;
  return i;
}

short CTileset::getFileID() {
  return getFileID(Tileset_ID::name[active_ID]);
}

bool CTileset::wasSuccess() {
  return succ;
}

bool CTileset::changeTileset(const short& ID) {
  using namespace Tileset_ID;
  if (ID < 0 || ID >= num) {
    succ = false;
    return succ;
  }

  SDL_Texture* try_surf = NULL;
  std::string filepath = ts_path + name[ID] + extension;

  if ((try_surf = CSurface::OnLoad(filepath.c_str())) != 0) {
    succ = true;
    SDL_DestroyTexture(tileset);
    tileset = try_surf;
    CAsset::queryTileDims(tileset, ts_w, ts_h);
    active_ID = select_ID = ID;
  }
  else {
    succ = false;
  }
  return succ;
}

bool CTileset::changeTileset() {
  using namespace Tileset_ID;

  if (select_ID < 0 || select_ID >= num) {
    succ = false;
    pushInform(I_NOTFOUND);
    return succ;
  }
  if (active_ID == select_ID) {
    succ = false;
    pushInform(I_SAME);
    return succ;
  }

  SDL_Texture* try_surf = NULL;
  std::string filepath = ts_path + name[select_ID] + extension;

  if ((try_surf = CSurface::OnLoad(filepath.c_str())) != 0) {
    succ = true;
    pushInform(I_CHANGE);
    SDL_DestroyTexture(tileset);
    tileset = try_surf;
    CAsset::queryTileDims(tileset, ts_w, ts_h);
    active_ID = select_ID;
  }
  else {
    succ = false;
    select_ID = active_ID;
    pushInform(I_FAIL);
  }
  return succ;
}

void CTileset::changeTypeAlpha(const int& a) {
  type_alpha = a;
  refreshTypeAlpha();
}

void CTileset::changeCollAlpha(const int& a) {
  coll_alpha = a;
  refreshCollAlpha();
}

void CTileset::maxTypeAlpha() {
  SDL_SetTextureAlphaMod(type_tileset, MAX_RGBA);
}

void CTileset::maxCollAlpha() {
  SDL_SetTextureAlphaMod(coll_tileset, MAX_RGBA);
}

void CTileset::refreshTypeAlpha() {
  SDL_SetTextureAlphaMod(type_tileset, type_alpha);
}

void CTileset::refreshCollAlpha() {
  SDL_SetTextureAlphaMod(coll_tileset, coll_alpha);
}

void CTileset::pushInform(const int& ID) {
  if (ID < I_CANCEL || ID > I_NOTFOUND) return;
  CInform::InfoControl.pushInform(inform[ID]);
}

void CTileset::OnTerminate() {
  SDL_DestroyTexture(tileset);
  SDL_DestroyTexture(type_tileset);
  SDL_DestroyTexture(coll_tileset);
}
