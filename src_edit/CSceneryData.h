#ifndef _C_SCENERYDATA_H_
#define _C_SCENERYDATA_H_

namespace Decorations {
  namespace groups {
    extern const short num;
    extern const char* const name[];
    enum {
      GLOBAL = 0,
    };
  };
};

class CSceneryData {

  CSceneryData();

public:
  static CSceneryData control;

public:


};

#endif
