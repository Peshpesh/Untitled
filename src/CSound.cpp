#include "CSound.h"

CSound CSound::SoundSys;

CSound::CSound()
{
  frequency     = 44100;            // frequency in samples per second (Hz)
  s_chunk       = 2048;             // sfx chunk size in bytes
  stereo        = true;             // flag for stereo sound system
  sfx_volume    = MIX_MAX_VOLUME;   // sound effect volume (0 - 128)
  bgm_volume    = MIX_MAX_VOLUME;   // music volume (0 - 128)

  // construct all global sfx pointers as null
  wav_nav       = NULL;
  wav_confirm   = NULL;
  wav_cancel    = NULL;
  wav_scribe    = NULL;
  wav_dam       = NULL;
  wav_mufdam    = NULL;
  wav_dead      = NULL;
  wav_poof      = NULL;
  wav_ding      = NULL;
  wav_boom      = NULL;
  wav_superboom = NULL;
  wav_switch    = NULL;
  wav_heal      = NULL;
  wav_hpup      = NULL;
  wav_pellet    = NULL;
  wav_shield    = NULL;
  wav_block     = NULL;
  wav_break     = NULL;
  wav_click     = NULL;
  wav_boomstick = NULL;
  wav_goodkey   = NULL;
  wav_badkey    = NULL;
  wav_boost     = NULL;
  wav_secret    = NULL;
}

bool CSound::OnInit()
{
  if (Mix_OpenAudio(frequency, AUDIO_S32SYS, 1 + (int)(stereo), s_chunk) == -1) return false;

  int format = MIX_INIT_MP3|MIX_INIT_OGG;
  if (Mix_Init(format) & format != format)
  {
    // failed to initialize support for .mp3 and .ogg
    return false;
  }

  // Load all global sfx chunks
  // if ((wav_nav = LoadSFX(WAV_MENU_NAV)) == NULL)          return false;
  // if ((wav_confirm = LoadSFX(WAV_MENU_CONFIRM)) == NULL)  return false;
  // if ((wav_cancel = LoadSFX(WAV_MENU_CANCEL)) == NULL)    return false;
  // if ((wav_scribe = LoadSFX(WAV_MENU_SCRIBE)) == NULL)    return false;
  // if ((wav_dam = LoadSFX(WAV_DAMAGE)) == NULL)            return false;
  // if ((wav_mufdam = LoadSFX(WAV_MUFFLE)) == NULL)         return false;
  // if ((wav_dead = LoadSFX(WAV_DEAD)) == NULL)             return false;
  // if ((wav_poof = LoadSFX(WAV_POOF)) == NULL)             return false;
  // if ((wav_ding = LoadSFX(WAV_DING)) == NULL)             return false;
  // if ((wav_boom = LoadSFX(WAV_BOOM)) == NULL)             return false;
  // if ((wav_superboom = LoadSFX(WAV_SUPER_BOOM)) == NULL)  return false;
  // if ((wav_switch = LoadSFX(WAV_SWITCH)) == NULL)         return false;
  // if ((wav_heal = LoadSFX(WAV_HEAL)) == NULL)             return false;
  // if ((wav_hpup = LoadSFX(WAV_GAIN_HP)) == NULL)          return false;
  // if ((wav_pellet = LoadSFX(WAV_PELLET)) == NULL)         return false;
  // if ((wav_shield = LoadSFX(WAV_SHIELD)) == NULL)         return false;
  // if ((wav_block = LoadSFX(WAV_BLOCK)) == NULL)           return false;
  // if ((wav_break = LoadSFX(WAV_BROKEN)) == NULL)          return false;
  // if ((wav_click = LoadSFX(WAV_CLICK)) == NULL)           return false;
  // if ((wav_boomstick = LoadSFX(WAV_BOOMSTICK)) == NULL)   return false;
  // if ((wav_goodkey = LoadSFX(WAV_GOOD_KEY)) == NULL)      return false;
  // if ((wav_badkey = LoadSFX(WAV_BAD_KEY)) == NULL)        return false;
  // if ((wav_boost = LoadSFX(WAV_BOOST)) == NULL)           return false;
  // if ((wav_secret = LoadSFX(WAV_SECRET)) == NULL)         return false;

  return true;
}

Mix_Music* CSound::LoadMUS(int tracknum)
{
  Mix_Music* music = NULL;
  switch (tracknum)
  {
    case MUS_HOLLOW: music = Mix_LoadMUS("home.ogg"); break;
    // External (non-game) Tracks
    case MUS_I_TITLE: music = Mix_LoadMUS("../res/ogg/title_intr.ogg"); break;
    case MUS_L_TITLE: music = Mix_LoadMUS("../res/ogg/title_loop.ogg"); break;
    case MUS_I_DIARY: music = Mix_LoadMUS("../res/ogg/diary_intr.ogg"); break;
    case MUS_L_DIARY: music = Mix_LoadMUS("../res/ogg/diary_loop.ogg"); break;
    case MUS_I_BADEND: music = Mix_LoadMUS("../res/ogg/bad_intr.ogg"); break;
    case MUS_L_BADEND: music = Mix_LoadMUS("../res/ogg/bad_loop.ogg"); break;
    case MUS_I_GOODEND: music = Mix_LoadMUS("../res/ogg/end_intr.ogg"); break;
    case MUS_L_GOODEND: music = Mix_LoadMUS("../res/ogg/end_loop.ogg"); break;
    case MUS_I_BESTEND: music = Mix_LoadMUS("../res/ogg/yea_intr.ogg"); break;
    case MUS_L_BESTEND: music = Mix_LoadMUS("../res/ogg/yea_loop.ogg"); break;
    // Regional Tracks
    case MUS_I_HOME: music = Mix_LoadMUS("../res/ogg/home_intr.ogg"); break;
    case MUS_L_HOME: music = Mix_LoadMUS("../res/ogg/home_loop.ogg"); break;
    case MUS_I_YRAI: music = Mix_LoadMUS("../res/ogg/yrai_intr.ogg"); break;
    case MUS_L_YRAI: music = Mix_LoadMUS("../res/ogg/yrai_loop.ogg"); break;
    case MUS_I_RHIGHID: music = Mix_LoadMUS("../res/ogg/rhighid_intr.ogg"); break;
    case MUS_L_RHIGHID: music = Mix_LoadMUS("../res/ogg/rhighid_loop.ogg"); break;
    case MUS_I_RUINS: music = Mix_LoadMUS("../res/ogg/ruins_intr.ogg"); break;
    case MUS_L_RUINS: music = Mix_LoadMUS("../res/ogg/ruins_loop.ogg"); break;
    case MUS_I_AVA: music = Mix_LoadMUS("../res/ogg/ava_intr.ogg"); break;
    case MUS_L_AVA: music = Mix_LoadMUS("../res/ogg/ava_loop.ogg"); break;
    case MUS_I_UNDERGROUND: music = Mix_LoadMUS("../res/ogg/undergr_intr.ogg"); break;
    case MUS_L_UNDERGROUND: music = Mix_LoadMUS("../res/ogg/undergr_loop.ogg"); break;
    case MUS_I_VIRIDIA: music = Mix_LoadMUS("../res/ogg/viridia_intr.ogg"); break;
    case MUS_L_VIRIDIA: music = Mix_LoadMUS("../res/ogg/viridia_loop.ogg"); break;
    case MUS_I_OCEAN: music = Mix_LoadMUS("../res/ogg/ocean_intr.ogg"); break;
    case MUS_L_OCEAN: music = Mix_LoadMUS("../res/ogg/ocean_loop.ogg"); break;
    case MUS_I_WASTES: music = Mix_LoadMUS("../res/ogg/wastes_intr.ogg"); break;
    case MUS_L_WASTES: music = Mix_LoadMUS("../res/ogg/wastes_loop.ogg"); break;
    case MUS_I_HILLS: music = Mix_LoadMUS("../res/ogg/hills_intr.ogg"); break;
    case MUS_L_HILLS: music = Mix_LoadMUS("../res/ogg/hills_loop.ogg"); break;
    case MUS_I_VOLCANO: music = Mix_LoadMUS("../res/ogg/volcano_intr.ogg"); break;
    case MUS_L_VOLCANO: music = Mix_LoadMUS("../res/ogg/volcano_loop.ogg"); break;
    case MUS_I_MORIV: music = Mix_LoadMUS("../res/ogg/moriv_intr.ogg"); break;
    case MUS_L_MORIV: music = Mix_LoadMUS("../res/ogg/moriv_loop.ogg"); break;
    case MUS_I_HIGHLAND: music = Mix_LoadMUS("../res/ogg/high_intr.ogg"); break;
    case MUS_L_HIGHLAND: music = Mix_LoadMUS("../res/ogg/high_loop.ogg"); break;
    case MUS_I_CAVERN: music = Mix_LoadMUS("../res/ogg/cave_intr.ogg"); break;
    case MUS_L_CAVERN: music = Mix_LoadMUS("../res/ogg/cave_loop.ogg"); break;
    case MUS_I_LEXI: music = Mix_LoadMUS("../res/ogg/lexi_intr.ogg"); break;
    case MUS_L_LEXI: music = Mix_LoadMUS("../res/ogg/lexi_loop.ogg"); break;
    case MUS_I_KNOWLEDGE: music = Mix_LoadMUS("../res/ogg/hok_intr.ogg"); break;
    case MUS_L_KNOWLEDGE: music = Mix_LoadMUS("../res/ogg/hok_loop.ogg"); break;
    case MUS_I_VOID: music = Mix_LoadMUS("../res/ogg/void_intr.ogg"); break;
    case MUS_L_VOID: music = Mix_LoadMUS("../res/ogg/void_loop.ogg"); break;
    case MUS_I_PEAK: music = Mix_LoadMUS("../res/ogg/peak_intr.ogg"); break;
    case MUS_L_PEAK: music = Mix_LoadMUS("../res/ogg/peak_loop.ogg"); break;
    // Character/Boss Tracks
    case MUS_I_GEN_ACT_I: music = Mix_LoadMUS("../res/ogg/boss1_intr.ogg"); break;
    case MUS_L_GEN_ACT_I: music = Mix_LoadMUS("../res/ogg/boss1_loop.ogg"); break;
    case MUS_I_GEN_ACT_II: music = Mix_LoadMUS("../res/ogg/boss2_intr.ogg"); break;
    case MUS_L_GEN_ACT_II: music = Mix_LoadMUS("../res/ogg/boss2_loop.ogg"); break;
    case MUS_I_GEN_ACT_III: music = Mix_LoadMUS("../res/ogg/boss3_intr.ogg"); break;
    case MUS_L_GEN_ACT_III: music = Mix_LoadMUS("../res/ogg/boss3_loop.ogg"); break;
    case MUS_I_GEN_ACT_IV: music = Mix_LoadMUS("../res/ogg/boss4_intr.ogg"); break;
    case MUS_L_GEN_ACT_IV: music = Mix_LoadMUS("../res/ogg/boss4_loop.ogg"); break;
    case MUS_I_GEN_ACT_V: music = Mix_LoadMUS("../res/ogg/boss5_intr.ogg"); break;
    case MUS_L_GEN_ACT_V: music = Mix_LoadMUS("../res/ogg/boss5_loop.ogg"); break;
    case MUS_I_EARTH: music = Mix_LoadMUS("../res/ogg/earth_intr.ogg"); break;
    case MUS_L_EARTH: music = Mix_LoadMUS("../res/ogg/earth_loop.ogg"); break;
    case MUS_I_WATER: music = Mix_LoadMUS("../res/ogg/water_intr.ogg"); break;
    case MUS_L_WATER: music = Mix_LoadMUS("../res/ogg/water_loop.ogg"); break;
    case MUS_I_FIRE: music = Mix_LoadMUS("../res/ogg/fire_intr.ogg"); break;
    case MUS_L_FIRE: music = Mix_LoadMUS("../res/ogg/fire_loop.ogg"); break;
    case MUS_I_WIND: music = Mix_LoadMUS("../res/ogg/wind_intr.ogg"); break;
    case MUS_L_WIND: music = Mix_LoadMUS("../res/ogg/wind_loop.ogg"); break;
    case MUS_I_LORA: music = Mix_LoadMUS("../res/ogg/lora_intr.ogg"); break;
    case MUS_L_LORA: music = Mix_LoadMUS("../res/ogg/lora_loop.ogg"); break;
    case MUS_I_VIDE: music = Mix_LoadMUS("../res/ogg/vide_intr.ogg"); break;
    case MUS_L_VIDE: music = Mix_LoadMUS("../res/ogg/vide_loop.ogg"); break;
    case MUS_I_AWAN: music = Mix_LoadMUS("../res/ogg/awan_intr.ogg"); break;
    case MUS_L_AWAN: music = Mix_LoadMUS("../res/ogg/awan_loop.ogg"); break;
    case MUS_I_ICARID: music = Mix_LoadMUS("../res/ogg/icarid_intr.ogg"); break;
    case MUS_L_ICARID: music = Mix_LoadMUS("../res/ogg/icarid_loop.ogg"); break;
    case MUS_I_ZACH: music = Mix_LoadMUS("../res/ogg/zach_intr.ogg"); break;
    case MUS_L_ZACH: music = Mix_LoadMUS("../res/ogg/zach_loop.ogg"); break;
    case MUS_I_FINAL: music = Mix_LoadMUS("../res/ogg/final_intr.ogg"); break;
    case MUS_L_FINAL: music = Mix_LoadMUS("../res/ogg/final_loop.ogg"); break;
    case MUS_I_VERY: music = Mix_LoadMUS("../res/ogg/very_intr.ogg"); break;
    case MUS_L_VERY: music = Mix_LoadMUS("../res/ogg/very_loop.ogg"); break;
    case MUS_I_LEPPY: music = Mix_LoadMUS("../res/ogg/lep_intr.ogg"); break;
    case MUS_L_LEPPY: music = Mix_LoadMUS("../res/ogg/lep_loop.ogg"); break;
    // Situational Tracks
    case MUS_I_SHOP: music = Mix_LoadMUS("../res/ogg/shop_intr.ogg"); break;
    case MUS_L_SHOP: music = Mix_LoadMUS("../res/ogg/shop_loop.ogg"); break;
    case MUS_I_STRANGER: music = Mix_LoadMUS("../res/ogg/stranger_intr.ogg"); break;
    case MUS_L_STRANGER: music = Mix_LoadMUS("../res/ogg/stranger_loop.ogg"); break;
    case MUS_I_GIFT: music = Mix_LoadMUS("../res/ogg/gift_intr.ogg"); break;
    case MUS_L_GIFT: music = Mix_LoadMUS("../res/ogg/gift_loop.ogg"); break;
    case MUS_I_CALAMITY: music = Mix_LoadMUS("../res/ogg/calamity_intr.ogg"); break;
    case MUS_L_CALAMITY: music = Mix_LoadMUS("../res/ogg/calamity_loop.ogg"); break;
    case MUS_I_HONEST: music = Mix_LoadMUS("../res/ogg/honest_intr.ogg"); break;
    case MUS_L_HONEST: music = Mix_LoadMUS("../res/ogg/honest_loop.ogg"); break;
    case MUS_I_ATTACK: music = Mix_LoadMUS("../res/ogg/attack_intr.ogg"); break;
    case MUS_L_ATTACK: music = Mix_LoadMUS("../res/ogg/attack_loop.ogg"); break;
    case MUS_I_DEFEAT: music = Mix_LoadMUS("../res/ogg/defeat_intr.ogg"); break;
    case MUS_L_DEFEAT: music = Mix_LoadMUS("../res/ogg/defeat_loop.ogg"); break;
    case MUS_I_ESCAPE: music = Mix_LoadMUS("../res/ogg/escape_intr.ogg"); break;
    case MUS_L_ESCAPE: music = Mix_LoadMUS("../res/ogg/escape_loop.ogg"); break;
    case MUS_I_GAMEOVER: music = Mix_LoadMUS("../res/ogg/gameover_intr.ogg"); break;
    case MUS_L_GAMEOVER: music = Mix_LoadMUS("../res/ogg/gameover_loop.ogg"); break;
    case MUS_I_GAMEOVER_EXTENDED: music = Mix_LoadMUS("../res/ogg/extend_intr.ogg"); break;
    case MUS_L_GAMEOVER_EXTENDED: music = Mix_LoadMUS("../res/ogg/extend_loop.ogg"); break;
    default: break;
  }
  return music;
}

Mix_Chunk* CSound::LoadSFX(int sfxnum)
{
  Mix_Chunk* chunk = NULL;
  switch (sfxnum)
  {
    case WAV_WUPARTY: break; //chunk = Mix_LoadWAV("../res/wav/"); break;
    case WAV_MENU_NAV:      chunk = Mix_LoadWAV("../res/wav/nav.wav"); break;
    case WAV_MENU_CONFIRM:  chunk = Mix_LoadWAV("../res/wav/conf.wav"); break;
    case WAV_MENU_CANCEL:   chunk = Mix_LoadWAV("../res/wav/cancel.wav"); break;
    case WAV_MENU_SCRIBE:   chunk = Mix_LoadWAV("../res/wav/scribe.wav"); break;
    //  Action SFX
    case WAV_DAMAGE:        chunk = Mix_LoadWAV("../res/wav/damage.wav"); break;
    case WAV_MUFFLE:        chunk = Mix_LoadWAV("../res/wav/mufdam.wav"); break;
    case WAV_DEAD:          chunk = Mix_LoadWAV("../res/wav/dead.wav"); break;
    case WAV_POOF:          chunk = Mix_LoadWAV("../res/wav/poof.wav"); break;
    case WAV_DING:          chunk = Mix_LoadWAV("../res/wav/ding.wav"); break;
    case WAV_BOOM:          chunk = Mix_LoadWAV("../res/wav/boom.wav"); break;
    case WAV_SUPER_BOOM:    chunk = Mix_LoadWAV("../res/wav/superboom.wav"); break;
    case WAV_SWITCH:        chunk = Mix_LoadWAV("../res/wav/switch.wav"); break;
    case WAV_HEAL:          chunk = Mix_LoadWAV("../res/wav/heal.wav"); break;
    case WAV_GAIN_HP:       chunk = Mix_LoadWAV("../res/wav/hpup.wav"); break;
    //  Combat SFX
    case WAV_PELLET:        chunk = Mix_LoadWAV("../res/wav/pellet.wav"); break;
    case WAV_SHIELD:        chunk = Mix_LoadWAV("../res/wav/shield.wav"); break;
    case WAV_BLOCK:         chunk = Mix_LoadWAV("../res/wav/block.wav"); break;
    case WAV_BROKEN:        chunk = Mix_LoadWAV("../res/wav/broken.wav"); break;
    case WAV_CLICK:         chunk = Mix_LoadWAV("../res/wav/click.wav"); break;
    //  Item SFX
    case WAV_BOOMSTICK:     chunk = Mix_LoadWAV("../res/wav/dynamite.wav"); break;
    case WAV_GOOD_KEY:      chunk = Mix_LoadWAV("../res/wav/goodkey.wav"); break;
    case WAV_BAD_KEY:       chunk = Mix_LoadWAV("../res/wav/badkey.wav"); break;
    case WAV_CRAMPON:       chunk = Mix_LoadWAV("../res/wav/crampon.wav"); break;
    case WAV_BOOST:         chunk = Mix_LoadWAV("../res/wav/boost.wav"); break;
    //  Environment SFX
    case WAV_DOOR_OPEN:     chunk = Mix_LoadWAV("../res/wav/dooropen.wav"); break;
    case WAV_DOOR_CLOSE:    chunk = Mix_LoadWAV("../res/wav/doorclose.wav"); break;
    case WAV_ELEC_OPEN:     chunk = Mix_LoadWAV("../res/wav/elecopen.wav"); break;
    case WAV_ELEC_CLOSE:    chunk = Mix_LoadWAV("../res/wav/elecclose.wav"); break;
    case WAV_TEMPLE_OPEN:   chunk = Mix_LoadWAV("../res/wav/templeopen.wav"); break;
    case WAV_TEMPLE_CLOSE:  chunk = Mix_LoadWAV("../res/wav/templeclose.wav"); break;
    case WAV_RUSTLE:        chunk = Mix_LoadWAV("../res/wav/rustle.wav"); break;
    case WAV_RUMBLE:        chunk = Mix_LoadWAV("../res/wav/rumble.wav"); break;
    case WAV_RAIN:          chunk = Mix_LoadWAV("../res/wav/rain.wav"); break;
    case WAV_DRIPDROP:      chunk = Mix_LoadWAV("../res/wav/dripdrop.wav"); break;
    case WAV_GUST:          chunk = Mix_LoadWAV("../res/wav/gust.wav"); break;
    case WAV_POP:           chunk = Mix_LoadWAV("../res/wav/pop.wav"); break;
    case WAV_BORK:          chunk = Mix_LoadWAV("../res/wav/bork.wav"); break;
    case WAV_SECRET:        chunk = Mix_LoadWAV("../res/wav/tada.wav"); break;
    //  Character SFX
    case WAV_BOY:           chunk = Mix_LoadWAV("../res/wav/boy.wav"); break;
    case WAV_MAN:           chunk = Mix_LoadWAV("../res/wav/man.wav"); break;
    case WAV_GIRL:          chunk = Mix_LoadWAV("../res/wav/girl.wav"); break;
    case WAV_WOMAN:         chunk = Mix_LoadWAV("../res/wav/woman.wav"); break;
    case WAV_SENA:          chunk = Mix_LoadWAV("../res/wav/sena.wav"); break;
    case WAV_LORA:          chunk = Mix_LoadWAV("../res/wav/lora.wav"); break;
    case WAV_ADRIAN:        chunk = Mix_LoadWAV("../res/wav/adrian.wav"); break;
    case WAV_MERIDITH:      chunk = Mix_LoadWAV("../res/wav/meridith.wav"); break;
    case WAV_HARTMAN:       chunk = Mix_LoadWAV("../res/wav/hartman.wav"); break;
    case WAV_LEPLACIA:      chunk = Mix_LoadWAV("../res/wav/leplacia.wav"); break;
    case WAV_VIDE:          chunk = Mix_LoadWAV("../res/wav/vide.wav"); break;
    case WAV_AWAN:          chunk = Mix_LoadWAV("../res/wav/awan.wav"); break;
    case WAV_ZACH:          chunk = Mix_LoadWAV("../res/wav/zach.wav"); break;
    case WAV_ERIN:          chunk = Mix_LoadWAV("../res/wav/erin.wav"); break;
    default: break;
  }
  return chunk;
}

bool CSound::PlayMusic(Mix_Music* music)
{
  if (Mix_PlayMusic(music, -1) == -1) return false;

  return true;
}

bool CSound::PlaySound(Mix_Chunk* chunk)
{
  if (chunk == NULL) return false;
  if (Mix_PlayChannel(-1, chunk, 0) == -1) return false;

  return true;
}

//  Note that this function only works for globally-loaded sfx
//  Passed enumerations that are not linked to global sfx
//  will play no sound and return false
bool CSound::PlaySound(const int& sfxnum)
{
  Mix_Chunk* chunk = NULL;
  switch (sfxnum)
  {
    case WAV_MENU_NAV:      chunk = wav_nav; break;
    case WAV_MENU_CONFIRM:  chunk = wav_confirm; break;
    case WAV_MENU_CANCEL:   chunk = wav_cancel; break;
    case WAV_MENU_SCRIBE:   chunk = wav_scribe; break;
    case WAV_DAMAGE:        chunk = wav_dam; break;
    case WAV_MUFFLE:        chunk = wav_mufdam; break;
    case WAV_DEAD:          chunk = wav_dead; break;
    case WAV_POOF:          chunk = wav_poof; break;
    case WAV_DING:          chunk = wav_ding; break;
    case WAV_BOOM:          chunk = wav_boom; break;
    case WAV_SUPER_BOOM:    chunk = wav_superboom; break;
    case WAV_SWITCH:        chunk = wav_switch; break;
    case WAV_HEAL:          chunk = wav_heal; break;
    case WAV_GAIN_HP:       chunk = wav_hpup; break;
    case WAV_PELLET:        chunk = wav_pellet; break;
    case WAV_SHIELD:        chunk = wav_shield; break;
    case WAV_BLOCK:         chunk = wav_block; break;
    case WAV_BROKEN:        chunk = wav_break; break;
    case WAV_CLICK:         chunk = wav_click; break;
    case WAV_BOOMSTICK:     chunk = wav_boomstick; break;
    case WAV_GOOD_KEY:      chunk = wav_goodkey; break;
    case WAV_BAD_KEY:       chunk = wav_badkey; break;
    case WAV_BOOST:         chunk = wav_boost; break;
    case WAV_SECRET:        chunk = wav_secret; break;
    default:  break;
  }
  return PlaySound(chunk);
}

//  Changing the audio output requires a reinitialization
//  of the mixing library. Thus, this change should only be
//  permitted in low-dynamic situations, such as via the main
//  menu or in pre-execution.
bool CSound::ChangeOutput()
{
  if (stereo) stereo = false;
  else stereo = true;

  return stereo;
}

bool CSound::IncreaseSFX()
{
  if (sfx_volume >= MIX_MAX_VOLUME) return false;

  Mix_Volume(-1, ++sfx_volume);
  return true;
}

bool CSound::DecreaseSFX()
{
  if (sfx_volume == 0) return false;

  Mix_Volume(-1, --sfx_volume);
  return true;
}

bool CSound::IncreaseBGM()
{
  if (bgm_volume >= MIX_MAX_VOLUME) return false;

  Mix_VolumeMusic(++bgm_volume);
  return true;
}

bool CSound::DecreaseBGM()
{
  if (bgm_volume == 0) return false;

  Mix_VolumeMusic(--bgm_volume);
  return true;
}

bool CSound::OnCleanup()
{
  // Free all global sfx chunks
  Mix_FreeChunk(wav_nav);
  Mix_FreeChunk(wav_confirm);
  Mix_FreeChunk(wav_cancel);
  Mix_FreeChunk(wav_scribe);
  Mix_FreeChunk(wav_dam);
  Mix_FreeChunk(wav_mufdam);
  Mix_FreeChunk(wav_dead);
  Mix_FreeChunk(wav_poof);
  Mix_FreeChunk(wav_ding);
  Mix_FreeChunk(wav_boom);
  Mix_FreeChunk(wav_superboom);
  Mix_FreeChunk(wav_switch);
  Mix_FreeChunk(wav_heal);
  Mix_FreeChunk(wav_hpup);
  Mix_FreeChunk(wav_pellet);
  Mix_FreeChunk(wav_shield);
  Mix_FreeChunk(wav_block);
  Mix_FreeChunk(wav_break);
  Mix_FreeChunk(wav_click);
  Mix_FreeChunk(wav_boomstick);
  Mix_FreeChunk(wav_goodkey);
  Mix_FreeChunk(wav_badkey);
  Mix_FreeChunk(wav_boost);
  Mix_FreeChunk(wav_secret);

  Mix_Quit();
  return true;
}
