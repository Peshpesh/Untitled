#ifndef _C_INVENTORY_H_
#define _C_INVENTORY_H_

#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"

class CInventory : public CEvent {
  CInventory();
public:
  static CInventory control;
};

#endif
