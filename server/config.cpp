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
  
   port_ = data["port"];
   isColor_ = data["isColor"];
   addressdb_ = data["addressdb"];
   logindb_ = data["logindb"];
   passworddb_ = data["passworddb"];
   namedb_ = data["namedb"];
   
   //Закрываем файл
   f.close();
}

//Получит порт
uint16_t Config::getPort() const{
   return port_;
}

//Цветной или нет интерфейс
bool Config::getIsColor() const{
   return isColor_;
}

//Получить адрес MySQL-сервера
const std::string& Config::getAddressDb() const{
   return addressdb_;
}

//Получить логин для MySQL-сервера
const std::string& Config::getLoginDb() const{
   return logindb_;
}

//Пароль для MySQL
const std::string& Config::getPasswordDb() const{
   return passworddb_;
}

//Имя БД
const std::string& Config::getNameDb() const{
   return namedb_;
}
