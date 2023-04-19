//Файл main.cpp
#include <iostream>
#include "chat.h"
#include "terminal.h"

int clientCode(){
   try{
      Chat chat;
      Terminal terminal(chat.getIsColor());//объект для работы с терминалом
      char c = '0';
      while(1){
         if(c == '0'){
            //Отображаем первое меню
            c = chat.showHelloMenu();
         }
         else if(c == '1'){
            //Открываем окно для ввода логина и пароля
            chat.showLogIn();
            c = '0';
         }
         else if(c == '2'){
            //Отображаем меню для регистрации
            chat.showRegistrationMenu();
            c = '0';
         }
         else if(c == 'q'){
            terminal.clearScreen();
            terminal.setColor("GOOD");
            std::cout << "До встречи" << std::endl;
            terminal.setColor("DEFAULT");
            terminal.waitEnter();
            terminal.clearScreen();
            break;
         }
         terminal.clearScreen();
      }
   }
   catch(const std::string &e){
      std::cout << e << std::endl;
      return 1;
   }
   catch(const char *e){
      std::cout << e << std::endl;
      return 1;
   }
   catch(...){
      std::cout << "UNKNOWN EXCEPTION!" << std::endl;
      return 1;
   }

   return 0;
}

int main(){
   return clientCode(); 
}
