//Файл main.cpp

#include <iostream>
#include <string>
#include "serverchat.h"
#include "convert.h"
#include "terminal.h"

int clientCode(){
   try{
      ServerChat server;//создаем объект для сервера
      
      server.connectToBd();//подключаемся к БД
      server.config();//настраиваем его

      server.readAllUsersToBd();//читаем информацию о всех пользователях из БД
      
      char m[lengthMessage];//делаем массив для получения сообщений
      bzero(m, lengthMessage);

      Convert convert;//объект для конвертирования
      Terminal terminal;//объект для работы с терминалом
      
      while(1){
         server.wait();//сервер ждет подключения
         while(strncmp("END", m, 3) != 0){
            server.receive(m, lengthMessage);//получаем данные
            //Если пришла команда для авторизации
            if(strncmp("CHK", m, 3) == 0){
               //Условие для авторизации
               server.printDateTime();
               std::cout << "Authorization request received" << std::endl;

               //Принимаем логин
               server.receive(m, lengthMessage);
               std::string login(m);

               //Принимаем пароль
               server.receive(m, lengthMessage);
               std::string password(m);
               
               server.authUser(login, password);

               bzero(m, lengthMessage);
            }
            else if(strncmp("MSG", m, 3) == 0){
               //Если пришла команда для получения сообщений
               //Условие для отправки сообщений
               server.printDateTime();
               std::cout << "Received a request to receive messages" << std::endl;

               //Принимаем логин
               server.receive(m, lengthMessage);
               std::string login(m);
               
               //Прием количества сообщений на клиенте
               server.receive(m, lengthMessage);
               size_t amount = convert.charToSizeT(m);

               server.sendMessages(login, amount);
               
               bzero(m, lengthMessage);
            }
            else if(strncmp("USR", m, 3) == 0){
               //Если пришла команда для авторизации
               //Условие для добавления пользователя
               server.printDateTime();
               std::cout << "Received a request to add a user" << std::endl;
               
               //Принимаем логин
               server.receive(m, lengthMessage);
               std::string login(m);

               //Принимаем пароль
               server.receive(m, lengthMessage);
               std::string password(m);

               int res = server.addUser(login, password);

               if(res == 1){
                  terminal.setColor("INSERT");
                  server.printDateTime();
                  std::cout << "User " << login << " added" << std::endl;
                  terminal.setColor("DEFAULT");
               }
               else if(res == 2){
                  terminal.setColor("ERROR");
                  server.printDateTime();
                  std::cout << "User " << login << " not added" << std::endl;
                  terminal.setColor("DEFAULT");
               }

               bzero(m, lengthMessage);
            }
            else if(strncmp("ADM", m, 3) == 0){
               //Если пришла команда для добавления сообщения
               //Условие для добавления сообщения
               server.printDateTime();
               std::cout << "Received a request to send a message" << std::endl;

               //Принимаем логин отправителя
               server.receive(m, lengthMessage);
               std::string from(m);

               //Принимаем логин получателя
               server.receive(m, lengthMessage);
               std::string to(m);

               //Принимаем текст сообщения
               server.receive(m, lengthMessage);
               std::string text(m);

               int res = server.addMessage(from, to, text);

               if(res == 1){
                  terminal.setColor("INSERT");
                  server.printDateTime();
                  std::cout << "User " << from << " sent a message" << std::endl;
                  terminal.setColor("DEFAULT");
               }
               else if(res == 2){
                  terminal.setColor("ERROR");
                  server.printDateTime();
                  std::cout << "User " << from << " did not send a message" << std::endl;
                  terminal.setColor("DEFAULT");
               }

               bzero(m, lengthMessage);
            }
            else if(strncmp("BCK", m, 3) == 0){
               //Если пришла команда для выхода пользователя
               server.receive(m, lengthMessage);
               std::string login(m);
               server.logOutUser(login);
               bzero(m, lengthMessage);
            }
         }
         bzero(m, lengthMessage);
      }
      server.disconnectToBd();//отключаемся от БД
      server.close();//закрывае соединение 
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
