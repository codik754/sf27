//Файл user.h
#pragma once

#include <string>

//Класс для пользователя
class User{
   const std::string login_;//поле для логина
public:
   //Конструктор по умолчанию
   User() : login_("UNKNOWN") {}
   //Параметризированный конструктор
   explicit User(const std::string& login) : login_(login){}

   ~User() = default;//деструктор класса
   
   //Проверка логина
   bool checkLogin(const std::string &login) const;
   //Получить логин
   const std::string& getLogin() const;
};
