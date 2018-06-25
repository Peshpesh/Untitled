#ifndef _C_STAGE_H_
#define _C_STAGE_H_

class CStage {
public:
  static CStage* stage;

  CStage();
  virtual void OnInit() = 0;
  virtual void OnLoad() = 0;
  virtual void OnLoop() = 0;
  virtual void OnRender() = 0;
  virtual void OnCleanup() = 0;
};

#endif
