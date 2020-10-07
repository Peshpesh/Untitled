#include "CUtil.h"

CUtil::CUtil() {
  //
}

bool CUtil::isInt(const char& c) {
  bool retval = false;
  switch (c) {
    case '0': retval = true; break;
    case '1': retval = true; break;
    case '2': retval = true; break;
    case '3': retval = true; break;
    case '4': retval = true; break;
    case '5': retval = true; break;
    case '6': retval = true; break;
    case '7': retval = true; break;
    case '8': retval = true; break;
    case '9': retval = true; break;
    default:  break;
  }
  return retval;
}

int CUtil::charToInt(const char& c) {
  int retval = -1;
  switch (c) {
    case '0': retval = 0; break;
    case '1': retval = 1; break;
    case '2': retval = 2; break;
    case '3': retval = 3; break;
    case '4': retval = 4; break;
    case '5': retval = 5; break;
    case '6': retval = 6; break;
    case '7': retval = 7; break;
    case '8': retval = 8; break;
    case '9': retval = 9; break;
    default:  break;
  }
  return retval;
}

int CUtil::strToInt(const std::string& str) {
  if (str.empty()) return 0;
  int val = 0;

  bool neg = (str[0] == '-');
  int i = str.size() - 1;
  int O = 1;
  while (i >= neg) {
    if (str[i] == '.') return neg ? -val : val; // assuming the period is a floating point
    if (!isInt(str[i])) return 0;  // invalid character
    val += O * charToInt(str[i]);
    O *= 10;
    i--;
  }
  return val;
}

double CUtil::strToDouble(const std::string& str) {
  if (str.empty()) return 0.0;

  double val = 0.0;

  bool neg = (str[0] == '-');
  bool isNum = false;
  bool frac = false;
  int int_digits = 0;
  int i = neg;    // start at index 1 (true) if there's a leading minus sign
  // how many integer digits are there in the string? (int_digits)
  // does the string represent a floating point value? (frac)
  while (i < str.size()) {
    if (str[i] == '.') {
      if (!frac) frac = true;
      else return val;    // invalid string (more than 1 decimal point)
    }
    else if (!isInt(str[i])) return 0.0;  // invalid string (non-numeric characters)
    else {
      if (!isNum) isNum = true;
      if (!frac) int_digits++;
    }
    i++;
  }
  if (!isNum) return 0.0;

  i = neg;
  while (int_digits) {
    int O = 1;
    for (int j = 1; j < int_digits; j++) O *= 10;
    val += (O * charToInt(str[i]));
    i++;
    int_digits--;
  }
  if (frac) {
    i++;
    int O = 1;
    while (i < str.size()) {
      O *= 10;
      val += (double)(charToInt(str[i])) / O;
      i++;
    }
  }
  return neg ? -val : val;
}

std::string CUtil::msToHHMMSS(const unsigned long& t) {
  unsigned short hh = t / (1000 * 60 * 60);
  unsigned short mm = (t % (1000 * 60 * 60)) / (1000 * 60);
  unsigned short ss = (t % (1000 * 60)) / (1000);
  std::string timestamp = intToStr(hh) + "-" + intToStr(mm) + "-" + intToStr(ss);
  return timestamp;
}

std::string CUtil::intToStr(const int& val) {
  std::string retstr;
  int magnitude = 1;

  if (val < 0) {
    retstr = "-";
    magnitude = -magnitude;
  }

  // How big is this number? (how many digits is key)
  while (val / (magnitude * 10) != 0) {
    // if the loop condition is nonzero, then that means the denominator
    // isn't large enough to reduce the fraction to zero...
    // The fraction reduces to zero IF the denominator exceeds
    // the numerator, which is what we're looking for.
    // EX: First loop does N / 10. If zero, then abs(N) is less than 10 (Magnitude of 10^0, or 1).
    //     Otherwise, next loop does N / 100. If zero, then abs(N) is less than 100. (Mag 10^1, or 10)
    //     Next loop would be N / 1000... And on until the loop ends.
    magnitude *= 10;
  }

  while (magnitude != 0) {
    // First, mod the number by current mag*10 to get rid of following digits.
    // Second, divide the resulting number by mag to get rid of leading digits.
    switch ((val % (magnitude * 10)) / magnitude) {
      case 0: retstr.push_back('0'); break;
      case 1: retstr.push_back('1'); break;
      case 2: retstr.push_back('2'); break;
      case 3: retstr.push_back('3'); break;
      case 4: retstr.push_back('4'); break;
      case 5: retstr.push_back('5'); break;
      case 6: retstr.push_back('6'); break;
      case 7: retstr.push_back('7'); break;
      case 8: retstr.push_back('8'); break;
      case 9: retstr.push_back('9'); break;
      default: break;
    }
    magnitude /= 10;
  }
  return retstr;
}

std::string CUtil::doubleToStr(double val, const unsigned int& precision) {
  std::string retstr;

  if (val < 0.0) {
    retstr = "-";
    val = -val;
  }

  if (precision != 0) {
    std::string intPart = intToStr((int)(val));

    int O = 1;    // big O
    for (int i = 1; i <= precision; i++) O *= 10;

    double truncVal = val - (int)(val);
    std::string truncPart = intToStr((int)(truncVal * O));
    while (truncPart.size() < precision) truncPart = "0" + truncPart;

    retstr = intPart + "." + truncPart;
  }
  else {
    retstr = intToStr((int)(val));
  }
  return retstr;
}
