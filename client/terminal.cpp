//Файл terminal.cpp
#include "terminal.h"
#include <iostream>
#include <limits>
#include <stdio.h>
#include <cstdlib>

//Установить цвет текста в терминале
void Terminal::setColor(const std::string &color) const{
   //Если не нужно выводить цвета
   if(!isColor_){
      return;
   }

   if(color == "FIRST"){
      std::cout << "\033[01;38;05;178m";
   }
   else if(color == "INSERT"){
      std::cout << "\033[01;38;05;120m";
   }
   else if(color == "ERROR"){
      std::cout << "\033[01;38;05;196m";
   }
   else if(color == "GOOD"){
      std::cout << "\033[01;38;05;167m";
   }
   else if(color == "USER"){
      std::cout << "\033[01;38;05;76;48;05;22m"; 
   }
   else if(color == "TEXT"){
      std::cout << "\033[01;38;05;120m";
   }
   else if(color == "DATE"){
      std::cout << "\033[01;38;05;67m";
   }
   else if(color == "DEFAULT"){
      std::cout << "\033[0m";
   }
}

//Очистить экран
void Terminal::clearScreen() const{
   system("clear");
}

//Ожидание нажатия клавиши
void Terminal::waitEnter() const{
  std::cout << "Нажмите клавишу Enter" << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  char c = 'c';
  while(c != '\n'){
      c = getchar();
  }
}
