#include "CInventory.h"

CItem CInventory::fetchItem(const short& ID) {
  using namespace items;
  CItem val;
  switch (ID) {
    case JOURNAL: {
      val.equip = false;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
    case PEWPEW: {
      val.equip = true;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
    case MEDIKIT: {
      val.equip = false;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
    case WARMGLOVES: {
      val.equip = false;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
    case ROOMKEY_RUINS: {
      val.equip = false;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
    case TRANQUIL_STONE: {
      val.equip = false;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
    default: {
      val.equip = false;
      val.num = 1;
      val.maxnum = 1;
      val.spr = CAsset::getRect(0,0,1,1);
      break;
    }
  }
  val.ID = ID;
  return val;
}

void CInventory::fetchInfo(const short& ID, std::string& name, std::string& about) {
  using namespace items;
  switch (ID) {
    case JOURNAL: {
      name = "Journal";
      about = "A red journal. It's got my name on it.";
      break;
    }
    case PEWPEW: {
      name = "Pew Gun";
      about = "A small pellet gun.";
      break;
    }
    case MEDIKIT: {
      name = "Medikit";
      about = "Bandages included. (Heals 10 HP.)";
      break;
    }
    case WARMGLOVES: {
      name = "Warm Gloves";
      about = "Some warm gloves that Sena gave me. They're a little big...";
      break;
    }
    case ROOMKEY_RUINS: {
      name = "Room Key";
      about = "A key to Leplacia's cabin.";
      break;
    }
    case TRANQUIL_STONE: {
      name = "Tranquil Stone";
      about = "A cloudy, blue-green crystal attached to a broken string.";
      break;
    }
    default: {
      name = "LOL";
      about = ":D";
      break;
    }
  }
}
