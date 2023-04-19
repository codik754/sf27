//Файл idatabase.h
#pragma once

#include <vector>
#include <string>
#include "user.h"
#include "message.h"

//Интерфейс для базы данных. Нужен для реализации паттерна Strategy
class IDatabase{
public:
   virtual ~IDatabase() = default;//деструктор класса
   virtual void connect() = 0; //подключиться к серверу 
   virtual void disconnect() = 0; //отключиться от сервера
   virtual void readAllUsers(std::vector<User> &v) = 0;//прочитать список всех пользователей
   virtual void readMessages(const std::string &login, std::vector<Message> &v) = 0;//прочитать сообщения отправленных определенному пользователю
   virtual void addUser(const std::string &login, const std::string &pass) = 0;//добавить пользователя в БД
   virtual void addMessage(const std::string &from, const std::string &to, const std::string &text) = 0;//добавить сообщение в БД
};
