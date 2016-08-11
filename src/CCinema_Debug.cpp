#include "CCinema_Debug.h"

CCinema_Debug::CCinema_Debug()
{
	Progress = 0;
	BossID = NULL;
	Bars_A = NULL;
	Bars_B = NULL;
	Scene = false;
}

bool CCinema_Debug::OnLoad(SDL_Renderer* renderer, int* prog)
{
	//	Progress = NEW_AREA;
	//	CCinema::OnLoad(renderer, prog);
	Progress = prog;
	CEntity::EntityList.push_back(new CDoor(AREA_3, 100.0, 0.0));
	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Unq_Texture,
		CEntityInfo::EntityInfoList[12].Xo, CEntityInfo::EntityInfoList[12].Yo,
		CEntityInfo::EntityInfoList[12].W, CEntityInfo::EntityInfoList[12].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 32.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 1216.0;
	return true;
}

void CCinema_Debug::OnLoop(float &pX, float &pY, SDL_Renderer* renderer)
{
	if (!(*Progress & STOLE_GEM) && pX <= 64 && pY >= 608 && pY < 640)
	{
		*Progress |= STOLE_GEM;
	}
	else if (*Progress & STOLE_GEM  && !(*Progress & KILLED_BOSS) && BossID == NULL && pX >= 608)
	{
		BossID = new CYoshi;
		BossID->Health = 20;
		BossID->Damage = 5;
		BossID->X = 680;
		BossID->Y = 540;
		BossID->OnLoad(CEntityMod::EntityControl.Com_Texture, 0, 0, 64, 64, 8);
		CEntity::EntityList.push_back(BossID);

		Bars_A = new CBars;
		Bars_B = new CBars;

		Bars_A->OnLoad(CEntityMod::EntityControl.Unq_Texture,
			CEntityInfo::EntityInfoList[5].Xo, CEntityInfo::EntityInfoList[5].Yo,
			CEntityInfo::EntityInfoList[5].W, CEntityInfo::EntityInfoList[5].H, 1);
		Bars_B->OnLoad(CEntityMod::EntityControl.Unq_Texture,
			CEntityInfo::EntityInfoList[5].Xo, CEntityInfo::EntityInfoList[5].Yo,
			CEntityInfo::EntityInfoList[5].W, CEntityInfo::EntityInfoList[5].H, 1);

		Bars_A->X = Bars_B->X = 768;
		Bars_A->Y = 576;
		Bars_B->Y = 608;
		CEntity::EntityList.push_back(Bars_A);
		CEntity::EntityList.push_back(Bars_B);
		Scene = true;
	}
	else if (!(*Progress & KILLED_BOSS) && BossID != NULL)
	{
		if (BossID->Dead)
		{
			Bars_A->Dead = true;
			Bars_B->Dead = true;
			*Progress |= KILLED_BOSS;
		}
	}
}

void CCinema_Debug::OnRender(SDL_Renderer* renderer)
{
	if (BossID != NULL)
	{
		if (CDialogue::DiaControl.OnSpeech(renderer,
			"HELLO I AM A YOSHI HI HOW ARE \
			YOU DO YOU \nLIKE APPLES I LIKE \nAPPLES \
			I HOPE YOU \nLIKE APPLES BECAUSE I DONT \
			UNDERSTAND |WHY SOME PEOPLE \nDONT LIKE \
			APPLES ITS A SHAME REALLY YOU \nSHOULD LIKE \
			THEM FOR SURE BUT IF YOU DONT I GUESS \
			I WONT HOLD IT AGAINST YOU |BUT YOURE KIND \
			OF A \nTERRIBLE PERSON IF\nTHATS THE CASE\n \
			JUST SAYING") == 0)
		{
			Scene = false;
		}
	}
}

void CCinema_Debug::OnSceneLoop()
{
	bool MovingLeft = CEntity::EntityList[0]->MoveLeft;
	bool MovingRight = CEntity::EntityList[0]->MoveRight;

	// Prevent user from moving during the scene
	if (MovingLeft) CEntity::EntityList[0]->MoveLeft = false;
	if (MovingRight) CEntity::EntityList[0]->MoveRight = false;

	// Still, do looping functions in case they're in the air or in the middle of something
	CEntity::EntityList[0]->OnLoop();

	// If the user was holding down a movement button during the scene,
	// make sure they will move in that direction if they end the scene
	// before pressing the button again (prevents ending a scene and
	// not moving despite holding the left/right buttons down already)
	CEntity::EntityList[0]->MoveLeft = MovingLeft;
	CEntity::EntityList[0]->MoveRight = MovingRight;
}

void CCinema_Debug::OnCleanup()
{
	// Pure virtual
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

CCinema_DebugB::CCinema_DebugB()
{
	Progress = 0;
	Scene = false;
}

bool CCinema_DebugB::OnLoad(SDL_Renderer* renderer, int* prog)
{
	//	Progress = NEW_AREA;
	Progress = prog;
	CEntity::EntityList.push_back(new CDoor(AREA_1, 100.0,1000.0));

	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Unq_Texture,
		CEntityInfo::EntityInfoList[12].Xo, CEntityInfo::EntityInfoList[12].Yo,
		CEntityInfo::EntityInfoList[12].W, CEntityInfo::EntityInfoList[12].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 32.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 576.0;

	CEntity::EntityList.push_back(new CShop);
	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Com_Texture,
		CEntityInfo::EntityInfoList[2].Xo, CEntityInfo::EntityInfoList[2].Yo,
		CEntityInfo::EntityInfoList[2].W, CEntityInfo::EntityInfoList[2].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 32.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 0.0;
	CEntity::EntityList.push_back(new CShop);
	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Com_Texture,
		CEntityInfo::EntityInfoList[2].Xo, CEntityInfo::EntityInfoList[2].Yo,
		CEntityInfo::EntityInfoList[2].W, CEntityInfo::EntityInfoList[2].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 64.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 0.0;
	CEntity::EntityList.push_back(new CShop);
	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Com_Texture,
		CEntityInfo::EntityInfoList[2].Xo, CEntityInfo::EntityInfoList[2].Yo,
		CEntityInfo::EntityInfoList[2].W, CEntityInfo::EntityInfoList[2].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 96.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 0.0;
	CEntity::EntityList.push_back(new CShop);
	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Com_Texture,
		CEntityInfo::EntityInfoList[2].Xo, CEntityInfo::EntityInfoList[2].Yo,
		CEntityInfo::EntityInfoList[2].W, CEntityInfo::EntityInfoList[2].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 128.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 0.0;
	CEntity::EntityList.push_back(new CShop);
	if (CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityMod::EntityControl.Com_Texture,
		CEntityInfo::EntityInfoList[2].Xo, CEntityInfo::EntityInfoList[2].Yo,
		CEntityInfo::EntityInfoList[2].W, CEntityInfo::EntityInfoList[2].H, 0) == false)
	{
		return false;
	}
	CEntity::EntityList[CEntity::EntityList.size() - 1]->X = 160.0;
	CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = 0.0;
	return true;
}

void CCinema_DebugB::OnLoop(float &pX, float &pY, SDL_Renderer* renderer)
{

}

void CCinema_DebugB::OnRender(SDL_Renderer* renderer)
{

}

void CCinema_DebugB::OnSceneLoop()
{

}

void CCinema_DebugB::OnCleanup()
{
	// Pure virtual
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

CCinema_Arena::CCinema_Arena()
{
	Progress = 0;
	Scene = false;
}

bool CCinema_Arena::OnLoad(SDL_Renderer* renderer, int* prog)
{
	//	Progress = NEW_AREA;
	Progress = prog;
	return true;
}

void CCinema_Arena::OnLoop(float &pX, float &pY, SDL_Renderer* renderer)
{

}

void CCinema_Arena::OnRender(SDL_Renderer* renderer)
{

}

void CCinema_Arena::OnSceneLoop()
{

}

void CCinema_Arena::OnCleanup()
{
	// Pure virtual
}
