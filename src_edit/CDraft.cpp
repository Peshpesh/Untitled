#include "CDraft.h"

namespace {
  const char* const basepath = "../res_edit/drafts/";
  const char* const ext = ".png";
}

CDraft CDraft::control;

CDraft::CDraft() {
  img = NULL;
  srcR.x = srcR.y = srcR.w = srcR.h = 0;
  alpha = MAX_RGBA * 0.5;

  X = Y = Z = 0;
  name = "";

  hidden = false;
  draw_on_top = true;
}

void CDraft::OnInit() {
  // std::string fname;
  // fname = "mask";
  // fname = basepath + fname + ext;
  //
  // SDL_Texture* mask;
  // if ((mask = CSurface::OnLoad(fname.c_str())) == NULL) {
  //   CInform::InfoControl.pushInform("Could not load mask image.");
  //   return;
  // }
  //
  // fname = "applmask";
  // fname = basepath + fname + ext;
  //
  // SDL_Texture* appl;
  // if ((appl = CSurface::OnLoad(fname.c_str())) == NULL) {
  //   CInform::InfoControl.pushInform("Could not load appl image.");
  //   return;
  // }
  //
  // if ((test_compound = CMask::createCompound(appl, mask)) == NULL) {
  //   CInform::InfoControl.pushInform("Could not load compound image.");
  //   return;
  // }
}

void CDraft::OnLoad(const std::string& name) {
  if (name == "") {
    CInform::InfoControl.pushInform("No draft filename given.");
    return;
  } else if (name == this->name) {
    CInform::InfoControl.pushInform("Draft file is already loaded.");
    return;
  }

  std::string fname = basepath + name + ext;

  SDL_Texture* tmptxt = NULL;
  if ((tmptxt = CSurface::OnLoad(fname.c_str())) == NULL) {
    CInform::InfoControl.pushInform("Could not load draft image.");
  } else {
    CInform::InfoControl.pushInform("Requested draft loaded.");
    SDL_DestroyTexture(img);
    img = tmptxt;
    this->name = name;
    SDL_SetTextureAlphaMod(img, alpha);
    SDL_QueryTexture(img, NULL, NULL, &srcR.w, &srcR.h);
  }
}

void CDraft::OnRender() {
  if (img == NULL || hidden) return;

  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  dstWinPos.y -= (Z * TILE_SIZE);
  CSurface::OnDraw(img, &srcR, &dstWinPos);

  // // test.clearCanvas();
  // // test.beginDrawing();
  // SDL_Point origin;
  // origin.x = 0;
  // origin.y = 0;
  //
  // SDL_Rect testR = srcR;
  // testR.x = 0; //dstWinPos.x;
  // testR.y = 0; //dstWinPos.y;
  // testR.w = 200;
  // testR.h = 200;
  //
  // CSurface::OnDraw(test_compound, &testR, &origin);
}

void CDraft::OnCleanup() {
  name.clear();
  SDL_DestroyTexture(img);
}
