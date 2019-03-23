#ifndef _C_OPTIONS_H_
#define _C_OPTIONS_H_

#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"
#include "CCamera.h"
#include "CInterrupt.h"

namespace g_options {
  extern const short w_cam;
  extern const short h_cam;
  extern const short x_camxlim;
  extern const short y_camxlim;
  extern const short x_camylim;
  extern const short y_camylim;

  extern const char* const camxlim_title;
  extern const SDL_Point p_camxlim_title;
  extern const char* const camylim_title;
  extern const SDL_Point p_camylim_title;

  extern const SDL_Rect r_cam_xmin;
  extern const SDL_Rect r_cam_ymin;
  extern const SDL_Rect r_cam_xmax;
  extern const SDL_Rect r_cam_ymax;

  extern const short bsiz;
  extern const SDL_Point* in_col;
  extern const SDL_Point* off_col;
  extern const SDL_Point* off_hcol;
  extern const SDL_Point* on_col;
  extern const short max_edit_dig;
}

class COptions : public CEvent {
  COptions();

public:
  static COptions control;

private:
  int* edit_target;
  int cam_xmin;
  int cam_ymin;
  int cam_xmax;
  int cam_ymax;
  std::string edit_sval;
  bool did_edit_cam_minmax;
  bool auto_save;
  int auto_save_period;   // in minutes

public:
  void OnEvent(SDL_Event* Event);

private:
  bool handleInterr(SDL_Event* Event);

  void OnLButtonDown(int mX, int mY);
  bool handleCameraOpts(const SDL_Point* m);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void addToEdit(const char& c);
  void delFromEdit();
  void applyEdit();
  void cleartarget();

public:
  bool OnRender(const SDL_Point* m);

private:
  bool drawIntrpt(const SDL_Point* m);
  bool drawCameraOpts(const SDL_Point* m);
};


#endif
