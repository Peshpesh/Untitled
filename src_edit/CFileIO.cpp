#include "CFileIO.h"

CFileIO CFileIO::IOhandle;

namespace {
  const short fname_max_size = 29;
  const short bstrsiz = 2;
  const short b_w = 60;  // width of a button
  const short b_h = 13; // height of a button
  const short bspac = 10; // spacing between buttons
  const short cstrsiz = 3;
  const short row_h = 11; // height of a text row
  const short fname_w = 90; // width of name of a text field ("TARGET NAME")
  const short w = 270;
  const short h = 180;
  const short x = (WWIDTH - 270) / 2;
  const short y = (WHEIGHT - 320) / 2;
  const short info_h = 100;
  const SDL_Rect canv         = {x, y, w, h};
  const SDL_Rect titleBox     = {canv.x, canv.y + cstrsiz, canv.w, row_h};
  const SDL_Rect prevTitleBox = {canv.x + cstrsiz, titleBox.y + titleBox.h, fname_w, row_h};
  const SDL_Rect fprevBox     = {prevTitleBox.x + prevTitleBox.w, prevTitleBox.y, canv.w - prevTitleBox.w - (cstrsiz * 2), row_h};
  const SDL_Rect newTitleBox  = {canv.x + cstrsiz, prevTitleBox.y + prevTitleBox.h + cstrsiz, fname_w, row_h};
  const SDL_Rect fnewBox      = {newTitleBox.x + newTitleBox.w, newTitleBox.y, canv.w - newTitleBox.w - (cstrsiz * 2), row_h};
  const SDL_Rect infoBox      = {canv.x + cstrsiz, newTitleBox.y + newTitleBox.h + cstrsiz, canv.w - (cstrsiz * 2), info_h};
  const SDL_Rect pfmButton    = {canv.x + (canv.w - (b_w * 3) - (bspac * 2)) / 2, infoBox.y + infoBox.h + bspac, b_w, b_h};
  const SDL_Rect pvmButton    = {pfmButton.x + b_w + bspac, pfmButton.y, b_w, b_h};
  const SDL_Rect escLoadBut   = {pvmButton.x + b_w + bspac, pvmButton.y, b_w, b_h};
  const SDL_Rect saveButton   = {canv.x + (canv.w - (b_w * 2) - bspac) / 2, infoBox.y + infoBox.h + bspac, b_w, b_h};
  const SDL_Rect escSaveBut   = {saveButton.x + b_w + bspac, saveButton.y, b_w, b_h};

  enum {
    I_CANCEL = 0,
    I_SAVE,
    I_LOAD,
    I_SAVE_NOTHING,
    I_LOAD_NOTHING,
    I_MAKE_NEW,
    I_FAIL_ENTITY,
    I_FAIL_SCENERY,
    I_FAIL_SAVE,
  };

  const char* const inform[] = {
    "IO cancelled.",
    "Save successful.",
    "Load successful.",
    "Save nothing... ?",
    "Loaded nothing successfully.",
    "All data reset.",
    "Failed to load Entity file.",
    "Failed to load Scenery file.",
    "Failed to save data."
  };
}

CFileIO::CFileIO() {
  prevName = "";
  newName = "";
  initMenus();
}

void CFileIO::initMenus() {
  reset.canvCol     = &palette::green;
  reset.titleBoxCol = &palette::black;
  reset.fBoxCol     = &palette::black;
  reset.bCol        = &palette::black;
  reset.textCol     = &rgb::black;
  reset.fnameCol    = &rgb::black;
  reset.optCol      = &palette::white;
  reset.optHovCol   = &palette::red;

  reset.title       = "...New Stage...";
  reset.prevTitle   = "";
  reset.newTitle    = "";
  reset.optAText    = "New PFM";
  reset.optBText    = "New PVM";
  reset.optCText    = "Cancel";

  load.canvCol     = &palette::cyan;
  load.titleBoxCol = &palette::black;
  load.fBoxCol     = &palette::dark_violet;
  load.bCol        = &palette::black;
  load.textCol     = &rgb::black;
  load.fnameCol    = &rgb::white;
  load.optCol      = &palette::white;
  load.optHovCol   = &palette::green;

  load.title       = "...Load Stage...";
  load.prevTitle   = "Previous Name";
  load.newTitle    = "Target Name";
  load.optAText    = "Load PFM";
  load.optBText    = "Load PVM";
  load.optCText    = "Cancel";

  save.canvCol     = &palette::yellow;
  save.titleBoxCol = &palette::black;
  save.fBoxCol     = &palette::dark_red;
  save.bCol        = &palette::black;
  save.textCol     = &rgb::black;
  save.fnameCol    = &rgb::white;
  save.optCol      = &palette::white;
  save.optHovCol   = &palette::green;

  save.title       = "...Save Stage...";
  save.prevTitle   = "Previous Name";
  save.newTitle    = "Target Name";
  save.optAText    = "Save";
  save.optBText    = "Cancel";
  save.optCText    = "";

  reset.info       = "\
    Reset information\n\
    --------------------\n\
    All vectors for...\n\
    \n\
    - maps\n\
    - entities\n\
    - scenery\n\
    \n\
    ...will be cleared out and reset to default settings.\n\
    \n\
    Select PFM for a new platform stage.\n\
    Select PVM for a new planview stage.";

  load.info        = "\
    Load information\n\
    --------------------\n\
    Enter a root filename to load area and associated files.\n\
    A successful load will change...\n\
    \n\
    - The area and all maps\n\
    - entities and entity sets\n\
    - scenery and their textures\n\
    \n\
    All files will be loaded from the maps subdirectory in data.";

  save.info        = "\
    Save information\n\
    --------------------\n\
    Enter a root filename to name all contributing files for the working area.\n\
    A successful save will create...\n\
    \n\
    - binary .pfm or .pvm file\n\
    - binary .ent file\n\
    - binary .scn file\n\
    \n\
    All files will be saved in the maps subdirectory in data.\n\
    \n\
    Note that any pre-existing files that share the root filename provided will be overwritten.";
}

void CFileIO::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CFileIO::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
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
    // case SDLK_RETURN: handleIOrequest(); break;
    case SDLK_ESCAPE: pushInform(I_CANCEL); CInterrupt::removeFlag(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE); newName.clear(); break;
    default: break;
  }
}

void CFileIO::OnLButtonDown(int mX, int mY) {
  SDL_Point mouse = {mX, mY};
  bool thirdOpt = !CInterrupt::isFlagOn(INTRPT_SAVE);

  if (thirdOpt) {
    if (SDL_PointInRect(&mouse, &pfmButton)) handleIOrequest();
    else if (SDL_PointInRect(&mouse, &pvmButton)) handleIOrequest();
    else if (SDL_PointInRect(&mouse, &escLoadBut)) {
      pushInform(I_CANCEL);
      CInterrupt::removeFlag(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE);
      newName.clear();
    }
  } else {
    if (SDL_PointInRect(&mouse, &saveButton)) handleIOrequest();
    else if (SDL_PointInRect(&mouse, &escSaveBut)) {
      pushInform(I_CANCEL);
      CInterrupt::removeFlag(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE);
      newName.clear();
    }
  }
}

void CFileIO::handleIOrequest() {
  if (CInterrupt::isFlagOn(INTRPT_NEW)) newData();
  else if (CInterrupt::isFlagOn(INTRPT_LOAD)) {
    if (!newName.empty()) loadData();
    else pushInform(I_LOAD_NOTHING);
  }
  else if (CInterrupt::isFlagOn(INTRPT_SAVE)) {
    if (!newName.empty()) saveData();
    else pushInform(I_SAVE_NOTHING);
  }
  CInterrupt::removeFlag(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE);
}

bool CFileIO::OnRender(const SDL_Point* m) {
  if (CInterrupt::isFlagOn(INTRPT_NEW))       renderMenu(reset, m);
  else if (CInterrupt::isFlagOn(INTRPT_LOAD)) renderMenu(load, m);
  else if (CInterrupt::isFlagOn(INTRPT_SAVE)) renderMenu(save, m);
  return true;
}

void CFileIO::renderMenu(const prompt& menu, const SDL_Point* m) {
  CAsset::drawStrBox(&canv, cstrsiz, menu.canvCol, menu.bCol);

  CAsset::drawBoxFill(&prevTitleBox, menu.titleBoxCol);
  CAsset::drawBoxFill(&newTitleBox, menu.titleBoxCol);

  CAsset::drawBoxFill(&fprevBox, menu.fBoxCol);
  CAsset::drawBoxFill(&fnewBox, menu.fBoxCol);

  if (!CInterrupt::isFlagOn(INTRPT_SAVE)) {
    CAsset::drawStrBox(&pfmButton, bstrsiz, SDL_PointInRect(m, &pfmButton) ? menu.optHovCol : menu.optCol, menu.bCol);
    CAsset::drawStrBox(&pvmButton, bstrsiz, SDL_PointInRect(m, &pvmButton) ? menu.optHovCol : menu.optCol, menu.bCol);
    CAsset::drawStrBox(&escLoadBut, bstrsiz, SDL_PointInRect(m, &escLoadBut) ? menu.optHovCol : menu.optCol, menu.bCol);
    Font::NewCenterWrite(menu.optAText, &pfmButton, menu.textCol);
    Font::NewCenterWrite(menu.optBText, &pvmButton, menu.textCol);
    Font::NewCenterWrite(menu.optCText, &escLoadBut, menu.textCol);
  } else {
    CAsset::drawStrBox(&saveButton, bstrsiz, SDL_PointInRect(m, &saveButton) ? menu.optHovCol : menu.optCol, menu.bCol);
    CAsset::drawStrBox(&escSaveBut, bstrsiz, SDL_PointInRect(m, &escSaveBut) ? menu.optHovCol : menu.optCol, menu.bCol);
    Font::NewCenterWrite(menu.optAText, &saveButton, menu.textCol);
    Font::NewCenterWrite(menu.optBText, &escSaveBut, menu.textCol);
  }

  if (!CInterrupt::isFlagOn(INTRPT_NEW)) {
    Font::NewCenterWrite(menu.prevTitle, &prevTitleBox, menu.fnameCol);
    Font::NewCenterWrite(menu.newTitle, &newTitleBox, menu.fnameCol);
    Font::NewCenterWrite(prevName.c_str(), &fprevBox, menu.fnameCol);

    Font::FontControl.setDynamic();
    Font::NewCenterWrite(newName.c_str(), &fnewBox, menu.fnameCol);
  }
  Font::NewCenterWrite(menu.title, &titleBox, menu.textCol);
  Font::NewCenterWrite(menu.info, &infoBox, menu.textCol);
}

std::string CFileIO::getPrevName() {
  return prevName;
}

void CFileIO::backPath() {
  if (newName.size() > 0) newName.erase(newName.end() - 1);
}

void CFileIO::addToPath(const char& addSym) {
  if (newName.size() < fname_max_size) {
    newName.push_back(addSym);
  }
}

void CFileIO::newData() {
  CArea::control.OnInit();
  CEntity::OnInit();
  CScenery::OnInit();

	CCamera::CameraControl.SetPos(0, 0);

  prevName = newName;
  newName.clear();

  pushInform(I_MAKE_NEW);
}

void CFileIO::loadData() {
  if (!CArea::control.OnLoad(newName.c_str())) {
    // problem loading the area
    newName.clear();
    return;
  }

  CCamera::CameraControl.SetPos(0, 0);

  if (!CEntity::OnLoad(newName.c_str())) {
    pushInform(I_FAIL_ENTITY);
    newName.clear();
    return;
  }

  if (!CScenery::OnLoad(newName.c_str())) {
    // problem loading 2.5D elements
    pushInform(I_FAIL_SCENERY);
    newName.clear();
    return;
  }

  pushInform(I_LOAD);

  prevName = newName;
  newName.clear();
}

void CFileIO::saveData()
{
  if (!CArea::control.OnSave(newName.c_str())) {
    pushInform(I_FAIL_SAVE);
    return;
  }
  if (!CEntity::OnSave(newName.c_str())) {
    pushInform(I_FAIL_SAVE);
    return;
  }
  if (!CScenery::OnSave(newName.c_str())) {
    pushInform(I_FAIL_SAVE);
    return;
  }

  prevName = newName;
  newName.clear();

  pushInform(I_SAVE);
}

void CFileIO::pushInform(const int& ID) {
  if (ID < I_CANCEL || ID > I_FAIL_SAVE) return;
  CInform::InfoControl.pushInform(inform[ID]);
}
