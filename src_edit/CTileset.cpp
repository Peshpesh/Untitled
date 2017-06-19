#include "CTileset.h"

std::string CTileset::filename = "default";
std::string CTileset::newFilename = "";
const char* const CTileset::ts_path = "../res_edit/tile/";
const char* const CTileset::extension = ".png";

CTileset::CTileset()
{
  //
}

bool CTileset::OnLClick(const SDL_Point* mouse)
{
  return true;
}

std::string CTileset::getFilePath()
{
  std::string filepath;
  filepath = "";
  return filepath;
}
