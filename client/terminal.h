//Файл terminal.h
#pragma once

#include <string>

//Класс для работы с терминалом
class Terminal{
   bool isColor_;//выводить цвета или нет
public:
   //Конструктор по умолчанию
   Terminal() : isColor_(true){}
   //Конструктор с параметрами
   explicit Terminal(bool b) : isColor_(b){}

   void setColor(const std::string &color) const;//установить цвет текста в терминале
   void clearScreen() const;//очистить экран
   void waitEnter() const;//ожидание нажатия клавиши
};
