//Файл config.cpp
#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

//Прочитать конфигурации
void Config::readConfig(){
   std::ifstream f(namefile_);

   //Проверяем открыт ли файл
   if(!f.is_open()){
      std::string str = "Error opening the configuration file. Configuration file: " + namefile_;
      throw str;
   }

   //Считываем данные
   nlohmann::json data;
   f >> data;
  
   address_ = data["address"];
   port_ = data["port"];
   isColor_ = data["isColor"];

   f.close();
}

//Получить адрес сервера
const std::string& Config::getAddress() const{
   return address_;
}

//Получит порт
uint16_t Config::getPort() const{
   return port_;
}

//Цветной или нет интерфейс
bool Config::getIsColor() const{
   return isColor_;
}
