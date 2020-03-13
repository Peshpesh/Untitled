#ifndef _C_DIFFICULTY_H_
#define _C_DIFFICULTY_H_

enum Difficulty {
  EASY    = 0,
  NORMAL  = 1,
  HARD    = 2,
  BRUTAL  = 3,
};

class CDiff {
  CDiff();
  static Difficulty d;
public:
  static Difficulty getDiff();
  static void setDiff(const Difficulty& d);
};
#endif
