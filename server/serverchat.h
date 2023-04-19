//Файл serverchat.h
#pragma once

#include "iserver.h"
#include "tcpserver.h"
#include "user.h"
#include "message.h"
#include "sha256.h"
#include "datetime.h"
#include "config.h"
#include "idatabase.h"
#include "dbmysql.h"
#include "logger.h"
#include <memory>
#include <vector>

class ServerChat{
   std::unique_ptr<IServer> server_;//указатель для работы с сервером
   std::vector<User> users_;//вектор пользователей
   unsigned short amountErrors_; //количество подряд идущих ошибок
   Datetime timing_; //время последней ошибки. Нужно для сравнения
   Config config_; //конфигурации. Объект нужен для чтения конфигураций
   std::shared_ptr<IDatabase> database_;//указатель для работы с базой данных
   Logger logger_; //объект для работы с логером
   
public:
   //Конструктор по умолчанию
   ServerChat() :users_(), amountErrors_(0), timing_(), config_("server.json"), logger_() {
      //Читаем конфигурации
      config_.readConfig();
      
      //Создаем указатель для работы с сервером
      server_ = std::make_unique<TcpServer>(config_.getPort());
      //Создаем указатель для работы с базой данных
      database_ = DbMysql::getInstance(config_.getAddressDb(), config_.getLoginDb(), config_.getPasswordDb(), config_.getNameDb());
   }

   //Деструктор класса
   ~ServerChat() = default;

   //Напечатать текущую дату и время
   void printDateTime();

   //Настройка сервера
   void config();

   //Ожидать соединения
   void wait();

   //Закрыть соединение
   void close();

   //Принять сообщение
   void receive(char *m, int length);

   //Авторизация пользователя
   bool authUser(const std::string &login, const std::string &password);

   //Отправить сообщения на клиент
   void sendMessages(const std::string &login, const size_t amount);

   //Установить статус пользователя не авторизирвован
   void logOutUser(const std::string &login);

   //Добавить пользователя
   int addUser(const std::string &login, const std::string &password);

   //Добавить сообщение
   int addMessage(const std::string &from, const std::string &to, const std::string &text);
   
   //Это ошибка
   void thisIsError();

   //Подключиться к БД
   void connectToBd();

   //Отключиться от БД
   void disconnectToBd();

   //Прочитать информацию о всех пользователях из БД
   void readAllUsersToBd();

   //Отправить список пользователей. Пригодится в дальнейшем для определения клиентом списка пользователей онлайн
   void sendUsers();
};
