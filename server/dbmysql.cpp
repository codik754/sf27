//Файл dbmysql.cpp
#include "dbmysql.h"

#include <iostream>

//Объявляем статическое поле класса
std::shared_ptr<DbMysql> DbMysql::singleton_ = nullptr;

//Конструктор по умолчанию
DbMysql::DbMysql() : mysql_(), address_(), user_(), password_(), namedb_() {}

//Коструктор с параметрами
DbMysql::DbMysql(const std::string &address, const std::string &user, const std::string &password, const std::string &namedb) : mysql_(), address_(address), user_(user), password_(password), namedb_(namedb) {}

//Получить экземпляр класса
std::shared_ptr<DbMysql> DbMysql::getInstance(const std::string &address, const std::string &user, const std::string &password, const std::string &namedb){
   if(singleton_ == nullptr){
      singleton_ =  std::shared_ptr<DbMysql>(new DbMysql(address, user, password, namedb));
   }
   return singleton_;
}

//Подключиться к серверу
void DbMysql::connect(){
   // Получаем дескриптор соединения
   mysql_init(&mysql_);
   if (&mysql_ == nullptr) {
      // Если дескриптор не получен — выводим сообщение об ошибке
      throw "Error: can't create MySQL-descriptor";
   }

   // Подключаемся к серверу
   if (!mysql_real_connect(&mysql_, address_.c_str(), user_.c_str(), password_.c_str(), namedb_.c_str(), 0, NULL, 0)) {
      // Если нет возможности установить соединение с БД выводим сообщение об ошибке
      std::string str = "Error: can't connect to database. " + std::string(mysql_error(&mysql_));
      throw str;
   } 

   //Настрпиваем кодировку
   mysql_set_character_set(&mysql_, "utf8");
}

//Отключиться от серверу
void DbMysql::disconnect(){
   // Закрываем соединение с сервером базы данных
   mysql_close(&mysql_);   
}

//Прочитать список всех пользователей
void DbMysql::readAllUsers(std::vector<User> &v){
   MYSQL_RES* res;
   MYSQL_ROW row;
   //Отправляем запрос на сервер
   mysql_query(&mysql_, "SELECT login, password FROM users"); //Делаем запрос к таблице

   //Выводим все что есть в таблице через цикл
   if ((res = mysql_store_result(&mysql_))) {
      while ((row = mysql_fetch_row(res))) {
         for (unsigned i = 0; i < mysql_num_fields(res) - 1; ++i) {
            //std::cout << row[i] << "  ";
            v.emplace_back(row[i], row[i + 1]);
         }
         //std::cout << std::endl;
      }
   }
   else{
      std::string str = "Ошибка MySql номер " + std::string(mysql_error(&mysql_));
      throw str;
   }
}

//Прочитать сообщения отправленных определенному пользователю
void DbMysql::readMessages(const std::string &login, std::vector<Message> &v){
   MYSQL_RES* res;
   MYSQL_ROW row;

   //Формируем запрос
   std::string q = "SELECT u1.login as 'from' , u2.login as 'to', `text`, DATE_FORMAT(messages.datetime, '%d.%m.%Y %T')  FROM messages \
                     INNER JOIN users AS u1 ON u1.id = messages.from \
                     INNER JOIN users AS u2 ON u2.id = messages.to \
                     WHERE u2.login = '" + login + "' OR u2.login = 'all'";
   //Отправляем запрос на сервер
   mysql_query(&mysql_, q.c_str()); //Делаем запрос к таблице

   //Выводим все что есть в таблице через цикл
   if ((res = mysql_store_result(&mysql_))) {
      while ((row = mysql_fetch_row(res))) {
         for (unsigned i = 0; i < mysql_num_fields(res) - 3; ++i) {
            v.emplace_back(row[i], row[i + 1], row[i + 2], row[i + 3]);
         }
      }
   }
   else{
      std::string str = "Ошибка MySql номер " + std::string(mysql_error(&mysql_));
      throw str;
   }

}

//Добавить пользователя в БД
void DbMysql::addUser(const std::string &login, const std::string &pass){
   //Формируем запрос
   std::string q = "INSERT INTO users(login, password) values('" + login + "', '" + pass + "')";
   mysql_query(&mysql_, q.c_str());
}

//Добавить сообщение в БД
void DbMysql::addMessage(const std::string &from, const std::string &to, const std::string &text){
   //Формируем запрос
   std::string q = "INSERT INTO messages(`from`, `to`, `text`, `datetime`) values((SELECT id FROM users WHERE login = '" + from  + "'), (SELECT id FROM users WHERE login = '" + to + "'), '" + text + "', NOW())";
   mysql_query(&mysql_, q.c_str());
}
