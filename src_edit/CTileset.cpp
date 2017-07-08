#include "CTileset.h"

CTileset CTileset::TSControl;

namespace {
  const SDL_Rect canv         = {220,190,200,100};
  const SDL_Rect fnameBox     = {225,210,190,11};
  const SDL_Rect titleBox     = {225,193,190,16};
  const SDL_Rect infoBox      = {225,222,190,40};
  const SDL_Rect okButton     = {255,270,60,13};
  const SDL_Rect cancelButton = {325,270,60,13};
  const SDL_Point* canvCol      = &palette::black;
  const SDL_Point* fnameBoxCol  = &palette::white;
  const SDL_Point* optCol       = &palette::black;
  const SDL_Point* optHovCol    = &palette::light_indigo;
  const SDL_Point* bCol         = &palette::white;
  const SDL_Color* textCol      = &rgb::white;
  const SDL_Color* fnameCol     = &rgb::dark_red;
  const short bstrsiz = 2;
  const short cstrsiz = 3;
  const char* const ts_path = "../res/tile/";
  const char* const extension = ".png";
  const char* const title = "Change Tileset";
  const char* const mainInfo = "WARNING:\nSuccessfully changing the active tileset will reset the working Area and empty containers of entities and scenery.";
  const char* const oktext = "OK";
  const char* const canceltext = "Cancel";

  const char* const inform[] = {
    "Cancelled.\nNo changes were made.",
    "Tileset changed successfully.\nThe area was reset.",
    "You are already using that tileset!\nNo changes were made.",
    "Failed to load tileset.\nNo changes were made."
  };
  enum {
    I_CANCEL = 0,
    I_CHANGE,
    I_SAME,
    I_FAIL,
  };
}

CTileset::CTileset()
{
  succ = false;

  tileset = NULL;
  ts_w = ts_h = 0;

  file = "";
  newF = "";
}

bool CTileset::OnInit()
{
  return changeTileset("default");
}

void CTileset::OnEvent(SDL_Event* Event)
{
  CEvent::OnEvent(Event);
}

void CTileset::resetPath()
{
  newF.clear();
}

void CTileset::backPath()
{
  if (newF.size() > 0) newF.erase(newF.end()-1);
}

void CTileset::addToPath(char addChar)
{
  if (newF.size() < newF.max_size()) newF.push_back(addChar);
}

void CTileset::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
  switch (sym)
  {
    case SDLK_0:	addToPath('0');	break;
    case SDLK_1:	addToPath('1');	break;
    case SDLK_2:	addToPath('2');	break;
    case SDLK_3:	addToPath('3');	break;
    case SDLK_4:	addToPath('4');	break;
    case SDLK_5:	addToPath('5');	break;
    case SDLK_6:	addToPath('6');	break;
    case SDLK_7:	addToPath('7');	break;
    case SDLK_8:	addToPath('8');	break;
    case SDLK_9:	addToPath('9');	break;
    case SDLK_a:	addToPath('a');	break;
    case SDLK_b:	addToPath('b');	break;
    case SDLK_c:	addToPath('c');	break;
    case SDLK_d:	addToPath('d');	break;
    case SDLK_e:	addToPath('e');	break;
    case SDLK_f:	addToPath('f');	break;
    case SDLK_g:	addToPath('g');	break;
    case SDLK_h:	addToPath('h');	break;
    case SDLK_i:	addToPath('i');	break;
    case SDLK_j:	addToPath('j');	break;
    case SDLK_k:	addToPath('k');	break;
    case SDLK_l:	addToPath('l');	break;
    case SDLK_m:	addToPath('m');	break;
    case SDLK_n:	addToPath('n');	break;
    case SDLK_o:	addToPath('o');	break;
    case SDLK_p:	addToPath('p');	break;
    case SDLK_q:	addToPath('q');	break;
    case SDLK_r:	addToPath('r');	break;
    case SDLK_s:	addToPath('s');	break;
    case SDLK_t:	addToPath('t');	break;
    case SDLK_u:	addToPath('u');	break;
    case SDLK_v:	addToPath('v');	break;
    case SDLK_w:	addToPath('w');	break;
    case SDLK_x:	addToPath('x');	break;
    case SDLK_y:	addToPath('y');	break;
    case SDLK_z:	addToPath('z');	break;
    case SDLK_PERIOD: addToPath('.'); break;
    case SDLK_MINUS: addToPath('-'); break;
    case SDLK_UNDERSCORE: addToPath('_'); break;
    case SDLK_BACKSPACE: backPath(); break;
    case SDLK_RETURN: CInterrupt::removeFlag(INTRPT_CHANGE_TS); changeTileset(); break;
    case SDLK_ESCAPE: CInterrupt::removeFlag(INTRPT_CHANGE_TS); succ = false; pushInform(I_CANCEL); resetPath(); break;
    default: break;
  }
}

void CTileset::OnLButtonDown(int mX, int mY)
{
  SDL_Point mouse = {mX, mY};
  if (SDL_PointInRect(&mouse, &okButton))
  {
    CInterrupt::removeFlag(INTRPT_CHANGE_TS);
    changeTileset();
  }
  else if (SDL_PointInRect(&mouse, &cancelButton))
  {
    succ = false;
    pushInform(I_CANCEL);
    CInterrupt::removeFlag(INTRPT_CHANGE_TS);
    resetPath();
  }
}

bool CTileset::OnRender(const SDL_Point* m)
{
  CAsset::drawStrBox(&canv, cstrsiz, canvCol, bCol);
  CAsset::drawBoxFill(&fnameBox, fnameBoxCol);
  CAsset::drawStrBox(&okButton, bstrsiz, SDL_PointInRect(m, &okButton) ? optHovCol : optCol, bCol);
  CAsset::drawStrBox(&cancelButton, bstrsiz, SDL_PointInRect(m, &cancelButton) ? optHovCol : optCol, bCol);

  Font::FontControl.SetFont(FONT_MINI);
  Font::NewCenterWrite(title, &titleBox, textCol);
  Font::NewCenterWrite(newF.c_str(), &fnameBox, fnameCol);
  Font::NewCenterWrite(mainInfo, &infoBox, textCol);
  Font::NewCenterWrite(oktext, &okButton, textCol);
  Font::NewCenterWrite(canceltext, &cancelButton, textCol);

  return true;
}

SDL_Rect CTileset::getTileSrcR(const int& ID)
{
  SDL_Rect srcR = {0, 0, 0, 0};
  if (ID < 0) return srcR;

  srcR.x = (ID % ts_w) * TILE_SIZE;
  srcR.y = (ID / ts_w) * TILE_SIZE;
  srcR.w = srcR.h = TILE_SIZE;

  return srcR;
}

std::string CTileset::getFileName()
{
  return file;
}

std::string CTileset::getFilePath()
{
  std::string filepath = ts_path + file + extension;
  return filepath;
}

bool CTileset::wasSuccess()
{
  return succ;
}

bool CTileset::changeTileset(const char* fname)
{
  SDL_Texture* try_surf = NULL;

  std::string filepath = ts_path + std::string(fname) + extension;

  if ((try_surf = CSurface::OnLoad(filepath.c_str())) != 0) {
    succ = true;
    SDL_DestroyTexture(tileset);
    tileset = try_surf;
    CAsset::queryTileDims(tileset, ts_w, ts_h);
    file = fname;
  }
  else {
    succ = false;
  }

  return succ;
}

void CTileset::changeTileset()
{
  if (newF == file) {
    succ = false;
    pushInform(I_SAME);
    resetPath();
    return;
  }

  SDL_Texture* try_surf = NULL;
  std::string filepath = ts_path + newF + extension;

  if ((try_surf = CSurface::OnLoad(filepath.c_str())) != 0) {
    succ = true;
    pushInform(I_CHANGE);
    SDL_DestroyTexture(tileset);
    tileset = try_surf;
    CAsset::queryTileDims(tileset, ts_w, ts_h);
    file = newF;
  }
  else {
    succ = false;
    pushInform(I_FAIL);
  }

  resetPath();
}

void CTileset::pushInform(const int& ID)
{
  if (ID < I_CANCEL || ID > I_FAIL) return;

  CInform::InfoControl.pushInform(inform[ID]);
}
