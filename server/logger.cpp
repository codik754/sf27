//Файл logger.cpp
#include "logger.h"
#include <algorithm>

//Конструктор по умолчанию
Logger::Logger() : nameFile_("log.txt") {
   file_ = std::fstream(nameFile_, std::ios::in | std::ios::out | std::ios::app);   
   //Если файл не открыт
   if(!file_.is_open()){
      std::string str = "Error open file " + nameFile_;
      throw str;
   }
}

//Конструктор с параметрами
Logger::Logger(const std::string &nameFile) : nameFile_(nameFile) {
   file_ = std::fstream(nameFile_, std::ios::in | std::ios::out | std::ios::app);   
   //Если файл не открыт
   if(!file_.is_open()){
      std::string str = "Error open file " + nameFile_;
      throw str;
   }
}

//Деструктор класса 
Logger::~Logger(){
   //Ждем завершения всех потоков
   std::for_each(tv.begin(), tv.end(), [](std::thread &t){
      if(t.joinable()){
         t.join();
      }
   });

   //Закрываем файл
   file_.close();
}

//Записать в файл
void Logger::writeToFile(const std::string &str){
   //Лочим мьютекс
   mutex.lock();
   //Перемещаем позицию в конец файла
   file_.seekp(0, std::ios_base::end);
   file_ << str << std::endl;
   //Разлочиваем мьютекс
   mutex.unlock();
}

//Прочитать строку из файла
std::string Logger::readFromFile(){
   //Лочим мьютекс
   mutex.lock();
   //Перемещаем позицию на начало
   file_.seekg(0, std::ios_base::beg);
   std::string str;
   std::getline(file_, str);
   //Разлочиваем мьютекс
   mutex.unlock();
   return str;
}

//Запись строки сообщений
void Logger::writeLine(const std::string &line){
   //Создаем поток
   tv.emplace_back(&Logger::writeToFile, this, line);
}

//Чтение строки сообщений
std::string Logger::readLine(){
   std::string str;//строка для записи
   //создаем поток
   std::thread t([&str, this](){
      str = readFromFile();
   });
   
   //Ждем завершения
   if(t.joinable()){
      t.join();
   }
   return str;
}
