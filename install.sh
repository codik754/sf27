#!/bin/bash

port=55000
isColor="true"
logindb="root"
passworddb="123456"
namedb="sf25db"
addressdb="localhost"
address="127.0.0.1"

nameDir="done"
if [ -d $nameDir ]; then
   rm -rvf $nameDir
fi

mkdir $nameDir

cd createdb
make
#Проверяем на успешность выполнения
if [[ $? -ne 0 ]]
then
   echo "Ошибка. Посмотрите README.md"
   exit
fi
mv createdb ../$nameDir

cd ../deletedb
make
#Проверяем на успешность выполнения
if [[ $? -ne 0 ]]
then
   echo "Ошибка. Посмотрите README.md"
   exit
fi
mv deletedb ../$nameDir

cd ../server
make
#Проверяем на успешность выполнения
if [[ $? -ne 0 ]]
then
   echo "Ошибка. Посмотрите README.md"
   exit
fi
mv serverforchat ../$nameDir

cd ../client
make
#Проверяем на успешность выполнения
if [[ $? -ne 0 ]]
then
   echo "Ошибка. Посмотрите README.md"
   exit
fi
mv clientforchat ../$nameDir

cd ..

echo "=============================================================="
echo "Такие настройки будут установлены для работы чата:"
echo 
echo "Адрес сервера для чата: ${address}"
echo "Порт: ${port}"
echo "Цветной интерфейс: ${isColor}"
echo "=============================================================="

answer="q"
while [[ ( "$answer" != "y" ) && ( "$answer" != "n" ) ]]
do
   echo -n "Все верно?(y-да/n-нет): "
   read answer
done

if [[ "$answer" == "n"  ]]
then
   while [[ "$answer" == "n" ]]
   do
     echo -n "Адрес сервера для чата: "
     read address
     echo -n "Введите номер порта: "
     read port
     echo -n "Цветной интерфейс(false - нет): "
     read isColor

     echo "=============================================================="
     echo "Такие настройки будут установлены для работы чата:"
     echo
     echo "Адрес сервера для чата: ${address}"
     echo "Порт: ${port}"
     echo "Цветной интерфейс: ${isColor}"
     echo "=============================================================="
     
     answer="q"
     while [[ ( "$answer" != "y" ) && ( "$answer" != "n" ) ]]
     do
        echo -n "Все верно?(y-да/n-нет): "
        read answer
     done
   done
fi

echo "=============================================================="
echo "Такие настройки будут установлены для связи с MySQL сервером:"
echo
echo "Адрес сервера: ${addressdb}"
echo "Логин: ${logindb}"
echo "Пароль: ${passworddb}"
echo "Имя базы данных: ${namedb}"
echo "=============================================================="

answer="q"
while [[ ( "$answer" != "y" ) && ( "$answer" != "n" ) ]]
do
   echo -n "Все верно?(y-да/n-нет): "
   read answer
done

if [[ "$answer" == "n"  ]]
then
   while [[ "$answer" == "n" ]]
   do
     echo -n "Введите адрес сервера MySQL:"
     read addressdb
     echo -n "Введите логин: "
     read logindb
     echo -n "Введите пароль: "
     read passworddb
     echo -n "Введите имя БД: "
     read namedb

     echo "=============================================================="
     echo "Такие настройки будут установлены для связи с MySQL сервером:"
     echo
     echo "Адрес сервера: ${addressdb}"
     echo "Логин: ${logindb}"
     echo "Пароль: ${passworddb}"
     echo "Имя базы данных: ${namedb}"
     echo "=============================================================="
     
     answer="q"
     while [[ ( "$answer" != "y" ) && ( "$answer" != "n" ) ]]
     do
        echo -n "Все верно?(y-да/n-нет): "
        read answer
     done
   done
fi

cd $nameDir
echo "{" > client.json
echo "{" > client.json
echo "   \"address\" : \"$address\"," >> client.json
echo "   \"port\" : $port," >> client.json
echo "   \"isColor\" : $isColor" >> client.json
echo "}" >> client.json

echo "{" > server.json
echo "   \"port\" : $port," >> server.json
echo "   \"isColor\" : $isColor," >> server.json
echo "   \"addressdb\" : \"$addressdb\"," >> server.json
echo "   \"logindb\" : \"$logindb\"," >> server.json
echo "   \"passworddb\" : \"$passworddb\"," >> server.json
echo "   \"namedb\" : \"$namedb\"" >> server.json
echo "}" >> server.json

echo "Файлы с конфигурациями сделаны!"
