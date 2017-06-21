#ifndef _C_APP_H_
#define _C_APP_H_

#include <SDL.h>
#include <vector>

#include "CInterrupt.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CCamera.h"
#include "CArea.h"
#include "CUI.h"
#include "CChangeTile.h"
#include "CIO.h"
#include "CEntityEdit.h"
#include "CSceneryEdit.h"
#include "Define.h"

#include "CEditMap.h"

enum
{
  MODIFY_MAP = 0,
  MODIFY_NPC,
  REMOVE_NPC,
  MODIFY_SCENE,
  REMOVE_SCENE,
};

namespace io_ui
{
  static const char* engineName[] = {
    "Map Editor",
    "Npc Placer",
    "Npc Culler",
    "Scn Placer",
    "Scn Culler"
  };
  static const SDL_Rect engineButton[] = {
    {520, 490, 70, 16},
    {520, 506, 70, 16},
    {520, 522, 70, 16},
    {520, 538, 70, 16},
    {520, 554, 70, 16}
  };
  const short bsiz = 2;
  static const SDL_Point* engineOnCol = &color::cyan;
  static const SDL_Point* engineOffCol = &color::gray;
  static const SDL_Point* engineHvCol = &color::light_violet;
}

namespace npc_editor
{
  const short tbl_nm_x = 250;
  const short tbl_nm_y = 490;
  const short ent_nm_x = 250;
  const short ent_nm_y = 510;
  namespace but_nset
  {
    const short x = 5;
    const short y = 540;
    const short w = 75;
    const short h = 50;
  }
  // Entity Editor definitions (application static)
}

namespace scn_editor
{
  namespace popt_flip
  {
    const short x = 20;
    const short y = 510;
  }
  namespace dp_adj
  {
    const short l_x = 150;
    const short c_x = 250;
    const short u_x = 350;
    const short y = 530;
  }
  const short scn_nm_x = 250;
  const short scn_nm_y = 490;
  const unsigned short scn_nm_w = 160;
  // Scenery Editor definitions (application static)
}

class CApp : public CEvent {
private:
	SDL_Window* Map_Display;    // Edit Window
	SDL_Texture* Map_Interface; // Bordering interface for editor

	bool Running;

  SDL_Point mouse;
	int mouseX;
	int mouseY;

public:
	char* Tileset_Path;
	char* Entity_Path;

	int active_mod;
	int intrpt;
	int tabl_name_W;

public:
	CApp();

	int OnExecute();

	void OnEvent(SDL_Event* Event);

	bool EventOPTS(int mX, int mY);

	bool EventNPCedit(int mX, int mY);
	void ModEntity(int mX, int mY);
	bool AddEntity(int Xo, int Yo);
	bool SubEntity(int Xo, int Yo);

	bool EventSCNedit(int mX, int mY);
	bool CheckZup(const int& mX);
	bool CheckZdown(const int& mX);
	float GetZincrement(const int& mX, const int& Xo);
	bool CheckSCNswitch(const int& mY);
	bool CheckSCNchange(const int& mX);

	bool OnInit();
	void OnExit();

	// Handles looping calculations
	void OnLoop();

	// Uses keyboard state to detect directional input from user for moving camera
	void OnMotion(const Uint8 *state);

	// Renders graphics
	void OnRender();
  bool RenderEngine();

	bool RenderNPCedit();
	bool RenderSCNedit();
	bool RenderSCNswitch();
	bool RenderSCNdepth();
	bool RenderButton(int X, int Y, int W, int H, int bsiz, int colX, int colY, bool hl);

	// Destroys all windows, textures, surfaces, renderers...
	void OnTerminate();

	// void QueryTileset();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	void OnRButtonDown(int mX, int mY);
};

#endif
