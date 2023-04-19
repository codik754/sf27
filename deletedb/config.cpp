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
   
   login_ = data["logindb"];
   password_ = data["passworddb"];
   namedb_ = data["namedb"];
   addressDb_ = data["addressdb"];

   f.close();
}

//Получить логин
const std::string& Config::getLogin() const{
   return login_;
}

//Получить пароль
const std::string& Config::getPassword() const{
   return password_;
}

//Получить имя БД
const std::string& Config::getNameDb() const{
   return namedb_;
}

//Получить адрес сервера БД
const std::string& Config::getAddressDb() const{
   return addressDb_;
}
