#ifndef _C_ENTITY_H_
#define _C_ENTITY_H_

#include <vector>
#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"

// enum {
	// Summary:
	// Player is exclusively used as a type for players only
	// NPC types are those that the player can interact with.
	// Item types are those that the player can gather via collision.
	// Coin types are those that add to the player's purse via collision.
	// ENTITY_TYPE_GENERIC = 0,	// All other types of entity (Non-player, -item, and -coin, and can't interact).
	// ENTITY_TYPE_PLAYER,				// Player is exclusively used as a type for players only.
	// ENTITY_TYPE_NPC,					// NPC types are those that the player can interact with.
	// ENTITY_TYPE_ITEM,					// Item types are those that the player can gather via collision.
	// ENTITY_TYPE_COIN,					// Coin types are those that add to the player's purse via collision.
// };

enum Status {
	STAT_NONE = 0,								// No abilities
	STAT_INVIN 	= 0x00000001,			// Invincibility
	STAT_INVIS 	= 0x00000002,			// Invisibility
	STAT_HASTE 	= 0x00000004,			// Increased speed
	STAT_WINGS 	= 0x00000008,			// Ability to fly
	STAT_GILLS 	= 0x00000010,			// Infinite breath underwater
	STAT_TOXIC 	= 0x00000020,			// Poisoned
	STAT_SLOW 	= 0x00000040,			// Decreased speed
};

enum {
	// Summary:
	// Gravity flag causes an entity to have a constant downward acceleration.
	// Ghost allows an entity to move through walls, but will still trigger entity collisions.
	// Hollow allows entities to translate through itself, but other collision effects still occur.
	// Damage allows an entity to deal direct damage to the player by simple collision.
	// Friend means that the entity can deal damage on contact, but NOT to the player.
	// Maponly allows an entity to avoid colliding with other entities.
	ENTITY_FLAG_NONE		= 0,
	ENTITY_FLAG_GRAVITY = 0x00000001,	// Entity subject to gravity
	ENTITY_FLAG_GHOST		= 0x00000002,	// Entity can translate thru walls
	ENTITY_FLAG_HOLLOW	= 0x00000004,	// Entity allows other entities to translate thru it (collisions ON)
	// ENTITY_FLAG_DAMAGE	= 0x00000008,	// Entity can deal dmg to player on contact (collision)
	// ENTITY_FLAG_FRIEND	= 0x00000010,	// Entity deals dmg ONLY to enemies
	// ENTITY_FLAG_MAPONLY	= 0x00000020,	// Entity DOES NOT collide with entities
	// ENTITY_FLAG_BULLET	= 0x00000040,	// Entity is a bullet that "dies" on collision with map/entity
};

struct EntityTexInfo {
  int group_ID;
  SDL_Texture* img;
};

class CEntity {
public:
	static std::vector<CEntity*> EntityList;
	static std::vector<EntityTexInfo> TextureList;

protected:
	CAnimation Anim_Control;

public:
	SDL_Texture* sprtSrc;
	float	X;	// sprite x-position
	float	Y;  // sprite y-position
	SDL_Rect spriteR;	// sprite position & size on texture
	SDL_Rect hitboxR;	// X and Y are offset values relative to sprite
	bool	MoveLeft;
	bool	MoveRight;
	bool	Permanent;	// does this entity have run-time permanence

public:
	int		MaxHealth; // Maximum amount of HP the entity can have
	int		Health;	// How much HP the entity has
	int		Damage;	// How much damage the entity deals (direct contact)
	bool	Dead;		// is Entity dead
	int		Flags;	// Flags for this Entity
	int		Stat;		// Statuses for this Entity

	// int	Type;
	// bool	Engaged;	// Is it being interacted with?
	// bool	Wet;	// Contacting water tiles
	// bool	Icy;	// Contacting ice tiles

protected:
	float	SpeedX; // pixels / idealframe
	float	SpeedY; // pixels / idealframe
	float	AccelX; // pixels / idealframe^2
	float	AccelY; // pixels / idealframe^2

public:
	float	MaxSpeedX; // pixels / idealframe
	float	MaxSpeedY; // pixels / idealframe
	float	MaxAccelX; // pixels / idealframe^2
	float	MaxAccelY; // pixels / idealframe^2

protected:
	bool Jumper;
	bool Grounded;

protected:
	int	CurrentFrameCol;
	int	CurrentFrameRow;

public:
	CEntity();
	virtual ~CEntity();

public:
	// Load the frame info (image, etc.) for an entity.
	virtual void OnLoad(SDL_Texture* img, const SDL_Rect& sprR, const SDL_Rect& hitR, const int& maxFrames);

	virtual void OnLoop();

	virtual void OnRender();

	virtual void OnCleanup();

	virtual void OnAnimate();

	// Handles collisions (notifies Entities of recorded collisions)
	virtual bool OnCollision(CEntity* Entity);

	// Returns false if no interaction is occurring
	virtual bool OnInteract();

protected:
	// bool OnMove(float MoveX, float MoveY);

	// void ChkEnviro();

	// void StopMove();

public:
	// Checks if the entity's hitbox intersects passed hitbox
	// bool Collides(const int& oXl, const int& oYt, const int& oXr, const int& oYb);

public:
	bool Jump();

protected:
	// void Translate(double NewX, double NewY);
	// bool CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb);
	// bool CollEntity(CEntity* Entity, const int& destXl, const int& destXr, const int& destYt, const int& destYb);
	// int CollGround(const int& collID, const int& Xrel, const int& Yrel);
	// bool PosValidEntity(CEntity* Entity, int NewX, int NewY);

	//	Debug members
public:
	void GetPos(float& X, float& Y);
	// void GetPushY(int& pushY);
};

// class CEntityInfo
// {
// public:
// 	static std::vector<CEntityInfo> Com_EntityInfo;
// 	static std::vector<CEntityInfo> Unq_EntityInfo;
//
// 	int Xo;
// 	int Yo;
// 	int W;
// 	int H;
// 	int NumRows;
// 	int NumCols;
//
// 	CEntityInfo();
//
// 	static bool LoadCommon();
// 	static int LoadUnique(char const* File);
// };

class CEntityCol {
public:
	// List of queued collisions between two entities
	static std::vector<CEntityCol> EntityColList;

public:
	CEntity* EntityA;
	CEntity* EntityB;

public:
	CEntityCol();
};
#endif
