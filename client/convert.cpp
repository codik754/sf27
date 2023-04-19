//Файл convert.cpp
#include "convert.h"
#include <cstdlib>

//Из char в int
int Convert::charToInt(const char *m) const{
   return atoi(m);
}

//Из char в size_t
size_t Convert::charToSizeT(const char *m) const{
   return static_cast<size_t>(atoi(m));
}

//Из char в unsigned
unsigned Convert::charToUnsigned(const char *m) const{
   return static_cast<unsigned>(atoi(m));
}

//Из char в bool
bool Convert::charToBool(const char *m) const{
   return bool(atoi(m));
}
