//Файл convert.h
#pragma once

#include <cstddef>

//Класс для конвертирования данных
class Convert{
public:
   int charToInt(const char *m) const;//из char в int
   size_t charToSizeT(const char *m) const;//из char в size_t
   unsigned charToUnsigned(const char *m) const;//из char в unsigned
   bool charToBool(const char *m) const;//из char в bool
};
