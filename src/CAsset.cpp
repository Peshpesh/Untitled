#include "CAsset.h"

SDL_Texture* CAsset::paltex = NULL;
SDL_Texture* CAsset::arrtex = NULL;
SDL_Texture* CAsset::crttex = NULL;

namespace symbols {
  // arrow fills
  const SDL_Rect f_AL = {15, 15, ARR_SZ, ARR_SZ};
  const SDL_Rect f_AR = {0,  15, ARR_SZ, ARR_SZ};
  const SDL_Rect f_AU = {15, 0,  ARR_SZ, ARR_SZ};
  const SDL_Rect f_AD = {0,  0,  ARR_SZ, ARR_SZ};
  // arrow strokes
  const SDL_Rect s_AL = {45, 15, ARR_SZ, ARR_SZ};
  const SDL_Rect s_AR = {30, 15, ARR_SZ, ARR_SZ};
  const SDL_Rect s_AU = {45, 0,  ARR_SZ, ARR_SZ};
  const SDL_Rect s_AD = {30, 0,  ARR_SZ, ARR_SZ};
}

CAsset::CAsset() {
  //
}

bool CAsset::OnInit() {
  if ((paltex = CSurface::OnLoad("../res/palette.png")) == NULL) {
		return false;
	}
  if ((arrtex = CSurface::OnLoad("../res/arrow.png")) == NULL) {
		return false;
	}
  if ((crttex = CSurface::OnLoad("../res/carot.png")) == NULL) {
    return false;
  }

  SDL_SetTextureBlendMode(paltex, SDL_BLENDMODE_BLEND);
	return true;
}

void CAsset::queryTileDims(SDL_Texture* texture, int& w, int& h) {
  int PixWidth, PixHeight;
  SDL_QueryTexture(texture, NULL, NULL, &PixWidth, &PixHeight);
  w = PixWidth / TILE_SIZE;
  h = PixHeight / TILE_SIZE;
}

void CAsset::paletteAlpha(const short& a) {
  if (a >= 0 && a <= MAX_RGBA) {
    SDL_SetTextureAlphaMod(paltex, a);
  }
}

void CAsset::paletteBlend(const SDL_Color& rgb) {
  SDL_SetTextureColorMod(paltex, rgb.r, rgb.g, rgb.b);
}

void CAsset::paletteBlendmode(const SDL_BlendMode& mode) {
  SDL_SetTextureBlendMode(paltex, mode);
}

void CAsset::paletteReset() {
  SDL_SetTextureColorMod(paltex, rgb::white.r, rgb::white.g, rgb::white.b);
  SDL_SetTextureBlendMode(paltex, SDL_BLENDMODE_BLEND);
}

void CAsset::carotBlend(const SDL_Color& rgb) {
  SDL_SetTextureColorMod(crttex, rgb.r, rgb.g, rgb.b);
}

void CAsset::carotReset() {
  SDL_SetTextureColorMod(crttex, rgb::white.r, rgb::white.g, rgb::white.b);
}

SDL_Rect CAsset::getRect(unsigned int X, unsigned int Y, unsigned int W, unsigned int H) {
	SDL_Rect rect;
	rect.x = X;
	rect.y = Y;
	rect.w = W;
	rect.h = H;
	return rect;
}

SDL_Rect CAsset::getRect(const SDL_Point* A, const SDL_Point* B) {
  int xmin = (A->x <  B->x) ? A->x : B->x;
  int xmax = (A->x >= B->x) ? A->x : B->x;
  int ymin = (A->y <  B->y) ? A->y : B->y;
  int ymax = (A->y >= B->y) ? A->y : B->y;
  int w = xmax - xmin + 1;
  int h = ymax - ymin + 1;

  SDL_Rect rect = {xmin, ymin, w, h};
  return rect;
}

SDL_Rect CAsset::getRect(const SDL_Point& A, const SDL_Point& B) {
  int xmin = (A.x <  B.x) ? A.x : B.x;
  int xmax = (A.x >= B.x) ? A.x : B.x;
  int ymin = (A.y <  B.y) ? A.y : B.y;
  int ymax = (A.y >= B.y) ? A.y : B.y;
  int w = xmax - xmin + 1;
  int h = ymax - ymin + 1;

  SDL_Rect rect = {xmin, ymin, w, h};
  return rect;
}

SDL_Rect CAsset::getWinCentRect(const unsigned int& w, const unsigned int& h) {
  int X = (WWIDTH - w) / 2;
  int Y = (WHEIGHT - h) / 2;
  if (X < 0 || Y < 0) {
    return CAsset::getRect(0,0,0,0);
  }
  return CAsset::getRect(X, Y, w, h);
}

SDL_Rect CAsset::getTileRect(const SDL_Point* A, const SDL_Point* B) {
  int xmin = (A->x <  B->x) ? A->x : B->x;
  int xmax = (A->x >= B->x) ? A->x : B->x;
  int ymin = (A->y <  B->y) ? A->y : B->y;
  int ymax = (A->y >= B->y) ? A->y : B->y;

  xmin -= (xmin >= 0) ? (xmin % TILE_SIZE) : (bool)(xmin % TILE_SIZE) * (TILE_SIZE + (xmin % TILE_SIZE));
  ymin -= (ymin >= 0) ? (ymin % TILE_SIZE) : (bool)(ymin % TILE_SIZE) * (TILE_SIZE + (ymin % TILE_SIZE));
  xmax += (xmax >= 0) ? (TILE_SIZE - (xmax % TILE_SIZE) - 1) : -((xmax + 1) % TILE_SIZE);
  ymax += (ymax >= 0) ? (TILE_SIZE - (ymax % TILE_SIZE) - 1) : -((ymax + 1) % TILE_SIZE);

  int w = xmax - xmin + 1;
  int h = ymax - ymin + 1;

  SDL_Rect rect = {xmin, ymin, w, h};

  return rect;
}

SDL_Point CAsset::getPos(int X, int Y) {
  SDL_Point pos;
  pos.x = X;
  pos.y = Y;
  return pos;
}

SDL_Rect CAsset::getPixel(const SDL_Point* pix) {
	SDL_Rect rect;

	rect.x = pix->x;
	rect.y = pix->y;
	rect.w = 1;
	rect.h = 1;

	return rect;
}

bool CAsset::inWorkspace(const SDL_Point* pos) {
  return (pos->x >= 0 && pos->x < WWIDTH && pos->y >= 0 && pos->y < WHEIGHT);
}

bool CAsset::inWorkspace(const int& x, const int& y) {
  return (x >= 0 && x < WWIDTH && y >= 0 && y < WHEIGHT);
}

bool CAsset::compRect(const SDL_Rect& A, const SDL_Rect& B) {
  return (A.x == B.x && A.y == B.y && A.w == B.w && A.h == B.h);
}

bool CAsset::drawLine(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick) {
  return true;
}

bool CAsset::drawBox(const SDL_Rect& box, const SDL_Point* color) {
  const int defThick = 1;
  return drawBox(box, color, defThick);
}

bool CAsset::drawBox(const SDL_Rect& box, const SDL_Point* color, const int& thick) {
  if (color == NULL || thick < 0) return false;
  if (thick == 0) return true;

  SDL_Rect srcR = getPixel(color);
  SDL_Rect dstR;

  // top side
  dstR = getRect(box.x, box.y, box.w, thick);
  CSurface::OnDraw(paltex, srcR, dstR);

  // bottom side
  dstR = getRect(box.x, box.y + box.h - thick, box.w, thick);
  CSurface::OnDraw(paltex, srcR, dstR);

  // left side
  dstR = getRect(box.x, box.y, thick, box.h);
  CSurface::OnDraw(paltex, srcR, dstR);

  // right side
  dstR = getRect(box.x + box.w - thick, box.y, thick, box.h);
  CSurface::OnDraw(paltex, srcR, dstR);

  return true;
}

bool CAsset::drawBox(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick) {
  SDL_Rect box = getRect(A, B);
  return drawBox(box, color, thick);
}

bool CAsset::drawBoxFill(const SDL_Rect& box, const SDL_Point* color) {
  if (color == NULL) return false;

  SDL_Rect srcR = getPixel(color);
  if (!CSurface::OnDraw(paltex, srcR, box)) return false;

  return true;
}

bool CAsset::drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color) {
  SDL_Rect dstR = getRect(A, B);
  return drawBoxFill(dstR, color);
}

bool CAsset::drawStrBox(const SDL_Rect& box, const int& str_w, const SDL_Point* color) {
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, &palette::black, str_w)) return false;

  return true;
}

bool CAsset::drawStrBox(const SDL_Rect& box, const int& str_w, const SDL_Point* color, const SDL_Point* str_col) {
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, str_col, str_w)) return false;

  return true;
}

bool CAsset::drawBox(const SDL_Rect& box, const SDL_Color& color) {
  const int defThick = 1;
  return drawBox(box, color, defThick);
}

bool CAsset::drawBox(const SDL_Rect& box, const SDL_Color& color, const int& thick) {
  if (thick <  0) return false;
  if (thick == 0) return true;

  paletteBlend(color);
  SDL_Rect srcR = getPixel(&palette::white);
  SDL_Rect dstR;

  // top side
  dstR = getRect(box.x, box.y, box.w, thick);
  CSurface::OnDraw(paltex, srcR, dstR);

  // bottom side
  dstR = getRect(box.x, box.y + box.h - thick, box.w, thick);
  CSurface::OnDraw(paltex, srcR, dstR);

  // left side
  dstR = getRect(box.x, box.y, thick, box.h);
  CSurface::OnDraw(paltex, srcR, dstR);

  // right side
  dstR = getRect(box.x + box.w - thick, box.y, thick, box.h);
  CSurface::OnDraw(paltex, srcR, dstR);

  paletteReset();
  return true;
}

bool CAsset::drawBox(const SDL_Point& A, const SDL_Point& B, const SDL_Color& color, const int& thick) {
  SDL_Rect box = getRect(A, B);
  return drawBox(box, color, thick);
}

bool CAsset::drawBoxFill(const SDL_Rect& box, const SDL_Color& color) {
  paletteBlend(color);
  SDL_Rect srcR = getPixel(&palette::white);
  if (!CSurface::OnDraw(paltex, srcR, box)) return false;
  paletteReset();
  return true;
}

bool CAsset::drawBoxFill(const SDL_Point& A, const SDL_Point& B, const SDL_Color& color) {
  SDL_Rect dstR = getRect(A, B);
  return drawBoxFill(dstR, color);
}

bool CAsset::drawRotBoxFill(const SDL_Rect& box, const SDL_Color& color, const double& r) {
  paletteBlend(color);
  SDL_Rect srcR = getPixel(&palette::white);
  if (!CSurface::OnDraw(paltex, srcR, box, r)) return false;
  paletteReset();
  return true;
}

bool CAsset::drawStrBox(const SDL_Rect& box, const int& str_w, const SDL_Color& color) {
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, &palette::black, str_w)) return false;
  return true;
}

bool CAsset::drawStrBox(const SDL_Rect& box, const int& str_w, const SDL_Color& color, const SDL_Color& str_col) {
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, str_col, str_w)) return false;
  return true;
}

bool CAsset::drawRotStrBox(const SDL_Rect& box, const int& str_w, const SDL_Color& color, const SDL_Color& str_col, const double& r) {
  if (!drawRotBoxFill(box, str_col, r)) return false;
  const SDL_Rect infill = {box.x + str_w, box.y + str_w, box.w - (str_w * 2), box.h - (str_w * 2)};
  if (!drawRotBoxFill(infill, color, r)) return false;
  return true;
}

bool CAsset::fillScreen() {
  return fillScreen(rgb::black);
}

bool CAsset::fillScreen(const SDL_Color& color) {
  SDL_Rect f = {0, 0, WWIDTH, WHEIGHT};
  return drawBoxFill(f, color);
}

bool CAsset::drawSmCircleMeter(const int& X, const int& Y, const int& val, const int& maxval) {
  using namespace carot;

  SDL_Rect dstR = {X, Y, sm_half_l.w, sm_half_l.h};
  SDL_Point anch = {sm_half_l.w - 1, sm_half_l.h / 2};
  float frac = float(val) / maxval;

  if (val <= 0 || val >= maxval) {
    if (val <= 0) carotBlend(rgb::dark_blue);
    else carotBlend(rgb::light_green);

    CSurface::OnDraw(crttex, sm_half_l, dstR);
    CSurface::OnDraw(crttex, sm_half_l, dstR, &anch, 180.0);

    carotBlend(rgb::black);
    dstR.w = sm_case.w;
    CSurface::OnDraw(crttex, sm_case, dstR);
  } else if (frac >= 0.5f) {
    carotBlend(rgb::dark_blue);
    CSurface::OnDraw(crttex, sm_half_l, dstR, &anch, 180.0);

    carotBlend(rgb::light_green);
    double rot = 360.0 - (((frac - 0.5f) / 0.5f) * 180.0);
    CSurface::OnDraw(crttex, sm_half_l, dstR);
    CSurface::OnDraw(crttex, sm_half_l, dstR, &anch, rot);

    carotBlend(rgb::black);
    dstR.w = sm_case.w;
    CSurface::OnDraw(crttex, sm_case, dstR);
  } else if (frac < 0.5f) {
    carotBlend(rgb::light_green);
    CSurface::OnDraw(crttex, sm_half_l, dstR);

    carotBlend(rgb::dark_blue);
    CSurface::OnDraw(crttex, sm_half_l, dstR, &anch, 180.0);
    double rot = 360.0 * (1.0 - frac);
    CSurface::OnDraw(crttex, sm_half_l, dstR, &anch, rot);

    carotBlend(rgb::black);
    dstR.w = sm_case.w;
    CSurface::OnDraw(crttex, sm_case, dstR);
  }
  return true;
}

bool CAsset::drawCircle(const int& Xo, const int& Yo, const int& r) {
  int x = r-1;
  int y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (r << 1);

  while (x >= y) {
      // drawBoxFill({Xo - x, Yo + y, 2*x, 1}, rgb::cyan);
      //
      // drawBoxFill({Xo - x, Yo - y, 2*x, 1}, rgb::cyan);
      //
      // drawBoxFill({Xo - y, Yo + x, 2*y, 1}, rgb::cyan);
      //
      // drawBoxFill({Xo - y, Yo - x, 2*y, 1}, rgb::cyan);

      // drawBoxFill({Xo + x, Yo + y, 1, 1}, rgb::red);
      // drawBoxFill({Xo + y, Yo + x, 1, 1}, rgb::red);
      // drawBoxFill({Xo - y, Yo + x, 1, 1}, rgb::red);
      // drawBoxFill({Xo - x, Yo + y, 1, 1}, rgb::red);
      // drawBoxFill({Xo - x, Yo - y, 1, 1}, rgb::red);
      // drawBoxFill({Xo - y, Yo - x, 1, 1}, rgb::red);
      // drawBoxFill({Xo + y, Yo - x, 1, 1}, rgb::red);
      // drawBoxFill({Xo + x, Yo - y, 1, 1}, rgb::red);

      if (err <= 0) {
          y++;
          err += dy;
          dy += 2;
      }
      if (err > 0) {
          x--;
          dx += 2;
          err += dx - (r << 1);
      }
  }
  return true;
}

bool CAsset::drawArrow(const SDL_Rect& dstR, const char& dir, const SDL_Color* rgb) {
  using namespace symbols;

  bool retval = false;

  SDL_SetTextureColorMod(arrtex, rgb->r, rgb->g, rgb->b);

  switch (dir)
  {
    case 'L': retval = CSurface::OnDraw(arrtex, s_AL, dstR); break;
    case 'R': retval = CSurface::OnDraw(arrtex, s_AR, dstR); break;
    case 'U': retval = CSurface::OnDraw(arrtex, s_AU, dstR); break;
    case 'D': retval = CSurface::OnDraw(arrtex, s_AD, dstR); break;
    default: break;
  }

  return retval;
}

bool CAsset::drawArrowFill(const SDL_Rect& dstR, const char& dir, const SDL_Color* rgb) {
  using namespace symbols;

  bool retval = false;

  SDL_SetTextureColorMod(arrtex, rgb->r, rgb->g, rgb->b);

  switch (dir)
  {
    case 'L': retval = CSurface::OnDraw(arrtex, f_AL, dstR); break;
    case 'R': retval = CSurface::OnDraw(arrtex, f_AR, dstR); break;
    case 'U': retval = CSurface::OnDraw(arrtex, f_AU, dstR); break;
    case 'D': retval = CSurface::OnDraw(arrtex, f_AD, dstR); break;
    default: break;
  }

  return retval;
}

bool CAsset::drawStrArrow(const SDL_Rect& dstR, const char& dir, const SDL_Color* rgb)
{
  if (!drawArrowFill(dstR, dir, rgb))       return false;
  if (!drawArrow(dstR, dir, &rgb::black))   return false;

  return true;
}

bool CAsset::drawStrArrow(const SDL_Rect& dstR, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb)
{
  if (!drawArrowFill(dstR, dir, rgb))   return false;
  if (!drawArrow(dstR, dir, str_rgb))   return false;

  return true;
}

bool CAsset::drawArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawArrow(dstR, dir, rgb);
}

bool CAsset::drawArrowFill(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawArrowFill(dstR, dir, rgb);
}

bool CAsset::drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawStrArrow(dstR, dir, rgb);
}

bool CAsset::drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawStrArrow(dstR, dir, rgb, str_rgb);
}

void CAsset::OnCleanup() {
  SDL_DestroyTexture(paltex);
  SDL_DestroyTexture(arrtex);
  SDL_DestroyTexture(crttex);
}

void CAsset::debug_a() {
  static double v = 0.0;
  static double vi = 3.1415926*9;
  static short i = 0;
  static const SDL_Color* lol[] = {
    &rgb::light_cyan,
    &rgb::light_green,
    &rgb::light_red,
    &rgb::yellow,
    &rgb::light_violet,
    &rgb::orange,
    &rgb::white,
  };
  static int x = 0;
  static int xi = vi;
  static int y = 0;
  static int yi = vi;
  paletteBlend(*lol[i]);
  SDL_Rect srcR = getPixel(&palette::white);
  SDL_Rect dstR = {x,y,100,100};
  CSurface::OnDraw(paltex, srcR, dstR, v);
  paletteReset();
  v += vi;
  i++;
  // if (v > 360.0 || v < 0.0) vi = -vi;
  if (v > 360.0) v-= 360.0;
  if (i > 6) i = 0;
  x += xi;
  y += yi;
  if (yi > 0 && y + 100 > WHEIGHT) yi = -yi;
  if (yi < 0 && y < 0) yi = -yi;
  if (xi > 0 && x + 100 > WWIDTH) xi = -xi;
  if (xi < 0 && x < 0) xi = -xi;
}
