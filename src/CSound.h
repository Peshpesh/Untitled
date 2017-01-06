#ifndef _C_SOUND_H_
#define _C_SOUND_H_

#include <SDL.h>
#include <SDL_mixer.h>

// Most music tracks will have enumerated taxonomy of the form:
//    "MUS_(I|L)_(BASENAME)"
// "I" Tracks are tracks that lead into a looping track (introductory)
// "L" Tracks are meant to loop after the corresponding "I" track is done
enum track
{
  // Testing Tracks
  MUS_HOLLOW = 0,
  // External (non-game) Tracks
  MUS_I_TITLE,              MUS_L_TITLE,    //  Title-screen music
  MUS_I_DIARY,              MUS_L_DIARY,    //  Leplacia's Encyclopaedia
  MUS_I_BADEND,             MUS_L_BADEND,   //  Worst ending music
  MUS_I_GOODEND,            MUS_L_GOODEND,  //  Good (normal) ending music
  MUS_I_BESTEND,            MUS_L_BESTEND,  //  Best (complete) ending music
  // Regional Tracks
  MUS_I_HOME,               MUS_L_HOME,         //  Played when you're home...
  MUS_I_YRAI,               MUS_L_YRAI,         //  Yrai
  MUS_I_RHIGHID,            MUS_L_RHIGHID,      //  Rhighid Range
  MUS_I_RUINS,              MUS_L_RUINS,        //  Avan Ruins
  MUS_I_AVA,                MUS_L_AVA,          //  Ava (pre-ruin)
  MUS_I_UNDERGROUND,        MUS_L_UNDERGROUND,  //  Beneath Yrai
  MUS_I_VIRIDIA,            MUS_L_VIRIDIA,      //  Viridia
  MUS_I_OCEAN,              MUS_L_OCEAN,        //  Ocean
  MUS_I_WASTES,             MUS_L_WASTES,       //  Polar Wastes
  MUS_I_HILLS,              MUS_L_HILLS,        //  Scarlet Hills
  MUS_I_VOLCANO,            MUS_L_VOLCANO,      //  Volcano
  MUS_I_MORIV,              MUS_L_MORIV,        //  Moriv
  MUS_I_HIGHLAND,           MUS_L_HIGHLAND,     //  Highlands
  MUS_I_CAVERN,             MUS_L_CAVERN,       //  Cerulean Caverns
  MUS_I_LEXI,               MUS_L_LEXI,         //  Lexi Islands
  MUS_I_KNOWLEDGE,          MUS_L_KNOWLEDGE,    //  House of Knowledge
  MUS_I_VOID,               MUS_L_VOID,         //  Nowhere
  MUS_I_PEAK,               MUS_L_PEAK,         //  Erin's Peak
  // Character/Boss Tracks
  MUS_I_GEN_ACT_I,          MUS_L_GEN_ACT_I,    //  Generic bosses near the story's beginning (Act I)
  MUS_I_GEN_ACT_II,         MUS_L_GEN_ACT_II,   //  Generic bosses near the start of conflict (Act II)
  MUS_I_GEN_ACT_III,        MUS_L_GEN_ACT_III,  //  Generic bosses in the middle of the story (Act III)
  MUS_I_GEN_ACT_IV,         MUS_L_GEN_ACT_IV,   //  Generic bosses near the end of the story (Act IV)
  MUS_I_GEN_ACT_V,          MUS_L_GEN_ACT_V,    //  Generic bosses after the end of the story (Act V)
  MUS_I_EARTH,              MUS_L_EARTH,        //  Earth phoenix
  MUS_I_WATER,              MUS_L_WATER,        //  Water phoenix
  MUS_I_FIRE,               MUS_L_FIRE,         //  Fire phoenix
  MUS_I_WIND,               MUS_L_WIND,         //  Wind phoenix
  MUS_I_LORA,               MUS_L_LORA,         //  Lora theme
  MUS_I_VIDE,               MUS_L_VIDE,         //  Vide theme
  MUS_I_AWAN,               MUS_L_AWAN,         //  Awan theme
  MUS_I_ICARID,             MUS_L_ICARID,       //  Icarid theme
  MUS_I_ZACH,               MUS_L_ZACH,         //  Zacharia theme
  MUS_I_FINAL,              MUS_L_FINAL,        //  The last battle
  MUS_I_VERY,               MUS_L_VERY,         //  The VERY last battle (I promise)
  MUS_I_LEPPY,              MUS_L_LEPPY,        //  You don't want none of this
  // Situational Tracks
  MUS_I_SHOP,               MUS_L_SHOP,               //  Shopping
  MUS_I_STRANGER,           MUS_L_STRANGER,           //  Confrontation
  MUS_I_GIFT,               MUS_L_GIFT,               //  The gift
  MUS_I_CALAMITY,           MUS_L_CALAMITY,           //  A great calamity afoot
  MUS_I_HONEST,             MUS_L_HONEST,             //  Honesty
  MUS_I_ATTACK,             MUS_L_ATTACK,             //  Under attack
  MUS_I_DEFEAT,             MUS_L_DEFEAT,             //  Defeated
  MUS_I_ESCAPE,             MUS_L_ESCAPE,             //  Escape
  MUS_I_GAMEOVER,           MUS_L_GAMEOVER,           //  The game is over
  MUS_I_GAMEOVER_EXTENDED,  MUS_L_GAMEOVER_EXTENDED,  //  The game is over?
};
enum sfx
{
  WAV_WUPARTY = 0,    //  PA-TEE!
  //  Frame SFX
  WAV_MENU_NAV,       //  Moving in a menu
  WAV_MENU_CONFIRM,   //  Confirm option
  WAV_MENU_CANCEL,    //  Cancel/break option
  WAV_MENU_SCRIBE,    //  Default "speech" (info)
  //  Action SFX
  WAV_DAMAGE,         //  Taking damage
  WAV_MUFFLE,         //  Taking muffled damage
  WAV_DEAD,           //  You died
  WAV_POOF,           //  Something "poof"ed
  WAV_DING,           //  Something "ding"ed
  WAV_BOOM,           //  Something "boom"ed
  WAV_SUPER_BOOM,     //  Something seriously "boom"ed
  WAV_SWITCH,         //  Switch active item/weapon
  WAV_HEAL,           //  Health get
  WAV_GAIN_HP,        //  Max HP increased
  //  Combat (weapon/defend) SFX
  WAV_PELLET,         //  Shoot the pellet
  WAV_SHIELD,         //  Put up the wall
  WAV_BLOCK,          //  Get the block
  WAV_BROKEN,         //  oops
  WAV_CLICK,          //  Shoot the nothing
  //  Item SFX
  WAV_BOOMSTICK,      //  This is my stick of boom
  WAV_GOOD_KEY,       //  That's a good key
  WAV_BAD_KEY,        //  That's a bad key
  WAV_CRAMPON,        //  Spiky sneakers for slippery stuff
  WAV_BOOST,          //  Catch-a-boooooooost
  //  Environment SFX
  WAV_DOOR_OPEN,      //  Not for closing doors
  WAV_DOOR_CLOSE,     //  Not for opening doors
  WAV_ELEC_OPEN,      //  Not for closing electronic doors
  WAV_ELEC_CLOSE,     //  Not for opening electronic doors
  WAV_TEMPLE_OPEN,    //  Not for closing stone passageways
  WAV_TEMPLE_CLOSE,   //  Not for opening stone passageways
  WAV_RUSTLE,         //  *rustling noises*
  WAV_RUMBLE,         //  *rumbling noises*
  WAV_RAIN,           //  *raining noises*
  WAV_DRIPDROP,       //  *dripping noises*
  WAV_GUST,           //  *gusting noises*
  WAV_POP,            //  *popping noises*
  WAV_BORK,           //  *bjorking noises*
  WAV_SECRET,         //  *secret noises*
  //  Character SFX
  WAV_BOY,
  WAV_MAN,
  WAV_GIRL,
  WAV_WOMAN,
  WAV_SENA,           //  Sena's speech
  WAV_LORA,           //  Lora's speech
  WAV_ADRIAN,         //  Adrian's speech
  WAV_MERIDITH,       //  Meridith's speech
  WAV_HARTMAN,        //  Hartman's speech
  WAV_LEPLACIA,       //  Leplacia's speech
  WAV_VIDE,           //  Vide's speech
  WAV_AWAN,           //  Awan's speech
  WAV_ZACH,           //  Zacharia's speech
  WAV_ERIN,           //  Erin's speech
};

class CSound
{
public:
  static CSound SoundSys;

private:
  int frequency;
  int s_chunk;
  bool stereo;
  unsigned int sfx_volume;
  unsigned int bgm_volume;

private:
  //  Global SFX (always loaded)
  Mix_Chunk*    wav_nav;
  Mix_Chunk*    wav_confirm;
  Mix_Chunk*    wav_cancel;
  Mix_Chunk*    wav_scribe;
  Mix_Chunk*    wav_dam;
  Mix_Chunk*    wav_mufdam;
  Mix_Chunk*    wav_dead;
  Mix_Chunk*    wav_poof;
  Mix_Chunk*    wav_ding;
  Mix_Chunk*    wav_boom;
  Mix_Chunk*    wav_superboom;
  Mix_Chunk*    wav_switch;
  Mix_Chunk*    wav_heal;
  Mix_Chunk*    wav_hpup;
  Mix_Chunk*    wav_pellet;
  Mix_Chunk*    wav_shield;
  Mix_Chunk*    wav_block;
  Mix_Chunk*    wav_break;
  Mix_Chunk*    wav_click;
  Mix_Chunk*    wav_boomstick;
  Mix_Chunk*    wav_goodkey;
  Mix_Chunk*    wav_badkey;
  Mix_Chunk*    wav_boost;
  Mix_Chunk*    wav_secret;

public:
  CSound();

public:
  bool OnInit();

  Mix_Music* LoadMUS(int tracknum);
  Mix_Chunk* LoadSFX(int sfxnum);

  bool PlayMusic(Mix_Music* music);
  bool PlaySound(Mix_Chunk* chunk);
  bool PlaySound(const int& sfxnum);

  bool ChangeOutput();
  bool IncreaseSFX();
  bool DecreaseSFX();
  bool IncreaseBGM();
  bool DecreaseBGM();

  bool OnCleanup();
};

#endif
