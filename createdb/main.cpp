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
   std::string q = "CREATE DATABASE " + config.getNameDb();

   //Создаем БД
   int r = mysql_query(&mysql, q.c_str()); 
   
   //Проверяем успешно ли прошел запрос
   if (r == 0) {
      std::cout << "База данных " << config.getNameDb() <<" добавлена!" << std::endl;
   }
   else{
      std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
      return 1;
   }
   
   //Выбираем БД
   q = "USE " + config.getNameDb();
   mysql_query(&mysql, q.c_str()); 

   //Создаем таблицу
   r = mysql_query(&mysql, "CREATE TABLE users(id INT AUTO_INCREMENT PRIMARY KEY, login VARCHAR(8) UNIQUE, password VARCHAR(100))");
   
   //Проверяем успешно ли прошел запрос
   if (r == 0) {
      std::cout << "Таблица users создана!" << std::endl;
   }
   else{
      std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
      return 1;
   } 

   //Добавляем данные в users
   r = mysql_query(&mysql, "INSERT INTO users(login, password) values('all', 'UNKNOWN')");
   int r1 = mysql_query(&mysql, "INSERT INTO users(login, password) values('admin', '7c04837eb356565e28bb14e5a1dedb240a5ac2561f8ed318c54a279fb6a9665e')");
   
   if(r == 0 && r1 == 0){
      std::cout << "В таблицу users добавлены изначальные значения" << std::endl;
   }
   else{
      std::cout << "Ошибка MySql при добавлении данных в таблицу users: " << mysql_error(&mysql) << std::endl;
      return 1;
   } 

   //Создаем таблицу messages
   r = mysql_query(&mysql, "CREATE TABLE messages(id INT AUTO_INCREMENT PRIMARY KEY, `from` INT NOT NULL, `to` INT NOT NULL, `text` VARCHAR(500) , `datetime` DATETIME)");

   //Проверяем правильность прохождения запроса
   if(r == 0) {
      std::cout << "Таблица messages создана!" << std::endl;
   }
   else{
      std::cout << "Ошибка MySql: " << mysql_error(&mysql) << std::endl;
      return 1;
   } 
   
   //Освобождаем дескриптор соединения
   mysql_close(&mysql);
 
   return 0;
}
