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
#include "CChangeScenery.h"
#include "CAnchorScenery.h"
#include "CLayerEditor.h"

namespace sceneryEngine {
  namespace buttons {
    namespace chScenery
    { // Change scenery button
      extern const char* const label;
      extern CButton button;
    }
    namespace chLayer
    { // Change layer button
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
  namespace anchor {
    extern const short x_grab;
    extern const short y_grab;
    extern const short x_make;
    extern const short y_make;
    extern const short x_adv;
    extern const short y_adv;
    extern const short but_w;
    extern const short but_h;
    extern CButton grab_anch;
    extern const char* const label_grab;
    extern CButton make_anch;
    extern const char* const label_make;
    extern CButton adv_anch;
    extern const char* const label_adv;
    namespace disp {
      extern const short field_w;
      extern const short field_h;
      extern const short lr_but_sz;
      extern const short x_disp;
      extern const short y_h_disp;
      extern const short y_v_disp;
      extern const SDL_Point* fieldCol;
      extern const SDL_Point* butCol;
      extern const SDL_Point* hovCol;
      extern const SDL_Rect field_h_disp;
      extern const SDL_Rect field_v_disp;
      extern const char* const label_h_disp;
      extern const char* const label_v_disp;
      extern const SDL_Rect lr_buttons[];
      enum {
        X_MINUS = 0,
        X_PLUS,
        Y_MINUS,
        Y_PLUS
      };
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
      extern const short pg_button_x;
      extern const short pg_button_y;
      extern const short pg_button_w;
      extern const short pg_button_h;
      extern const SDL_Rect prev_pg;
      extern const SDL_Rect curr_pg;
      extern const SDL_Rect next_pg;
      extern const short list_x;
      extern const short list_y;
      extern const short button_w;
      extern const short button_h;
      extern const short max_buttons;
    }
    namespace layerBrief {
      extern const SDL_Point* fieldCol;
      extern const SDL_Point* butCol;
      extern const SDL_Point* hovCol;
      extern const short list_x;
      extern const short list_y;
      extern const short field_w;
      extern const short field_h;
      extern const short buffer_h;
      extern const short num_fields;
      extern const short button_sz;
      extern const SDL_Rect fields[];
      extern const char* const labels[];
      extern const SDL_Rect l_button;
      extern const SDL_Rect r_button;
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
  bool render_active, has_rendered_active;
  short group_ID;
  short decor_ID;
  short list_page;
  short placePos;
  bool use_anchor;
  bool show_anchor;

public:
  static CSceneryEditor control;

private:
  std::vector<CButton> sceneryButtons;
  void updateSceneryButtons();
  void getPosDisplace(int& dx, int& dy, const SDL_Rect& dstR);
  void getPosDisplace(double& dx, double& dy, const SDL_Rect& dstR);
  void setOpacity(const unsigned short& A);

public:
  bool OnInit();
  bool drawBackground(int& N);
  bool drawForeground(int& N);
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);

  bool handleInterr(SDL_Event* Event);
  bool handleAddScenery(const SDL_Point* m);
  bool handleRemoveScenery(const SDL_Point* m);
  bool handleChScenery(const SDL_Point* m);
  bool handleChLayer(const SDL_Point* m);
  bool handleBriefChange(const SDL_Point* m);
  bool handleLayerMeter(const SDL_Point* m);
  bool handleOtherMeter(const SDL_Point* m);
  bool handleSwitchView(const SDL_Point* m);
  bool handleSwitchPlace(const SDL_Point* m);
  bool handleSceneryList(const SDL_Point* m);
  bool handlePlaceRelPos(const SDL_Point* m);
  bool handleGrabAnchor(const SDL_Point* m);
  bool handleMakeAnchor(const SDL_Point* m);
  bool handleAdvAnchor(const SDL_Point* m);
  bool handleArchDisplace(const SDL_Point* m);

public:
  bool OnRender(const SDL_Point* m);

private:
  bool drawWorkingScenery(const SDL_Point* m);
  bool drawChScenery(const SDL_Point* m, const bool& hov);
  bool drawChLayer(const SDL_Point* m, const bool& hov);
  bool drawLayerBrief(const SDL_Point* m, const bool& hov);
  bool drawSceneryList(const SDL_Point* m, const bool& hov);
  bool drawPlaceRelPos(const SDL_Point* m, const bool& hov);
  bool drawOpacLayer();
  bool drawOpacOther();
  bool drawSwitchView();
  bool drawSwitchPlace();
  bool drawAnchor(const SDL_Point* m);
  bool drawAnchDisplace(const SDL_Point* m);
  bool drawIntrpt(const SDL_Point* m);
};

#endif
