#ifndef _C_SIMULATE_H_
#define _C_SIMULATE_H_

#include "CSimEntity.h"
#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"

enum simstate {INACTIVE, PLACE, ACTIVE, SUSPENDED};

namespace simulator {
  extern const char* const start_lab;
  extern const char* const reset_lab;
  extern const char* const suspend_lab;
  extern const char* const stop_lab;
  extern const short w_main;
  extern const short h_main;
  extern const short x_main;
  extern const short y_main;
  extern const SDL_Rect r_start;
  extern const SDL_Rect r_suspend;
  extern const SDL_Rect r_stop;
  extern const short bsiz;
  extern const SDL_Point* off_col;
  extern const SDL_Point* start_col;
  extern const SDL_Point* start_hcol;
  extern const SDL_Point* reset_col;
  extern const SDL_Point* reset_hcol;
  extern const SDL_Point* suspend_col;
  extern const SDL_Point* suspend_hcol;
  extern const SDL_Point* stop_col;
  extern const SDL_Point* stop_hcol;
  namespace camera {
    enum edit_cam {EDIT_NONE = 0, EDIT_CAM_X, EDIT_CAM_Y, EDIT_FOLLOW_W, EDIT_FOLLOW_H};
    extern const short max_edit_dig;
    extern const short w_mode;
    extern const short h_mode;
    extern const short x_mode;
    extern const short y_mode;
    extern const char* const modes_title;
    extern const char* const modes[];
    extern const SDL_Point p_modes_title;
    extern const SDL_Rect r_modes[];

    extern const short w_manual;
    extern const short h_manual;
    extern const short x_manual;
    extern const short y_manual;
    extern const char* const manual_title;
    extern const SDL_Point p_manual_title;
    extern const SDL_Rect r_cam_x;
    extern const SDL_Rect r_cam_y;

    extern const short w_follow;
    extern const short h_follow;
    extern const short x_follow;
    extern const short y_follow;
    extern const char* const follow_title;
    extern const SDL_Point p_follow_title;
    extern const SDL_Rect r_follow_w;
    extern const SDL_Rect r_follow_h;

    extern const short x_app_mf;
    extern const short y_app_mf;
    extern const short h_app_mf;
    extern const short w_app_mf;
    extern const char* const app_mf_title;
    extern const SDL_Rect r_app_mf;

    extern const short bsiz;
    extern const SDL_Point* in_col;
    extern const SDL_Point* off_col;
    extern const SDL_Point* off_hcol;
    extern const SDL_Point* on_col;
  }
}

class CSimulate : public CEvent {
  CSimulate();

public:
  static CSimulate control;
  CSimEntity hero;

private:
  simstate status;
  short cam_option;
  unsigned int follow_w;
  unsigned int follow_h;
  int cam_x, cam_y;
  short edit_xywh;
  std::string edit_sval;
  bool did_edit_xywh;

public:
  void OnLoop(const SDL_Point* m);
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);
  void moveLeft();
  void moveRight();
  void stopMoveLeft();
  void stopMoveRight();
  void jump();
  void jumpRelease();

private:
  bool handleInterr(SDL_Event* Event);

  void OnLButtonDown(int mX, int mY);
  bool handleStartSim(const SDL_Point* m);
  bool handleSuspendSim(const SDL_Point* m);
  bool handleStopSim(const SDL_Point* m);

  bool handleCameraOption(const SDL_Point* m);
  bool handleManualCam(const SDL_Point* m);
  bool handleFollowCam(const SDL_Point* m);
  bool handleApplyCam(const SDL_Point* m);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void addToEdit(const char& c);
  void delFromEdit();
  void applyEdit();

public:
  bool OnRender(const SDL_Point* m);
  bool drawHero();

private:
  bool drawDebug();
  bool drawMain(const SDL_Point* m);
  bool drawCamera(const SDL_Point* m);
  bool drawManualCam(const SDL_Point* m);
  bool drawFollowCam(const SDL_Point* m);
  bool drawApplyCam(const SDL_Point* m);
  bool drawIntrpt(const SDL_Point* m);

public:
  simstate getStatus();
  void stopSim();
  void clearxywh();
  void resetxywh();

private:
  void updateCamera();
};

#endif
