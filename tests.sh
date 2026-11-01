#!/usr/bin/bash

echo "Создание нового покупателя. Каждому пятому покупателю присваивается скидка"
curl http://localhost:1234/customers -X POST -d "name=Bob" --verbose
printf "\n\n\n"

echo "Пополнение баланса покупателя на 1000"
curl http://localhost:1234/balance?name=Bob -X PATCH -d "amount=1000" --verbose
printf "\n\n\n"

echo "Вывод всех свободных мест c ценами"
curl http://localhost:1234/seats -X GET --verbose
printf "\n\n\n"

echo "Покупка свободного места"
curl http://localhost:1234/seats/reserve? -X PATCH -d "name=Bob&row=0&column=0" --verbose
printf "\n\n\n"

echo "Вывод баланса"
curl http://localhost:1234/balance?name=Bob -X GET --verbose
printf "\n\n\n"

echo "Изменение имени пользователя"
curl http://localhost:1234/customers?name=Bob -X PATCH -d "newName=Alex" --verbose
printf "\n\n\n"

echo "Получение пользователя"
curl http://localhost:1234/customers?name=Alex -X GET --verbose
printf "\n\n\n"

echo "Удаление пользователя"
curl http://localhost:1234/customers?name=Alex -X DELETE --verbose
printf "\n\n\n"

