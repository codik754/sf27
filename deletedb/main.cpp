#include <iostream>
#include <string>
#include <mysql.h>
#include "config.h"

int main(){
   //Создаем объект для чтения конфигурации
   Config config("server.json");

   try{
      //Считываем конфигурации
      config.readConfig();
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
   
   //Дескриптор соединения с MySQL
   MYSQL mysql;
 
   // Получаем дескриптор соединения
   if(!mysql_init(&mysql)){
      // Если дескриптор не получен — выводим сообщение об ошибке
      std::cout << "Error: can't create MySQL-descriptor" << std::endl; 
      return 1;
   }
 
   // Подключаемся к серверу
   if (!mysql_real_connect(&mysql, config.getAddressDb().c_str(), config.getLogin().c_str(), config.getPassword().c_str(), "", 0, NULL, 0)) {
      // Если нет возможности установить соединение с БД выводим сообщение об ошибке
      std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
      return 1;
   }
   
   //Формируем запрос
   std::string q = "DROP DATABASE " + config.getNameDb();

   //Создаем БД
   int r = mysql_query(&mysql, q.c_str()); 
   
   //Проверяем успешно ли прошел запрос
   if (r == 0) {
      std::cout << "База данных " << config.getNameDb() <<" удалена!" << std::endl;
   }
   else{
      std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
      return 1;
   }

   //Освобождаем дескриптор соединения
   mysql_close(&mysql);
 
   return 0;
}
