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

// Permanent option buttons (image/interface static)
#define PERM_OPTS_X 508
#define PERM_OPTS_Y 480
#define PERM_OPTS_W 232
#define PERM_OPTS_H 100
#define EDIT_BUT_X 508
#define EDIT_BUT_W 100
#define EDIT_BUT_H 33
#define MAP_BUT_Y 480
#define NPC_BUT_Y 513
#define SCN_BUT_Y 546
#define MODEL_BUT_X 608
#define MODEL_BUT_Y 480
#define MODEL_BUT_W 32
#define MODEL_BUT_H 100
#define IO_BUT_X 640
#define IO_BUT_W 100
#define IO_BUT_H 50
#define SAVE_BUT_Y 480
#define LOAD_BUT_Y 530


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
#define TS_CHG_BUT_Y 50     //
#define DISP_TILE_X 674     // Displayed (current) Tile info
#define DISP_TILE_Y 140     //
#define DISP_NAME_OFFSET 10
#define DISP_BTILE_X 674    // "..." background Tile info
#define DISP_BTILE_Y 210    //
#define DISP_FTILE_X 674    // "..." foreground Tile info
#define DISP_FTILE_Y 280    //
#define FORE_SWIT_X 642
#define FORE_SWIT_Y 262
#define ALPH_BAR_X 645
#define ALPH_BAR_W 90
#define ALPH_BAR_H 4
#define DISP_TYPE_X 674     // "..." Tile type info
#define DISP_TYPE_Y 350     //
#define ALPH_TYPE_Y 390
#define DISP_SLOPE_X 674    // "..." Tile slope info
#define DISP_SLOPE_Y 420    //
#define ALPH_SLOPE_Y 460
#define DUMMY_ENTITY_X 522
#define DUMMY_ENTITY_Y 0
#define VIEWOPTS_X 20
#define VIEWOPTS_Y 510
#define TILEOPTS_X 150
#define TILEOPTS_Y 495
#define BTILE_CHG_BUT_W 100   // Change Tile button info
#define BTILE_CHG_BUT_H 20   //
#define BTILE_CHG_BUT_X 320  //
#define BTILE_CHG_BUT_Y 510  //
#define FTILE_CHG_BUT_W 100   // Change Tile button info
#define FTILE_CHG_BUT_H 20   //
#define FTILE_CHG_BUT_X 320  //
#define FTILE_CHG_BUT_Y 540  //


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


// Change-tile interface definitions
#define MAX_TILES 8


// Other definitions
#define BUT_BORDER_SIZ 2
#define MENU_BORDER_SIZ 3
#define SWITCH_COLOR_X 40
#define ON_COLOR_Y 372
#define OFF_COLOR_Y 360
#define COLOR_SAT_Y 0
#define COLOR_PURE_Y 1
#define COLOR_DSAT_Y 2
#define RED_X 554
#define ORANGE_X 555
#define YELLOW_X 556
#define GREEN_X 557
#define CYAN_X 558
#define BLUE_X 559
#define INDIGO_X 560
#define VIOLET_X 561
#define MAGENTA_X 562
#define DARKS_X 563
#define LIGHTS_X 564
#define SWITCH_XO 32
#define ON_SWITCH_YO 365
#define OFF_SWITCH_YO 350
#define SWITCH_SIZE 15
#define CHAR_HEIGHT 14
#define CHAR_WIDTH 16
#define MINI_CHAR_SIZE 5
#define SYM_SPACING 5
#define Z_MAGNIFIER 1000
#define Z_PRECISION 4
#define MAX_RGBA 255

#endif
