//Файл dbmysql.h
#pragma once

#include "idatabase.h"
#include <string>
#include <mysql.h>
#include <memory>

//Класс для работы с MySQL сервером
class DbMysql : public IDatabase{
   MYSQL mysql_;//дескриптор соединения
   std::string address_;//адрес сервера
   std::string user_; //логин
   std::string password_; //пароль
   std::string namedb_; //имя БД
   static std::shared_ptr<DbMysql> singleton_;//указатель. Нужен для реализации паттерна Singleton

   //Конструктор по умолчанию
   DbMysql(); 
   //Коструктор с параметрами
   DbMysql(const std::string &address, const std::string &user, const std::string &password, const std::string &namedb); 
public:
   //Конструктор копирования
   DbMysql(DbMysql &other) = delete;
   //Оператор присваивания
   void operator =(const DbMysql&) = delete;
   
   //Получить экземпляр класса
   static std::shared_ptr<DbMysql> getInstance(const std::string &address, const std::string &user, const std::string &password, const std::string &namedb);

   //Деструктор класса
   virtual ~DbMysql() override = default;
   //Подключиться к серверу
   void connect() override;
   //Отключиться от сервера
   void disconnect() override;
   //Прочитать список всех пользователей
   void readAllUsers(std::vector<User> &v) override;
   //Прочитать сообщения отправленных определенному пользователю
   void readMessages(const std::string &login, std::vector<Message> &v) override;
   //Добавить пользователя в БД
   void addUser(const std::string &login, const std::string &pass) override;
   //Добавить сообщение в БД
   void addMessage(const std::string &from, const std::string &to, const std::string &text) override;

};
