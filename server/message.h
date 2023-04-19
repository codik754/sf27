//Файл message.h
#pragma once

#include <string>

//Класс для сообщений
class Message {
   std::string sendedFrom_;//от кого отправлено сообщение
   std::string sendedTo_;  //кому отправлено сообщение
   std::string text_;   //текст сообщения
   std::string dateandtime_; //дата отправки сообщения
public:
   //Конструктор по умолчанию
   Message();
   //Конструктор с параметрами
   Message(const std::string& from, const std::string& to, const std::string& text);
   //Конструктор с параметрами
   Message(const std::string& from, const std::string& to, const std::string& text, const std::string &dateandtime);

   //Конструктор копирования
   Message(const Message& other);
   //Деструктор
   ~Message() = default;
   
   //Узнать от кого отправлено сообщение
   const std::string& getSendedFrom() const;
   //Узнать кому отправлено сообщение
   const std::string& getSendedTo() const;
   //Получить текст сообщения
   const std::string& getText() const;
   //Получить дату и время
   const std::string& getDatetime() const;
   //Соответсвует ли поле кому отправлено сообщение переданной строке
   bool checkToSendedTo(const std::string &login) const;
};
