# Домашнее задание по модулю 27

## По заданию
Нужный класс реализован в файлах logger.h и logger.cpp. В методе int ServerChat::addMessage() реализована запись в файл с помощью объекта класса Logger.

## Для работы программы нужно:
Установленный и работающий сервер MySQL

## Для работы программы нужны библиотеки:
Библиотека для работы с MySQL. Для Ubuntu можно установить так:
* sudo apt install libmysql++-dev

JSON for Modern C++. Для Ubuntu можно установить так:
* sudo apt install nlohmann-json3-dev

## Как устанавливать программу:
* ./install.sh

В директории done появятся готовые файлы

## В папке done следующие програмные файлы:
* createdb - создает БД с нужными таблицами
* deletedb - удаляет БД
* clientforchat - клиент для чата
* serverforchat - сервер для чата

## В папке done следующие конфигурационные файлы:
* server.json - файл с настройками для сервера
* client.json - файл с настройками для клиента 

## Полезная информация:
Пароль для пользователя admin: a123
