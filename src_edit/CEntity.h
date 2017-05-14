#ifndef _CENTITY_H_
#define _CENTITY_H_

#include <vector>
#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"

enum
{
	// Summary:
	// Player is exclusively used as a type for players only.
	// NPC types are those that the player can interact with.
	// Item types are those that the player can gather via collision.
	// Coin types are those that add to the player's purse via collision.
	ENTITY_TYPE_GENERIC = 0,	// All other types of entity (Non-player, -item, and -coin, and can't interact).
	ENTITY_TYPE_PLAYER,				// Player is exclusively used as a type for players only.
	ENTITY_TYPE_NPC,					// NPC types are those that the player can interact with.
	ENTITY_TYPE_ITEM,					// Item types are those that the player can gather via collision.
	ENTITY_TYPE_COIN,					// Coin types are those that add to the player's purse via collision.
};
enum
{
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
	ENTITY_FLAG_DAMAGE	= 0x00000008,	// Entity can deal dmg to player on contact (collision)
	ENTITY_FLAG_FRIEND	= 0x00000010,	// Entity deals dmg ONLY to enemies
	ENTITY_FLAG_MAPONLY	= 0x00000020,	// Entity DOES NOT collide with entities
	ENTITY_FLAG_BULLET	= 0x00000040,	// Entity is a bullet that "dies" on collision with map/entity
};

class CEntity {
public:
	static std::vector<CEntity*> EntityList;

protected:
	CAnimation Anim_Control;
	SDL_Texture* Tex_Entity;

public:
	float	X;
	float	Y;
	int		Xo;	// X position on entity texture
	int		Yo;	// Y position on entity texture
	int		Width;
	int		Height;
	bool	MoveLeft;
	bool	MoveRight;
//	int	AnimState;

public:
	int		Health;	// How much HP the entity has
	int		Damage;	// How much damage the entity deals
	int		Type;
	bool	Dead;
	int		Flags;
	bool	Engaged;	// Is it being interacted with?
	bool	Wet;	// Contacting water tiles
	bool	Icy;	// Contacting ice tiles

protected:
	float	SpeedX; // pixels / second
	float	SpeedY; // pixels / second
	float	AccelX; // pixels / second^2
	float	AccelY; // pixels / second^2

public:
	float	MaxSpeedX; // pixels / second
	float	MaxSpeedY; // pixels / second
	float	MaxAccelX; // pixels / second^2
	float	MaxAccelY; // pixels / second^2

protected:
	int	CurrentFrameCol;
	int	CurrentFrameRow;

protected:
	int	Col_X; // "Hitbox" X location
	int	Col_Y; // "Hitbox" Y location
	int	Col_Width; // "Hitbox" Width
	int	Col_Height; // "Hitbox" Height

public:
	CEntity();
	virtual ~CEntity();

public:
	// Load the frame info (image, etc.) for an entity.
	//
	// NOTE:
	// In the Map Editor, animation is nullified,
	// and "MaxFrames" is used to store NPC_IDs.
	virtual bool OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames);

	virtual void OnLoop();

	virtual void OnRender(SDL_Renderer* Surf_Dest);

	virtual void OnCleanup();

	virtual void OnAnimate();

	// Handles collisions (notifies Entities of recorded collisions)
	virtual bool OnCollision(CEntity* Entity);

	// Returns false if no interaction is occurring
	virtual bool OnInteract(SDL_Renderer* renderer);

public:
	// Params are in pixels/second
	bool OnMove(float MoveX, float MoveY);

	void ChkEnviro();

	void StopMove();

public:
	// Determines collisions
	bool Collides(int oX, int oY, int oW, int oH);

protected:
	bool Jumper;

public:
	bool Jump();

private:
	bool PosValid(int NewX, int NewY, bool Vertical);
	bool PosValidTile(CTile* Tile);
	bool PosValidEntity(CEntity* Entity, int NewX, int NewY);
};

class CEntityInfo
{
public:
	// static std::vector<CEntityInfo>	EntityInfoList;
	static std::vector<CEntityInfo> Com_EntityInfo;
	static std::vector<CEntityInfo> Unq_EntityInfo;

	int Xo;
	int Yo;
	int W;
	int H;
	int NumRows;
	int NumCols;
	// bool Common;

	CEntityInfo();

	// static int OnLoad(char* File);

	// static bool LoadCommons();
	static bool LoadCommon();
	static int LoadUnique(char const* File);
};

class CEntityCol
{
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