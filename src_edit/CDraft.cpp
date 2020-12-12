#include "CDraft.h"

namespace {
  const char* const basepath = "../res_edit/drafts/";
  const char* const ext = ".png";
}

CDraft CDraft::control;

CDraft::CDraft() {
  img = NULL;
  mask = NULL;
  appl = NULL;
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

  if ((mask = CSurface::OnLoad(fname.c_str())) == NULL) {
    CInform::InfoControl.pushInform("Could not load mask image.");
    SDL_Delay(5000);
    return;
  }

  // fname = "applmask";
  // fname = basepath + fname + ext;
  //
  // if ((appl = CSurface::OnLoad(fname.c_str())) == NULL) {
  //   CInform::InfoControl.pushInform("Could not load mask target.");
  //   SDL_Delay(5000);
  //   return;
  // }


  int W, H;
  SDL_QueryTexture(mask, NULL, NULL, &W, &H);

  /* Creation of the target texture. */
  appl = CSurface::CreateTargetTexture(W, H);
  SDL_SetTextureBlendMode(appl, SDL_BLENDMODE_BLEND);
  SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_NONE);
  SDL_SetTextureBlendMode(img, SDL_BLENDMODE_ADD);
  // SDL_SetTextureBlendMode(appl, SDL_BLENDMODE_ADD);
  /* Use img object to test masking an image */
  // CSurface::SetTargetTexture(img);
  //
  // /* Let's copy the other textures onto the target texture. */
  // CSurface::OnDraw(mask, 0, 0);
  // CSurface::OnDraw(appl, 0, 0);
  //
  // CSurface::FreeTargetTexture();
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
  if (img == NULL || appl == NULL || mask == NULL) {
    SDL_Delay(1000);
    return;
  }

  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  dstWinPos.y -= (Z * TILE_SIZE);

  ////////////////////////////////////////// testing
  CSurface::SetTargetTexture(appl);

  /* Let's copy the other textures onto the target texture. */
  // CSurface::OnDraw(appl, 0, 0);
  // CSurface::OnDraw(mask, 0, 0);
  // CSurface::OnDraw(img, 0, 0);
  CSurface::OnDraw(mask, 0, 0);
  CSurface::OnDraw(img, dstWinPos.x, dstWinPos.y);

  CSurface::FreeTargetTexture();

  // CSurface::OnDraw(img, 0, 0);
  CSurface::OnDraw(appl, 0, 0);
  // CSurface::OnDraw(mask, 0, 0);
  // SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  // dstWinPos.y -= (Z * TILE_SIZE);
  // CSurface::OnDraw(img, &srcR, &dstWinPos);
  // CSurface::OnDraw(appl, &srcR, &dstWinPos);
  // CSurface::OnDraw(mask, &srcR, &dstWinPos);
}

void CDraft::OnCleanup() {
  SDL_DestroyTexture(img);
}
