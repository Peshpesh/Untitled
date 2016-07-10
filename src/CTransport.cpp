#include "CTransport.h"
#include "CCinema_Debug.h"

CTransport CTransport::Transporter;

CTransport::CTransport()
{
	Relocate = true;
	Origin = -1;
	Destination = ARENA;
	rX = rY = 300.0f;
}

bool CTransport::OnInit()
{
	return true;
}

bool CTransport::OnLoad()
{
	return true;
}

bool CTransport::OnRequest(const int &area, const float &dX, const float &dY)
{
	Relocate = true;
	this->Destination = area;
	this->rX = dX;
	this->rY = dY;
	return true;
}

void CTransport::OnRequest()
{
	Relocate = true;
}

void CTransport::OnTransport(float &pX, float &pY, SDL_Renderer* renderer)
{
	// Load the appropriate area, entity list, and situational details (CCinema)
	switch (Destination)
	{
		case AREA_1:
		{
			CArea::AreaControl.OnLoad("../data/maps/1.area", renderer);
			CEntityMod::EntityControl.LoadNPCs("../data/maps/1.ent", renderer);

			delete CCinema::CinemaControl;
			CCinema::CinemaControl = new CCinema_Debug;
			break;
		}
		case AREA_3:
		{
			CArea::AreaControl.OnLoad("../data/maps/3.area", renderer);
			CEntityMod::EntityControl.LoadNPCs("../data/maps/3.ent", renderer);

			delete CCinema::CinemaControl;
			CCinema::CinemaControl = new CCinema_DebugB;
			break;
		}
		case ARENA:
		{
			CArea::AreaControl.OnLoad("../data/maps/ARENA.area", renderer);
			CEntityMod::EntityControl.LoadNPCs("../data/maps/ARENA.ent", renderer);

			delete CCinema::CinemaControl;
			CCinema::CinemaControl = new CCinema_Arena;
			break;
		}
		default: break;
	}

	// Give recorded progress in the area to CinemaControl
	CCinema::CinemaControl->OnLoad(renderer, &CGameData::GameControl.ProgressList[Destination]);

	// Relocate the player in X and Y in new area
	pX = rX;
	pY = rY;

	// For the next transportation, the origin will be the previous destination.
	// I.e., where we've just arrived.
	Origin = Destination;

	// Relocation completed; turning off the flag
	Relocate = false;
}

void CTransport::OnRender(SDL_Renderer* renderer)
{

}

void CTransport::OnCleanup()
{
	Relocate = true;
	Origin = -1;
	Destination = ARENA;
	rX = rY = 300.0f;
}
