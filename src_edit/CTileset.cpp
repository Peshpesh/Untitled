#include "CTileset.h"

std::string CTileset::filename = "default";
std::string CTileset::newFilename = "";
const char* const CTileset::ts_path = "../res_edit/tile/";
const char* const CTileset::extension = ".png";

CTileset::CTileset()
{
  //
}

void CTileset::Init()
{
  newFilename = "";
}

bool CTileset::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
  // switch (sym)
  // {
  //   case SDLK_0:		Areaname[symbolnum++] = '0'; break;
  //   case SDLK_1:		Areaname[symbolnum++] = '1'; break;
  //   case SDLK_2:		Areaname[symbolnum++] = '2'; break;
  //   case SDLK_3:		Areaname[symbolnum++] = '3'; break;
  //   case SDLK_4:		Areaname[symbolnum++] = '4'; break;
  //   case SDLK_5:		Areaname[symbolnum++] = '5'; break;
  //   case SDLK_6:		Areaname[symbolnum++] = '6'; break;
  //   case SDLK_7:		Areaname[symbolnum++] = '7'; break;
  //   case SDLK_8:		Areaname[symbolnum++] = '8'; break;
  //   case SDLK_9:		Areaname[symbolnum++] = '9'; break;
  //   case SDLK_a:		Areaname[symbolnum++] = 'A'; break;
  //   case SDLK_b:		Areaname[symbolnum++] = 'B'; break;
  //   case SDLK_c:		Areaname[symbolnum++] = 'C'; break;
  //   case SDLK_d:		Areaname[symbolnum++] = 'D'; break;
  //   case SDLK_e:		Areaname[symbolnum++] = 'E'; break;
  //   case SDLK_f:		Areaname[symbolnum++] = 'F'; break;
  //   case SDLK_g:		Areaname[symbolnum++] = 'G'; break;
  //   case SDLK_h:		Areaname[symbolnum++] = 'H'; break;
  //   case SDLK_i:		Areaname[symbolnum++] = 'I'; break;
  //   case SDLK_j:		Areaname[symbolnum++] = 'J'; break;
  //   case SDLK_k:		Areaname[symbolnum++] = 'K'; break;
  //   case SDLK_l:		Areaname[symbolnum++] = 'L'; break;
  //   case SDLK_m:		Areaname[symbolnum++] = 'M'; break;
  //   case SDLK_n:		Areaname[symbolnum++] = 'N'; break;
  //   case SDLK_o:		Areaname[symbolnum++] = 'O'; break;
  //   case SDLK_p:		Areaname[symbolnum++] = 'P'; break;
  //   case SDLK_q:		Areaname[symbolnum++] = 'Q'; break;
  //   case SDLK_r:		Areaname[symbolnum++] = 'R'; break;
  //   case SDLK_s:		Areaname[symbolnum++] = 'S'; break;
  //   case SDLK_t:		Areaname[symbolnum++] = 'T'; break;
  //   case SDLK_u:		Areaname[symbolnum++] = 'U'; break;
  //   case SDLK_v:		Areaname[symbolnum++] = 'V'; break;
  //   case SDLK_w:		Areaname[symbolnum++] = 'W'; break;
  //   case SDLK_x:		Areaname[symbolnum++] = 'X'; break;
  //   case SDLK_y:		Areaname[symbolnum++] = 'Y'; break;
  //   case SDLK_z:		Areaname[symbolnum++] = 'Z'; break;
  // }
  return true;
}

bool CTileset::OnLButtonDown(const SDL_Point* mouse)
{
  return true;
}

std::string CTileset::getFilePath()
{
  std::string filepath;
  filepath = "";
  return filepath;
}
