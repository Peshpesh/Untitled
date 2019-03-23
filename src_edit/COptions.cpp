#include "COptions.h"

COptions COptions::control;

COptions::COptions() {
  edit_target = NULL;
  cam_xmin = 0;
  cam_ymin = 0;
  cam_xmax = TILE_SIZE * MAP_WIDTH;
  cam_ymax = TILE_SIZE * MAP_HEIGHT;
  did_edit_cam_minmax = false;
  auto_save = false;
  auto_save_period = 5;
}

void COptions::cleartarget() {
  edit_target = NULL;
  edit_sval.clear();
}

void COptions::OnEvent(SDL_Event* Event){
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool COptions::handleInterr(SDL_Event* Event){
  return false;
}

void COptions::OnLButtonDown(int mX, int mY){
  const SDL_Point m = {mX, mY};
  if (edit_target) cleartarget();
  if (handleCameraOpts(&m)) return;
}

bool COptions::handleCameraOpts(const SDL_Point* m) {
  using namespace g_options;
  bool retval = false;
  if (SDL_PointInRect(m, &r_cam_xmax)) {
    edit_target = &cam_xmax;
    retval = true;
  } else if (SDL_PointInRect(m, &r_cam_ymax)) {
    edit_target = &cam_ymax;
    retval = true;
  } else if (SDL_PointInRect(m, &r_cam_ymin)) {
    edit_target = &cam_ymin;
    retval = true;
  } else if (SDL_PointInRect(m, &r_cam_xmin)) {
    edit_target = &cam_xmin;
    retval = true;
  } return retval;
}

void COptions::OnKeyDown(SDL_Keycode sym, Uint16 mod){
  if (edit_target) {
    switch (sym) {
      case SDLK_0:	        addToEdit('0');	      break;
      case SDLK_1:	        addToEdit('1');	      break;
      case SDLK_2:	        addToEdit('2');	      break;
      case SDLK_3:	        addToEdit('3');	      break;
      case SDLK_4:	        addToEdit('4');	      break;
      case SDLK_5:	        addToEdit('5');	      break;
      case SDLK_6:	        addToEdit('6');	      break;
      case SDLK_7:	        addToEdit('7');	      break;
      case SDLK_8:	        addToEdit('8');	      break;
      case SDLK_9:	        addToEdit('9');	      break;
      case SDLK_BACKSPACE:  delFromEdit();        break;
      case SDLK_ESCAPE:     cleartarget();          break;
      case SDLK_RETURN:     applyEdit();          break;
      default:              break;
    }
  }
}

void COptions::addToEdit(const char& c){
  if (edit_sval.size() >= g_options::max_edit_dig) return;
  if (edit_sval == "0") {
    if (c != '0') edit_sval[0] = c;
  } else {
    edit_sval.push_back(c);
  }
}

void COptions::delFromEdit(){
  if (edit_sval.size() > 0) edit_sval.erase(edit_sval.end() - 1);
}

void COptions::applyEdit(){
  if (!edit_sval.empty()) {
    int appl_val = CAsset::strToInt(edit_sval);
    if (appl_val != *edit_target) {
      *edit_target = appl_val;
    }
  } cleartarget();
}

bool COptions::OnRender(const SDL_Point* m){
  bool intrpt = !(CInterrupt::isNone());

  if (!CAsset::drawAppFrame()) return false;

  if (!drawCameraOpts(intrpt ? NULL : m)) return false;

  if (intrpt && !drawIntrpt(m)) return false;
  return true;
}

bool COptions::drawIntrpt(const SDL_Point* m){
  return true;
}

bool COptions::drawCameraOpts(const SDL_Point* m){
  using namespace g_options;
  bool retval = true;

  std::string xmin_s = "XS " + Font::intToStr(cam_xmin);
  std::string ymin_s = "YS " + Font::intToStr(cam_ymin);
  std::string xmax_s = "XE " + Font::intToStr(cam_xmax);
  std::string ymax_s = "YE " + Font::intToStr(cam_ymax);

  Font::NewCenterWrite(camxlim_title, &p_camxlim_title);
  Font::NewCenterWrite(camylim_title, &p_camylim_title);

  if (edit_target) {
    bool edit_xmax = (edit_target == &cam_xmax);
    bool edit_ymax = edit_xmax ? false : (edit_target == &cam_ymax);
    bool edit_ymin = edit_xmax || edit_ymax ? false : (edit_target == &cam_ymin);
    bool edit_xmin = edit_xmax || edit_ymax || edit_ymin ? false : (edit_target == &cam_xmin);

    retval *= CAsset::drawStrBox(&r_cam_xmin, bsiz, edit_xmin ?
      on_col : (m && SDL_PointInRect(m, &r_cam_xmin)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_ymin, bsiz, edit_ymin ?
      on_col : (m && SDL_PointInRect(m, &r_cam_ymin)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_xmax, bsiz, edit_xmax ?
      on_col : (m && SDL_PointInRect(m, &r_cam_xmax)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_ymax, bsiz, edit_ymax ?
      on_col : (m && SDL_PointInRect(m, &r_cam_ymax)) ? off_hcol : off_col);

    Font::NewCenterWrite(edit_xmin ? edit_sval.c_str() : xmin_s.c_str(), &r_cam_xmin);
    Font::NewCenterWrite(edit_ymin ? edit_sval.c_str() : ymin_s.c_str(), &r_cam_ymin);
    Font::NewCenterWrite(edit_xmax ? edit_sval.c_str() : xmax_s.c_str(), &r_cam_xmax);
    Font::NewCenterWrite(edit_ymax ? edit_sval.c_str() : ymax_s.c_str(), &r_cam_ymax);
  } else {
    retval *= CAsset::drawStrBox(&r_cam_xmin, bsiz, (m && SDL_PointInRect(m, &r_cam_xmin)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_ymin, bsiz, (m && SDL_PointInRect(m, &r_cam_ymin)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_xmax, bsiz, (m && SDL_PointInRect(m, &r_cam_xmax)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_ymax, bsiz, (m && SDL_PointInRect(m, &r_cam_ymax)) ? off_hcol : off_col);
    Font::NewCenterWrite(xmin_s.c_str(), &r_cam_xmin);
    Font::NewCenterWrite(ymin_s.c_str(), &r_cam_ymin);
    Font::NewCenterWrite(xmax_s.c_str(), &r_cam_xmax);
    Font::NewCenterWrite(ymax_s.c_str(), &r_cam_ymax);
  }
  return retval;
}
