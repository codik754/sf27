//Файл config.h
#pragma once

#include <string>

//Класс для чтения конфигураций из файла
class Config{
   std::string namefile_;//имя файла откуда будет считываться конфигурация
   uint16_t port_;//порт
   bool isColor_;//цветной интерфейс или нет
   std::string addressdb_; //адрес MySQL сервера
   std::string logindb_; //логин для MySQL-сервера
   std::string passworddb_; //пароль
   std::string namedb_; //имя БД
public:
   //Конструктор по умолчанию
   Config() : namefile_("config.json"), port_(51000), isColor_(false), addressdb_(), logindb_(), passworddb_(), namedb_() {}
   //Конструктор с параметрами
   explicit Config(const std::string &namefile) : namefile_(namefile), port_(51000), isColor_(false), addressdb_(), logindb_(), passworddb_(), namedb_() {}

   //Прочитать конфигурации
   void readConfig();
  
   //Получить адрес порта
   uint16_t getPort() const;

   //Цветной или нет интерфес
   bool getIsColor() const;

   //Получить адрес MySQL-сервера
   const std::string& getAddressDb() const;

   //Получить логин для MySQL-сервера
   const std::string& getLoginDb() const;

   //Пароль для MySQL
   const std::string& getPasswordDb() const;

   //Имя БД
   const std::string& getNameDb() const;
};
