#ifndef _DEFINE_H_
#define _DEFINE_H_

#define MAP_WIDTH 20	// tiles
#define MAP_HEIGHT 20	// tiles

#define TILE_SIZE 32	// pixels


//  Canvas size
#define WWIDTH 640		// pixels
#define WHEIGHT 480		// pixels

//  Application size
#define EWIDTH 740      // pixels
#define EHEIGHT 580     // pixels



//---------  Application structural constants ----------//

// Directional Arrow definitions (image static)
#define L_ARROW_XO 2
#define R_ARROW_XO 17
#define U_ARROW_XO 17
#define D_ARROW_XO 2
#define L_ARROW_YO 365
#define R_ARROW_YO 365
#define U_ARROW_YO 350
#define D_ARROW_YO 350
#define ARROW_SIZE 15


// Map Editor definitions (application static)
#define TS_CHG_BUT_W 50     // Change Tileset button info
#define TS_CHG_BUT_H 40     //
#define TS_CHG_BUT_X 665    //
#define TS_CHG_BUT_Y 20     //
#define TILE_CHG_BUT_W 50   // Change Tile button info
#define TILE_CHG_BUT_H 40   //
#define TILE_CHG_BUT_X 665  //
#define TILE_CHG_BUT_Y 80   //
#define DISP_TILE_X 674     // Displayed (current) Tile info
#define DISP_TILE_Y 140     //
#define DISP_BTILE_X 674    // "..." background Tile info
#define DISP_BTILE_Y 200    //
#define DISP_FTILE_X 674    // "..." foreground Tile info
#define DISP_FTILE_Y 260    //
#define DISP_TYPE_X 674     // "..." Tile type info
#define DISP_TYPE_Y 320     //
#define DISP_SLOPE_X 674    // "..." Tile slope info
#define DISP_SLOPE_Y 380    //


// Entity Editor definitions (application static)
#define TABL_NAME_X 250
#define TABL_NAME_Y 490
#define ENT_NAME_X 250
#define ENT_NAME_Y 510
#define TBL_CHG_BUTTON_X 5
#define TBL_CHG_BUTTON_Y 540


// Scenery Editor definitions (application static)
#define SWITCHLIST_X 20
#define SWITCHLIST_Y 510
#define SCN_NAME_X 250
#define SCN_NAME_Y 490
#define SCN_NAME_W 160
#define DEPTH_COMBO_X 250
#define DEPTH_COMBO_Y 530
#define DEPTH_LOWER_X 150
#define DEPTH_UPPER_X 350


// Other definitions
#define SWITCH_XO 32
#define ON_SWITCH_YO 365
#define OFF_SWITCH_YO 350
#define SWITCH_SIZE 15
#define CHAR_HEIGHT 14
#define CHAR_WIDTH 16
#define SYM_SPACING 5
#define Z_MAGNIFIER 1000
#define Z_PRECISION 4

#endif
