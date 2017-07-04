#include "CFileIO.h"

CFileIO CFileIO::IOhandle;

namespace {
  const short bstrsiz = 2;
  const short cstrsiz = 3;
  const SDL_Rect canv         = {(WWIDTH - 270) / 2, (WHEIGHT - 320) / 2, 270, 320};
  const SDL_Rect titleBox     = {canv.x, canv.y + cstrsiz, canv.w, 11};
  const SDL_Rect prevTitleBox = {canv.x + cstrsiz, titleBox.y + titleBox.h, 90, 11};
  const SDL_Rect fprevBox     = {prevTitleBox.x + prevTitleBox.w, prevTitleBox.y, canv.w - prevTitleBox.w - (cstrsiz * 2), 11};
  const SDL_Rect newTitleBox  = {canv.x + cstrsiz, prevTitleBox.y + prevTitleBox.h + cstrsiz, 90, 11};
  const SDL_Rect fnewBox      = {newTitleBox.x + newTitleBox.w, newTitleBox.y, canv.w - newTitleBox.w - (cstrsiz * 2), 11};

  const char* const inform[] = {
    "IO cancelled.",
    "Save successful.",
    "Load successful.",
    "Save nothing... ?",
    "Loaded nothing successfully.",
    "Failed to load Entity file.",
    "Failed to load Scenery file.",
    "Failed to save data."
  };
  enum {
    I_CANCEL = 0,
    I_SAVE,
    I_LOAD,
    I_SAVE_NOTHING,
    I_LOAD_NOTHING,
    I_FAIL_ENTITY,
    I_FAIL_SCENERY,
    I_FAIL_SAVE,
  };
}

namespace render {
  const SDL_Point* canvCol      = &palette::cyan;
  const SDL_Point* titleBoxCol  = &palette::black;
  const SDL_Point* fnameBoxCol  = &palette::dark_violet;
  const SDL_Point* bCol         = &palette::dark_green;
  const SDL_Color* textCol      = &rgb::black;
  const SDL_Color* fnameCol     = &rgb::white;
  const char* const saveTitle = "...Save Stage...";
  const char* const loadTitle = "...Load Stage...";
  const char* const prevTitle = "Previous Name";
  const char* const newTitle  = "Target Name";
  const char* const okTitle   = "OK";
  const char* const cancTitle = "Cancel";
}

CFileIO::CFileIO()
{
  prevName = "testing";
  newName = "";
}

void CFileIO::OnEvent(SDL_Event* Event)
{
  CEvent::OnEvent(Event);
}

void CFileIO::OnKeyDown(SDL_Keycode sym, Uint16 mod)
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
    case SDLK_BACKSPACE: backPath(); break;
    case SDLK_RETURN: handleIOrequest(); break;
    case SDLK_ESCAPE: pushInform(I_CANCEL); CInterrupt::removeFlag(INTRPT_LOAD | INTRPT_SAVE); newName.clear(); break;
    default: break;
  }
}

void CFileIO::OnLButtonDown(int mX, int mY)
{
  //
}

void CFileIO::handleIOrequest()
{
  if (CInterrupt::isFlagOn(INTRPT_LOAD)) {
    if (!newName.empty()) loadData();
    else pushInform(I_LOAD_NOTHING);
  }
  else if (CInterrupt::isFlagOn(INTRPT_SAVE)) {
    if (!newName.empty()) saveData();
    else pushInform(I_SAVE_NOTHING);
  }
  CInterrupt::removeFlag(INTRPT_LOAD | INTRPT_SAVE);
}

bool CFileIO::OnRender(const SDL_Point* m)
{
  using namespace render;

  CAsset::drawStrBox(&canv, cstrsiz, canvCol, bCol);

  CAsset::drawBoxFill(&prevTitleBox, titleBoxCol);
  CAsset::drawBoxFill(&newTitleBox, titleBoxCol);

  CAsset::drawBoxFill(&fprevBox, fnameBoxCol);
  CAsset::drawBoxFill(&fnewBox, fnameBoxCol);

  Font::FontControl.SetFont(FONT_MINI);
  if (CInterrupt::isFlagOn(INTRPT_LOAD)) {
    Font::NewCenterWrite(loadTitle, &titleBox, textCol);
  }
  else {
    Font::NewCenterWrite(saveTitle, &titleBox, textCol);
  }
  Font::NewCenterWrite(prevTitle, &prevTitleBox, fnameCol);
  Font::NewCenterWrite(newTitle, &newTitleBox, fnameCol);
  Font::NewCenterWrite(prevName.c_str(), &fprevBox, fnameCol);
  Font::NewCenterWrite(newName.c_str(), &fnewBox, fnameCol);

  return true;
}

void CFileIO::backPath()
{
  if (newName.size() > 0) newName.erase(newName.end() - 1);
}

void CFileIO::addToPath(const char& addSym)
{
  if (newName.size() < newName.max_size()) newName.push_back(addSym);
}

void CFileIO::loadData()
{
  if (!CArea::AreaControl.NewLoad(newName.c_str())) {
    // problem loading the area
    return;
  }

  if (!CEntityEdit::NPCControl.LoadList(newName.c_str())) {
    // problem loading entities
    pushInform(I_FAIL_ENTITY);
    return;
  }

  if (!CSceneryEdit::ScnControl.LoadScenery(newName.c_str())) {
    // problem loading 2.5D elements
    pushInform(I_FAIL_SCENERY);
    return;
  }

  prevName = newName;
  newName.clear();

  pushInform(I_LOAD);
}

void CFileIO::saveData()
{
  if (!CArea::AreaControl.NewSave(newName.c_str())) {
    pushInform(I_FAIL_SAVE);
    return;
  }
  if (!CEntityEdit::NPCControl.SaveList(newName.c_str())) {
    pushInform(I_FAIL_SAVE);
    return;
  }
  if (!CSceneryEdit::ScnControl.SaveScenery(newName.c_str())) {
    pushInform(I_FAIL_SAVE);
    return;
  }

  prevName = newName;
  newName.clear();

  pushInform(I_SAVE);
}

void CFileIO::pushInform(const int& ID)
{
  if (ID < I_CANCEL || ID > I_FAIL_SAVE) return;

  CInform::InfoControl.pushInform(inform[ID]);
}
