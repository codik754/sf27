//Файл chat.h
#pragma once

#include <vector>
#include "message.h"
#include "sha256.h"
#include "tcpclient.h"
#include "iclient.h"
#include "config.h"
#include "user.h"
#include <memory>


//Класс для чата
class Chat{
   std::string login_; //логин пользователя
   std::vector<Message> messages_;//вектор сообщений
   Config config_; //объект для чтения настроек из файла
   std::unique_ptr<IClient> client_; //объект для работы с сетью
   std::vector<User> users_;//вектор пользователей

public:
   //Конструктор по умолчанию
   Chat() : login_(), messages_(), config_("client.json"), client_(new TcpClient), users_() {
      //Читаем конфигурации
      config_.readConfig();
   }

   virtual ~Chat() = default;//деструктор класса

   char showHelloMenu();//показать первое меню
   void showLogIn();//показать меню для входа
   bool auth(std::string login, std::string password);//авторизация
   void configClient();//настройка клиента для соединения
   void connectToServer();//соедиение с сервером
   void disconnect();//окончания соединения с сервером
   void receiveMessages(const std::string &login);//получить сообщения от сервера
   void showAllChat();//показать общий чат
   void showSelfChat();//показать чат с личными сообщениями
   void showChatMenu();//показать меню чата
   int calculateAllMessages() const;//подсчитать количество общих сообщений
   int calculateSelfMessages() const;//подсчитать количество личных сообщений
   void logOutUser();//отправить запрос на выход
   void showRegistrationMenu();//показать меню регистрации
   void showWriteMessageMenu();//показать меню для написания сообщений
   void showConfigMenu();//меню настройки
   void receiveUsers();//получить список пользователей
   bool getIsColor() const; //получить бит цвета
};

