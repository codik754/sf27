//Файл config.h
#pragma once

#include <string>

//Класс для чтения конфигураций из файла
class Config{
   std::string namefile_;//имя файла откуда будет считываться конфигурация
   std::string address_;//адрес сервера
   uint16_t port_;//порт
   bool isColor_;//цветной интерфейс или нет
public:
   //Конструктор по умолчанию
   Config() : namefile_("config.json"), port_(51000), isColor_(false) {}
   //Конструктор с параметрами
   explicit Config(const std::string &namefile) : namefile_(namefile), port_(51000), isColor_(false) {}

   //Прочитать конфигурации
   void readConfig();
  
   //Получить адрес сервера
   const std::string& getAddress() const;

   //Получить адрес порта
   uint16_t getPort() const;

   //Цветной или нет интерфес
   bool getIsColor() const;
};
