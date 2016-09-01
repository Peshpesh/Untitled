#ifndef _CITEMPROCESS_H_
#define _CITEMPROCESS_H_

#include "Define_Items.h"
#include "CEntity.h"
#include "EBomb.h"
#include "CPlayer.h"
#include "CArea.h"
#include "CEntityRes.h"

class CItemProcess
{
public:
	CItemProcess();

public:
	static bool OnInit(CPlayer* Player);

	static bool OnLoop(const int& itemID);

private:
	static CPlayer* Player;

private:
	static bool UseHPUP();
	static bool UseHPDW();
	static bool UseBOMB();
	static bool UseCHARM();
	static bool UseKEY();
};
#endif
