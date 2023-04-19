//Файл config.h
#pragma once

#include <string>

#include <iostream>

//Класс для чтения конфигураций из файла
class Config{
   std::string namefile_;//имя файла откуда будет считываться конфигурация
   std::string login_;   //логин для входа в MySQL
   std::string password_;//пароль от MySQL
   std::string namedb_;  //имя базы данных
   std::string addressDb_;//адрес сервера БД
public:
   //Конструктор по умолчанию
   Config() : namefile_("config.json"), login_(), password_(), namedb_(), addressDb_() {}
   //Конструктор с параметрами
   explicit Config(const std::string &namefile) : namefile_(namefile), login_(), password_(), namedb_(), addressDb_() {}

   //Прочитать конфигурации
   void readConfig();
   
   //Получить логин
   const std::string& getLogin() const;

   //Получить пароль
   const std::string& getPassword() const;

   //Получить имя БД
   const std::string& getNameDb() const;

   //Получить адрес сервера БД
   const std::string& getAddressDb() const;
};
