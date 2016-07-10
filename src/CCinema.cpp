#include "CCinema.h"

CCinema* CCinema::CinemaControl;

CCinema::CCinema()
{
	Scene = false;
	Progress = 0;
}

CCinema::~CCinema()
{
	//
}

bool CCinema::OnLoad(SDL_Renderer* renderer, int* prog)
{
	Progress = prog;
	return true;
}

void CCinema::OnLoop(float &pX, float &pY, SDL_Renderer* renderer)
{
	// Pure virtual
}

void CCinema::OnRender(SDL_Renderer* renderer)
{
	// Pure virtual
}

void CCinema::OnSceneLoop()
{
	// Pure virtual
}

void CCinema::OnCleanup()
{
	// Pure virtual
}
