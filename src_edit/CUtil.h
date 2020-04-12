#ifndef _C_UTIL_H_
#define _C_UTIL_H_

#include <string>

class CUtil {
  private:
    CUtil();
  public:
    static bool isInt(const char& c);
    static int charToInt(const char& c);
    static int strToInt(const std::string& str);
    static double strToDouble(const std::string& str);
    static std::string msToHHMMSS(const unsigned long& t);  // convert milliseconds to hh:mm:ss timestamp
    static std::string intToStr(const int& val);
    static std::string doubleToStr(double val, const unsigned int& precision);
};
#endif
