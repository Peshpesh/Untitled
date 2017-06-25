#include "CTileset.h"

CTileset CTileset::PickTS;

namespace {
  const SDL_Rect canv         = {220,190,200,100};
  const SDL_Rect fnameBox     = {225,210,190,11};
  const SDL_Rect titleBox     = {225,193,190,16};
  const SDL_Rect infoBox      = {225,222,190,40};
  const SDL_Rect okButton     = {255,270,60,13};
  const SDL_Rect cancelButton = {325,270,60,13};
  const SDL_Point* canvCol      = &color::black;
  const SDL_Point* fnameBoxCol  = &color::white;
  const SDL_Point* optCol       = &color::black;
  const SDL_Point* bCol         = &color::white;
  const SDL_Color* textCol      = &fontrgb::white;
  const SDL_Color* fnameCol     = &fontrgb::black;
  const short bstrsiz = 2;
  const short cstrsiz = 3;
  const char* const ts_path = "../res_edit/tile/";
  const char* const extension = ".png";
  const char* const title = "Change Tileset";
  const char* const info = "WARNING:\nSuccessfully changing the active tileset will reset the working Area and empty containers of entities and scenery.";
  const char* const oktext = "OK";
  const char* const canceltext = "Cancel";
}

CTileset::CTileset()
{
  changeTS = false;
  file = "default";
  newF = "";
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
    case SDLK_RETURN: CInterrupt::removeFlag(INTRPT_CHANGE_TS); changeTS = true; break;
    case SDLK_ESCAPE: CInterrupt::removeFlag(INTRPT_CHANGE_TS); resetPath(); break;
    default: break;
  }
}

void CTileset::OnLButtonDown(int mX, int mY)
{
  SDL_Point mouse = {mX, mY};
  if (SDL_PointInRect(&mouse, &okButton))
  {
    CInterrupt::removeFlag(INTRPT_CHANGE_TS);
    changeTS = true;
  }
  else if (SDL_PointInRect(&mouse, &cancelButton))
  {
    CInterrupt::removeFlag(INTRPT_CHANGE_TS);
    resetPath();
  }
}

bool CTileset::OnRender()
{
  CAsset::drawButton(&canv, cstrsiz, canvCol, bCol);
  CAsset::drawBoxFill(&fnameBox, fnameBoxCol);
  CAsset::drawButton(&okButton, bstrsiz, optCol, bCol);
  CAsset::drawButton(&cancelButton, bstrsiz, optCol, bCol);

  Font::FontControl.SetFont(FONT_MINI);
  Font::NewCenterWrite(title, &titleBox, textCol);
  Font::NewCenterWrite(newF.c_str(), &fnameBox, fnameCol);
  Font::NewCenterWrite(info, &infoBox, textCol);
  Font::NewCenterWrite(oktext, &okButton, textCol);
  Font::NewCenterWrite(canceltext, &cancelButton, textCol);

  return true;
}

std::string CTileset::getFilePath()
{
  std::string filepath = ts_path + file + extension;
  return filepath;
}

bool CTileset::reqChange()
{
  return changeTS;
}

SDL_Texture* CTileset::changeTileset()
{
  SDL_Texture* try_surf = NULL;
  std::string filepath = ts_path + newF + extension;

  if ((try_surf = CSurface::OnLoad(filepath.c_str())) != 0)
  {
    file = newF;
  }

  resetPath();
  changeTS = false;

  return try_surf;
}
