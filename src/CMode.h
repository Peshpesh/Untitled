#ifndef _C_MODE_H_
#define _C_MODE_H_

enum app_module
{
  APP_MODE_FATAL , // application has suffered a fatal error
  APP_MODE_TITLE , // application is at the "title screen"
  APP_MODE_GAME  , // application is "in game"
};

class CMode {
private:
  static app_module handle;

public:
  CMode();

  // changes module handle
  static void changeFlag(app_module flag);

  // returns true if passed module is active
  static bool isFlagOn(app_module flag);
};

#endif
