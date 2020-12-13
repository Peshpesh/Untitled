#include "CDraft.h"

namespace {
  const char* const basepath = "../res_edit/drafts/";
  const char* const ext = ".png";
}

CDraft CDraft::control;

CDraft::CDraft() {
  img = NULL;
  srcR.x = srcR.y = srcR.w = srcR.h = 0;
  alpha = MAX_RGBA * 0.4;

  X = 0;
  Y = 0;
  Z = 0;
}

void CDraft::OnInit() {
  std::string fname;
  fname = "mask";
  fname = basepath + fname + ext;

  SDL_Texture* mask;
  if ((mask = CSurface::OnLoad(fname.c_str())) == NULL) {
    CInform::InfoControl.pushInform("Could not load mask image.");
    return;
  }

  test.setMask(mask);

  // int W, H;
  // SDL_QueryTexture(mask, NULL, NULL, &W, &H);

  /* Creation of the target texture. */
  // appl = CSurface::CreateTargetTexture(W, H);
  // SDL_SetTextureBlendMode(appl, SDL_BLENDMODE_BLEND);
  // SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_NONE);
  // SDL_SetTextureBlendMode(img, SDL_BLENDMODE_ADD);
}

void CDraft::OnLoad(const std::string& name) {
  if (name == "") {
    CInform::InfoControl.pushInform("No draft filename given.");
    return;
  }

  std::string fname = basepath + name + ext;

  if ((img = CSurface::OnLoad(fname.c_str())) == NULL) {
    CInform::InfoControl.pushInform("Could not load draft image.");
    return;
  }

  SDL_QueryTexture(img, NULL, NULL, &srcR.w, &srcR.h);
}

void CDraft::OnRender() {
  if (img == NULL) return;

  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  dstWinPos.y -= (Z * TILE_SIZE);

  test.resetCanvas();
  for (int i = 0; i < 1; i++) {
    test.drawToCanvas(img, srcR, dstWinPos);
  }
  test.render(0, 0);

  // CSurface::OnDraw(img, &srcR, &dstWinPos);
}

void CDraft::OnCleanup() {
  SDL_DestroyTexture(img);
}
