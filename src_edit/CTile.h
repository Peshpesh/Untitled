#ifndef _C_TILE_H_
#define _C_TILE_H_

enum { // tile types
  TILE_TYPE_NORMAL = 0,   // Nothing unusual about these tiles
  TILE_TYPE_WATER,        // reduced speed when colliding with these tiles
  TILE_TYPE_ICE,          // increased inertia when colliding with these tiles
  TILE_TYPE_FIRE,         // persistent damage when colliding with these tiles
};

enum { // bitwise flags for tile placement in the map editor
  ENABLE_NONE    = 0,
  ENABLE_BG      = 0x00000001,    // Place background tiles
  ENABLE_FG      = 0x00000002,    // Place foreground tiles
  ENABLE_TYPE    = 0x00000004,    // Place tile types
  ENABLE_COLL    = 0x00000008,    // Place collision types
  ENABLE_BARRIER = 0x00000010,    // place barrier types (planview mode only)
};

enum { // collision types (platform mode only)
  SOLID_NONE = 0,       // tile is solid nowhere
  SOLID_ALL,            // tile is solid everywhere

  /*    GENTLE SLOPES   */
  SOLID_U_BL_MR,        // tile is solid Under Bottom-Left to Middle-Right line
  SOLID_U_ML_TR,        // tile is solid Under Middle-Left to Top-Right line
  SOLID_U_TL_MR,        // tile is solid Under Top-Left to Middle-Right line
  SOLID_U_ML_BR,        // tile is solid Under Middle-Left to Bottom-Right line
  SOLID_A_BL_MR,        // tile is solid Above Bottom-Left to Middle-Right line
  SOLID_A_ML_TR,        // tile is solid Above Middle-Left to Top-Right line
  SOLID_A_TL_MR,        // tile is solid Above Top-Left to Middle-Right line
  SOLID_A_ML_BR,        // tile is solid Above Middle-Left to Bottom-Right line

  /*    STEEP SLOPES    */
  SOLID_U_LT_MB,        // tile is solid Under Left-top to Middle-bottom line
  SOLID_U_MT_RB,        // tile is solid Under Middle-top to Right-bottom line
  SOLID_U_RT_MB,        // tile is solid Under Right-top to Middle-bottom line
  SOLID_U_MT_LB,        // tile is solid Under Middle-top to Left-bottom line

  /*    FLAT TILES      */
  SOLID_HALF_TH,        // top-half of tile is solid
  SOLID_HALF_BH,        // bottom-half of tile is solid
};

enum { // bitwise flags for tile barriers/fences (planview mode only)
  BAR_NONE  = 0,

  /*    TOTAL BARRIERS   */
  BAR_L     = 0x00000001, // Block all movement across left side
  BAR_R     = 0x00000002, // Block all movement across right side
  BAR_U     = 0x00000004, // Block all movement across up side
  BAR_D     = 0x00000008, // Block all movement across down side

  /*  OUTGOING BARRIERS  */
  BAR_OUT_L = 0x00000010, // Block outgoing movement across left side
  BAR_OUT_R = 0x00000020, // Block outgoing movement across right side
  BAR_OUT_U = 0x00000040, // Block outgoing movement across up side
  BAR_OUT_D = 0x00000080, // Block outgoing movement across down side

  /*  INCOMING BARRIERS  */
  BAR_IN_L  = 0x00000100, // Block incoming movement across left side
  BAR_IN_R  = 0x00000200, // Block incoming movement across right side
  BAR_IN_U  = 0x00000400, // Block incoming movement across up side
  BAR_IN_D  = 0x00000800, // Block incoming movement across down side
};

struct CTile {
  short    bg_ID;      // Background tile (ID) drawn
  short    fg_ID;      // Foreground tile (ID) drawn
  short    TypeID;     // Tile characteristics
  short    CollID;     // Collision characteristics
  CTile(): bg_ID(-1), fg_ID(-1), TypeID(TILE_TYPE_NORMAL), CollID(SOLID_NONE) {};
};

struct CPlanTile {
  short    ID;         // ID for the tile drawn
  short    type;       // Tile characteristics
  bool     solid;      // in planview mode, a tile is either solid or not solid
  int      barrier;    // in planview mode, tiles can have barriers on any side
  CPlanTile(): ID(-1), type(TILE_TYPE_NORMAL), solid(false), barrier(BAR_NONE) {};
};

#endif
