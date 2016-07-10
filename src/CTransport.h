#ifndef _CTRANSPORT_H_
#define _CTRANSPORT_H_

#include "CEntity.h"
#include "CEntityMod.h"
#include "CArea.h"
#include "CCinema.h"
#include "CGamedata.h"

/*
enum Destinations
{
	AREA_1 = 0,
	AREA_3 = 1,
};
*/

class CTransport
{
public:
	static CTransport		Transporter;

public:

	CTransport();

	bool OnInit();

	bool OnLoad();

	bool OnRequest(const int &area, const float &dX, const float &dY);

	void OnRequest();

	void OnTransport(float &pX, float &pY, SDL_Renderer* renderer);

	void OnRender(SDL_Renderer* renderer);

	void OnCleanup();

public:
	bool Relocate;		// True if a new area is to be loaded on next program loop
	int Destination;	// Enumerated value for the area loaded in OnTransport
	int Origin;			// Enumerated value for the area previously loaded
	float rX;			// x-position to put player in OnTransport
	float rY;			// y-position to put player in OnTransport
};


#endif