//Файл logger.h
#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

//Класс для логгирования сообщений
class Logger{
   std::string nameFile_;//имя файла для логирования
   std::fstream file_; //объект для работы с файлом 
   std::mutex mutex;//мьютекс
   std::vector<std::thread> tv;//вектор потоков
   
   //Записать в файл
   void writeToFile(const std::string &str);
   //Прочитать строку
   std::string readFromFile();
public:
   //Конструктор по умолчанию
   Logger();
   //Конструктор с параметрами
   explicit Logger(const std::string &nameFile);

   //Деструктор класса 
   ~Logger();

   //Запись строки сообщений в файл
   void writeLine(const std::string &line);

   //Чтение строки сообщений из файла
   std::string readLine();
};
