//Файл chat.cpp
#include "chat.h"
#include "terminal.h"
#include "convert.h"
#include "datetime.h"
#include <iostream>
#include <cstdlib>
#include <algorithm> 

//Показать первое меню
char Chat::showHelloMenu() {
    Terminal terminal(config_.getIsColor());//объект для работы с терминалом
    char choice = '0';//переменная для выбора
    while (true) {
        terminal.clearScreen();
        terminal.setColor("FIRST");
        std::cout << "Добрый день! Добро пожаловать в чат. Что будем делать?" << std::endl;
        std::cout << "1. Подключиться" << std::endl;
        std::cout << "2. Регистрация" << std::endl;
        std::cout << "q - Выход" << std::endl;
        std::cout << std::endl << "Введите символ: ";
        terminal.setColor("INSERT");
        std::cin >> choice;
        //Если введены символы соответствующие требуемым
        if (choice == '1' || choice == '2' || choice == '3' || choice == 'q') {
            break;
        }
        else {
            //Если введены символы не соответствующие выбранным
            terminal.clearScreen();
            terminal.setColor("ERROR");
            std::cout << "Команды " << choice << " не знаю!!!" << std::endl;
            terminal.setColor("DEFAULT");
            terminal.waitEnter(); 
            terminal.clearScreen();
        }
    }
    terminal.setColor("DEFAULT");
    return choice;
}

//Показать меню для входа
void Chat::showLogIn() {
    Terminal terminal(config_.getIsColor());//объект для работы с терминалом
    terminal.clearScreen();
    std::string tlogin;
    std::string tpassword;
    terminal.setColor("FIRST");
    std::cout << "Введите данные для входа " << std::endl;
    std::cout << "Логин: ";
    terminal.setColor("INSERT");
    std::cin >> tlogin;
    terminal.setColor("FIRST");
    std::cout << "Пароль: ";
    terminal.setColor("INSERT");
    std::cin >> tpassword;
    
    //Подключаемся к серверу
    try{
      configClient();//настраиваем клиент
      connectToServer();//подлючаемся к серверу
    }
    catch(const char *e){
      terminal.clearScreen();
      terminal.setColor("ERROR");
      std::cout << e << std::endl;
      terminal.setColor("DEFAULT");
      terminal.waitEnter();
      terminal.clearScreen();
      return;
    }
    catch(...){
      terminal.clearScreen();
      terminal.setColor("ERROR");
      std::cout << "Unknown exception!" << std::endl;
      terminal.setColor("DEFAULT");
      terminal.waitEnter();
      terminal.clearScreen();
      return;
    }
    
 
    SHA256 sha256;//создаем объект для хеширования пароля
    bool res = auth(tlogin, sha256(tpassword));
    
    terminal.clearScreen();
    //Если пользователь не найден
    if (!res) {
        terminal.setColor("ERROR");
        std::cout << "Логин или пароль введены неверно!" << std::endl;
        terminal.setColor("DEFAULT");
        terminal.waitEnter();
        terminal.clearScreen();
        client_->send("END");
        disconnect();
        return;
    }
    terminal.setColor("DEFAULT");
    login_ = tlogin;
    messages_.clear();
    users_.clear();

    //Получаем список пользователей
    receiveUsers();
    
    showChatMenu();//показываем меню чата
    logOutUser();//отправляем запрос на выход из системы
    
    client_->send("END");
    disconnect();
}

//Авторизация
bool Chat::auth(std::string login, std::string password){
   Convert convert;//объект для конвертирования
   client_->send("CHK");
   client_->send(login.c_str());
   client_->send(password.c_str());

   char m[lengthMessage];
   client_->receive(m, lengthMessage);
   
   return convert.charToBool(m);
}

//Настройка клиента для соединения
void Chat::configClient(){
  client_->config(config_.getAddress().c_str(), config_.getPort());
}

//Соединение с сервером
void Chat::connectToServer(){
  client_->connectToServer(); 
}

//Отключиться от сервера
void Chat::disconnect(){
   client_->disconnect();
}

//Получить сообщения от сервера
void Chat::receiveMessages(const std::string &login){
   Convert convert;//объект для конвертирования
   client_->send("MSG");
   client_->send(login.c_str());
   client_->send(messages_.size());

   char m[lengthMessage];
   client_->receive(m, lengthMessage);
   
   size_t amount = convert.charToSizeT(m);
  
   //Получаем сообщения
   for(size_t i = 0; i < amount; ++i){
      //Получаем информацию об отправители
      client_->receive(m, lengthMessage);
      std::string from = m;
      
      //Получаем информацию о получателе
      client_->receive(m, lengthMessage);
      std::string to = m;

      //Получаем сообщения сообщения
      client_->receive(m, lengthMessage);
      std::string text = m;

      //Получаем секунды отправки сообщения
      client_->receive(m, lengthMessage);
      std::string datetime = m;
      
      //Добавляем сообщения в вектор
      messages_.emplace_back(from, to, text, datetime);
   }
}

//Показать общий чат
void Chat::showAllChat(){
   Terminal terminal(config_.getIsColor());//объект для работы с терминалом
   terminal.setColor("FIRST");
   std::cout << "Общий чат" << std::endl;
   Datetime date;//объект для определения даты и времени
   date.setNow();//устанавливаем текущую дату и время
   //Выводим на экран
   std::cout << date.getStrDate() << std::endl;
   std::cout << date.getStrTime() << std::endl;
  
   std::cout << "________________________________________________________________________________________________" << std::endl;
   //Определяем есть ли сообщения в общем чате
  if (calculateAllMessages() == 0) {
       terminal.setColor("TEXT");
       std::cout << std::endl << "Сообщений нет" << std::endl;
   }
   else {
       //Определяем количество новых сообщений в общем чате
       for (const auto& message : messages_) {
           //Если поле кому содержит all
           if (message.checkToSendedTo("all")) {
               terminal.setColor("USER");
               //Выводим того кто отправл сообщение
               std::cout << "[" << message.getSendedFrom() << "]" << std::endl;
               terminal.setColor("DEFAULT");
               terminal.setColor("TEXT");
               //Выводим текст
               std::cout << message.getText() << std::endl;
               terminal.setColor("DATE");
               //Выводим дату и время отправки сообщения
               std::cout << message.getDatetime() << std::endl;
               std::cout << std::endl;
               terminal.setColor("DEFAULT");
           }
       }
   }
   terminal.setColor("FIRST");
   std::cout << "________________________________________________________________________________________________" << std::endl;
   std::cout << "1 - Обновить чат   2 - Личные сообщения" << "  3 - Написать сообщение " << "q - Выход" << std::endl;
   terminal.setColor("DEFAULT");
}

//Показать чат с личными сообщениями
void Chat::showSelfChat(){
   Terminal terminal(config_.getIsColor());//объект для работы с терминалом
   terminal.setColor("FIRST");
   std::cout << "Личные сообщения" << std::endl;
   Datetime date;//объект для определения даты и времени
   date.setNow();//устанавливаем текущую дату и время
   //Выводим на экран
   std::cout << date.getStrDate() << std::endl;
   std::cout << date.getStrTime() << std::endl;
   std::cout << "________________________________________________________________________________________________" << std::endl;
   //Если количество личных сообщений равно 0
   if (calculateSelfMessages() == 0) {
       terminal.setColor("TEXT");
       std::cout << std::endl << "Сообщений нет" << std::endl;
   }
   else {
       for (const auto& message : messages_) {
           //Если поле в сообщение кому соответствует логину текущего пользователя
           if (message.checkToSendedTo(login_)) {
               terminal.setColor("USER");
               //Выводим логин отправителя
               std::cout << "[" << message.getSendedFrom() << "]" << std::endl;
               terminal.setColor("DEFAULT");
               terminal.setColor("TEXT");
               //Выводим сообщение
               std::cout << message.getText() << std::endl;
               terminal.setColor("DATE");
               //Выводим дату и время отправки сообщения
               std::cout << message.getDatetime() << std::endl;
               std::cout << std::endl;
               terminal.setColor("DEFAULT");
           }
       }
   }
   terminal.setColor("FIRST");
   std::cout << "________________________________________________________________________________________________" << std::endl;
   std::cout << "1 - Общий чат" << "  2 - Обновить чат" << "  3 - Написать сообщение  4 - " <<
       "q - Выход" << std::endl;
   terminal.setColor("DEFAULT");
}

//Показать меню чата
void Chat::showChatMenu() {
    Terminal terminal(config_.getIsColor());//объект для работы с терминалом
     
    short type = 1;//тип чата(общий или личнные сообщения)
    char choice = '0';//выбор в чате

    while (true) {
        //Если type = 1 выводим общий чат
        if (type == 1){
            receiveMessages(login_);
            showAllChat();
            terminal.setColor("FIRST");
            std::cout << "Введите символ: ";
            terminal.setColor("INSERT");
            std::cin >> choice;//считываем ввод от пользователя
            terminal.setColor("DEFAULT");
        }
        
        //Если type = 2 выводим чат с личными сообщениями
        if (type == 2) {
            receiveMessages(login_);
            showSelfChat();
            terminal.setColor("FIRST");
            std::cout << "Введите символ: ";
            terminal.setColor("INSERT");
            std::cin >> choice;//считываем ввод от пользователя
            terminal.setColor("DEFAULT");
        }

        if (choice == 'q') {
            break;
        }
        else if (choice == '1') {
            if (type == 2) {
                type = 1;
            }
            terminal.clearScreen();

            continue;
        }
        else if (choice == '2') {
            if (type == 1) {
                type = 2;
            }
            terminal.clearScreen();
            continue;
        }
        else if (choice == '3') {
            terminal.clearScreen();
            showWriteMessageMenu();//показать меню для написания сообщения
        }
        terminal.clearScreen(); 
    }
    terminal.clearScreen(); 
}

//Подсчитать количество общих сообщений
int Chat::calculateAllMessages() const{
    //Подсчитываем количество совпадений
    int amount = std::count_if(messages_.begin(), messages_.end(), [](const Message& m) {
        return m.checkToSendedTo("all");
     });

    return amount;
}

//Подсчитать количество общих сообщений
int Chat::calculateSelfMessages() const{
    std::string login = login_;
    //Подсчитываем количество совпадений
    int amount = std::count_if(messages_.begin(), messages_.end(), [login](const Message& m) {
        return m.checkToSendedTo(login);
     });
    return amount;
}

//Отправить запрос на выход
void Chat::logOutUser(){
   client_->send("BCK");
   client_->send(login_.c_str());
   login_.clear();
   messages_.clear();
}

//Показать меню регистрации
void Chat::showRegistrationMenu() {
     Terminal terminal(config_.getIsColor());//объект для работы с терминалом
     terminal.clearScreen();
     std::string tlogin;
     std::string tpassword;

    //Подключаемся к серверу
    try{
      configClient();//настраиваем клиент
      connectToServer();//подлючаемся к серверу
    }
    catch(const char *e){
      terminal.clearScreen();
      terminal.setColor("ERROR");
      std::cout << e << std::endl;
      terminal.setColor("DEFAULT");
      terminal.waitEnter();
      terminal.clearScreen();
      return;
    }
    catch(...){
      terminal.clearScreen();
      terminal.setColor("ERROR");
      std::cout << "Unknown exception!" << std::endl;
      terminal.setColor("DEFAULT");
      terminal.waitEnter();
      terminal.clearScreen();
      return;
    }
     
     terminal.setColor("FIRST");
     std::cout << "Введите регистрационные данные" << std::endl;
     std::cout << "Логин: ";
     terminal.setColor("INSERT");
     std::cin >> tlogin;

     //Проверяем соответствует ли логин требованиям 
     if (tlogin.length() < 3) {
         terminal.clearScreen();
         terminal.setColor("ERROR");
         std::cout << "Логин очень короткий! Логин должен быть более 2 символов." << std::endl;
         terminal.setColor("DEFAULT");
         terminal.waitEnter();
         terminal.clearScreen();
         return;
     }

     if (tlogin.length() > 8) {
         terminal.clearScreen();
         terminal.setColor("ERROR");
         std::cout << "Логин очень длинный! Логин должен быть не более 8 символов." << std::endl;
         terminal.setColor("DEFAULT");
         terminal.waitEnter();
         terminal.clearScreen();
         return;
     }


     terminal.setColor("FIRST");
     std::cout << "Пароль: ";
     terminal.setColor("INSERT");
     std::cin >> tpassword;

     SHA256 sha256;
     Convert convert;//объект для конвертирования

     //Отправляем логин и пароль
     client_->send("USR");
     client_->send(tlogin.c_str());
     client_->send((sha256(tpassword)).c_str());
      
     //Получаем результат
     char m[lengthMessage];
     client_->receive(m, lengthMessage);

     int res = convert.charToInt(m);

     if(res == 1){
         terminal.clearScreen();
         terminal.setColor("INSERT");
         std::cout << "Поздравляем! Регистрация прошла успешно." << std::endl;
         terminal.setColor("DEFAULT");
         terminal.waitEnter();
         terminal.clearScreen();
     }
     else if(res == 2){
         terminal.clearScreen();
         terminal.setColor("ERROR");
         std::cout << "Этот логин занят!" << std::endl;
         terminal.setColor("DEFAULT");
         terminal.waitEnter();
         terminal.clearScreen();
     }

     client_->send("END");
     disconnect();
     terminal.clearScreen();
}

//Показать меню для написания сообщений
void Chat::showWriteMessageMenu() {
    Terminal terminal(config_.getIsColor());//объект для работы с терминалом
    Convert convert;//объект для конвертирования
    std::string to;
    std::string text;
        
    terminal.setColor("FIRST");
    std::cout << "Кому писать сообщение(all в общий чат): ";
    terminal.setColor("INSERT");
    std::cin >> to;
    terminal.setColor("FIRST");
    std::cout << "Текст сообщения: ";
    terminal.setColor("INSERT");
    std::cin.ignore();
    std::getline(std::cin, text);
    
    //Если поле пустое
    if (text.empty()) {
       terminal.clearScreen();
       terminal.setColor("ERROR");
       std::cout << "Поле сообщение пустое!!!" << std::endl;
       terminal.setColor("DEFAULT");
       terminal.waitEnter();
       return;
    }

     //Отправляем данные на сервер
     client_->send("ADM");
     client_->send(login_.c_str());
     client_->send(to.c_str());
     client_->send(text.c_str());
      
     //Получаем результат
     char m[lengthMessage];
     client_->receive(m, lengthMessage);

     int res = convert.charToInt(m);

     if(res == 1){
         terminal.clearScreen();
         terminal.setColor("INSERT");
         std::cout << "Сообщение отправлено!" << std::endl;
         terminal.setColor("DEFAULT");
         terminal.waitEnter();
         terminal.clearScreen();
     }
     else if(res == 2){
         terminal.clearScreen();
         terminal.setColor("ERROR");
         std::cout << "Пользователя с таким логином нет в чате" << std::endl;
         terminal.setColor("DEFAULT");
         terminal.waitEnter();
         terminal.clearScreen();
     }
     terminal.setColor("DEFAULT");
}

//Получить список пользователей
void Chat::receiveUsers(){
   Convert convert;//объект для конвертирования

   char m[lengthMessage];
   client_->receive(m, lengthMessage);
   
   size_t amount = convert.charToSizeT(m);
  
   //Получаем сообщения
   for(size_t i = 0; i < amount; ++i){
      //Получаем логин
      client_->receive(m, lengthMessage);
      std::string login = m;
      
      //Добавляем в вектор
      users_.emplace_back(login);
   }
}

//Получить бит цвета
bool Chat::getIsColor() const{
   return config_.getIsColor();
}
