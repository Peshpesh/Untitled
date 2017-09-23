#ifndef _C_SCENERYEDITOR_H_
#define _C_SCENERYEDITOR_H_

#include "CButton.h"
#include "CMeter.h"
#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"
#include "CScenery.h"
#include "CSceneryData.h"

namespace sceneryEngine
{
  namespace buttons {
    namespace chScenery
    { // Change scenery button
      extern const char* const label;
      extern CButton button;
    }
    namespace placeRelPos {
      extern const SDL_Point* offCol;
      extern const SDL_Point* hovCol;
      extern const SDL_Point* onCol;
      extern const short x;
      extern const short y;
      extern const short sz;
      extern CButton buttons[];
    }
  }
  namespace switches {
    extern const short sz;
    extern const short lab_y_offset;
    extern const short lab_x_offset;
    namespace view {
      extern const SDL_Point* offCol;
      extern const SDL_Point* onCol;
      extern const short x;
      extern const char* const labels[];
      extern CButton buttons[];
    }
    namespace place {
      extern const SDL_Point* offCol;
      extern const SDL_Point* onCol;
      extern const short x;
      extern const char* const labels[];
      extern CButton buttons[];
    }
  }
  namespace meters {
    namespace opacLayer
    {
      extern const char* const label;
      extern CMeter meter;
    }
    namespace opacOther
    {
      extern const char* const label;
      extern CMeter meter;
    }
  }
  namespace misc {
    namespace sceneryButtons {
      extern const SDL_Point* offCol;
      extern const SDL_Point* onCol;
      extern const SDL_Point* hovCol;
      extern const short list_x;
      extern const short list_y;
      extern const short button_w;
      extern const short button_h;
      extern const short max_buttons;
    }
    namespace placeRelPos {
      extern const short numpos_x;
      extern const short numpos_y;
      enum {
        TOP_LEFT = 0,
        TOP_CENTER,
        TOP_RIGHT,
        LEFT,
        CENTER,
        RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
      };
    }
  }
} // Scenery engine namespaces //


class CSceneryEditor : public CEvent {
  CSceneryEditor();

  bool showScenery;
  bool showWorkScenery;
  unsigned short layer;
  unsigned short layer_alpha;
  unsigned short other_alpha;
  short group_ID;
  short scene_ID;
  short placePos;
  bool snap_scenery;

public:
  static CSceneryEditor control;

private:
  std::vector<CButton> sceneryButtons;
  void updateSceneryButtons();
  void getPosDisplace(int& dx, int& dy, const SDL_Point* m, const SDL_Rect& dstR);

public:
  bool OnInit();
  bool drawBackground();
  bool drawForeground();
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);

  bool handleAddScenery(const SDL_Point* m);
  bool handleChScenery(const SDL_Point* m);
  bool handleLayerMeter(const SDL_Point* m);
  bool handleOtherMeter(const SDL_Point* m);
  bool handleSwitchView(const SDL_Point* m);
  bool handleSwitchPlace(const SDL_Point* m);
  bool handleSceneryList(const SDL_Point* m);
  bool handlePlaceRelPos(const SDL_Point* m);

public:
  bool OnRender(const SDL_Point* m);

private:
  bool drawChScenery(const SDL_Point* m, const bool& hov);
  bool drawSceneryList(const SDL_Point* m, const bool& hov);
  bool drawPlaceRelPos(const SDL_Point* m, const bool& hov);
  bool drawOpacLayer();
  bool drawOpacOther();
  bool drawSwitchView();
  bool drawSwitchPlace();
  bool drawIntrpt(const SDL_Point* m);
};

#endif
