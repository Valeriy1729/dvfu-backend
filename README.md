# Cinema Service

Сервис бронирования мест в кинотеатре на C++ с использованием фреймворка [userver](https://userver.tech/). Предоставляет HTTP API для управления клиентами, банковскими счетами и бронированием мест.

---

## Содержание

- [Возможности](#возможности)
- [Стек](#стек)
- [Структура проекта](#структура-проекта)
- [HTTP API](#http-api)
  - [Клиенты](#клиенты)
  - [Баланс](#баланс)
  - [Места](#места)
  - [Служебное](#служебное)
- [Матрица цен](#матрица-цен)
- [Сборка](#сборка)
- [Тесты](#тесты)
- [Архитектура и конкурентность](#архитектура-и-конкурентность)

---

## Возможности

- **Управление клиентами** — создание, чтение, обновление имени, удаление.
- **Банковские счета** — автоматическое создание счёта при регистрации клиента, пополнение баланса, просмотр баланса.
- **Бронирование мест** — матрица 6×5 с фиксированными ценами, проверка баланса, защита от двойного бронирования.
- **Скидки** — часть клиентов получает случайную скидку 500 единиц на бронирование.
- **Сброс состояния** — служебная ручка для тестов и разработки.

---

## Стек

| Компонент | Версия / примечание |
|-----------|---------------------|
| Язык | C++20 |
| Фреймворк | userver |
| Сборка | CMake |
| Формат ответов | JSON |
| База данных | In-memory (singleton-репозитории) |
| Тесты | GoogleTest (юнит) + pytest (интеграционные) |

---

## Структура проекта

```
.
├── main.cpp                     # точка входа, регистрация компонентов
├── httpHandler.hpp/.cpp         # HTTP-обработчик (userver)
├── serviceLogic.hpp             # декларации бизнес-логики
├── _processRequest.cpp          # маршрутизация по методу и suffix
│
├── models/
│   ├── customer.hpp/.cpp        # модель клиента + JSON-сериализация
│   └── bankAccount.hpp/.cpp     # модель банковского счёта
│
├── repositories/
│   ├── IRepository.hpp          # интерфейс репозитория
│   ├── customersRepository.hpp/.cpp
│   ├── bankAccountsRepository.hpp/.cpp
│   └── seatsRepository.hpp/.cpp
│
├── _settings_.hpp               # константы: размеры, цены, скидки
├── _BadRequestException.hpp     # кастомное исключение → 400
├── _getFromOptional.hpp         # хелпер: optional → value или throw
├── _getArgWithCheck.hpp         # хелпер: извлечение и валидация аргументов
├── _executeWithCheck.hpp        # хелпер: выполнение bool-лямбды с проверкой
├── _pairSerialization.hpp       # JSON-сериализация std::pair
│
├── logic/                       # реализация ручек
│   ├── createCustomer.cpp
│   ├── getCustomer.cpp
│   ├── updateCustomer.cpp
│   ├── deleteCustomer.cpp
│   ├── addMoney.cpp
│   ├── getBalance.cpp
│   ├── reserveSeat.cpp
│   ├── getAvaliableSeats.cpp
│   ├── resetService.cpp
│   └── _throwResourceNotFound.cpp
│
└── tests/
    ├── unit/                    # GoogleTest
    └── integration/             # pytest + conftest.py
```

---

## HTTP API

Базовый префикс: `/cinema-service`

### Клиенты

| Метод | Путь | Параметры | Успех | Ошибки |
|-------|------|-----------|-------|--------|
| `POST` | `/customers` | `name` | `201` | `400` — имя занято/отсутствует |
| `GET` | `/customers` | `name` | `200` + JSON | `400` — не найден |
| `PATCH` | `/customers` | `name`, `new_name` | `200` | `400` — не найден / имя занято |
| `DELETE` | `/customers` | `name` | `200` | `400` — не найден |

**Пример:**

```bash
curl -X POST 'http://localhost:8080/cinema-service/customers?name=Alice'
# Customer 'Alice' created

curl 'http://localhost:8080/cinema-service/customers?name=Alice'
# {"name":"Alice","has_discount":true}
```

### Баланс

| Метод | Путь | Параметры | Успех | Ошибки |
|-------|------|-----------|-------|--------|
| `GET` | `/balance` | `name` | `200` + JSON | `400` — клиент/счёт не найден |
| `PATCH` | `/balance` | `name`, `amount` | `200` | `400` — клиент не найден, `amount <= 0`, переполнение |

**Пример:**

```bash
curl -X PATCH 'http://localhost:8080/cinema-service/balance?name=Alice&amount=3000'
curl 'http://localhost:8080/cinema-service/balance?name=Alice'
# {"name":"Alice","balance":3000}
```

### Места

| Метод | Путь | Параметры | Успех | Ошибки |
|-------|------|-----------|-------|--------|
| `GET` | `/seats` | — | `200` + JSON-массив свободных мест | — |
| `PATCH` | `/reserve` | `name`, `row`, `column` | `200` | `400` — невалидные аргументы, `409` — место занято / мало денег |

**Пример:**

```bash
curl 'http://localhost:8080/cinema-service/seats'
# [[[0,0],1000],[[0,1],1100],...]

curl -X PATCH 'http://localhost:8080/cinema-service/reserve?name=Alice&row=0&column=0'
# Seat (0, 0) reserved with Alice
```

### Служебное

| Метод | Путь | Успех |
|-------|------|-------|
| `DELETE` | `/reset` | `200` — очищает клиентов, счета и брони |

> ⚠️ `reset` не требует аутентификации. **Не выставляйте сервис в публичную сеть без прокси/аутентификации.**

---

## Матрица цен

Места 6×5, цены (в условных единицах):

```
1000 1100 1200 1100 1000
1100 1200 1300 1200 1100
1200 1300 1500 1300 1200
1100 1200 1300 1200 1100
1000 1100 1200 1100 1000
 900 1000 1100 1000  900
```

Клиенты со скидкой платят `max(cost - 500, 0)`.

---

## Сборка

### Зависимости

- CMake ≥ 3.16
- Компилятор с поддержкой C++20 (GCC ≥ 11 / Clang ≥ 14)
- userver (см. [официальную инструкцию](https://userver.tech/dd/dc8/md_en_2userver_2build_2build.html))

### Локальная сборка

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

Бинарник: `build/cinema_booking_service`.

### Запуск

```bash
./build/cinema_service --config configs/static_config.yaml --config configs/config_vars.yaml
```

По умолчанию сервис слушает `0.0.0.0:8080`.

---

## Тесты

### Юнит-тесты (GoogleTest)

```bash
cd build
ctest --output-on-failure
```

Покрывают: модели (`Customer`, `BankAccount`), хелперы (`_getFromOptional`, `_getArgWithCheck`, `_executeWithCheck`), сериализацию `std::pair`, `reset` репозиториев.

### Интеграционные тесты (pytest)

Требуют запущенного сервиса (или поднятого через `pytest_userver`).

```bash
pytest tests/integration/ -v
```

Покрывают: CRUD клиентов, баланс, бронирование, граничные случаи (414 на гигантские аргументы, 400 на невалидные числа), конкурентность (50 клиентов бронируют одно место — ровно одна бронь; 500 параллельных пополнений — корректный итог).

---

## Архитектура и конкурентность

- **Singleton-репозитории** (`SeatsRepository::get()`, `CustomersRepository::get()`, `BankAccountsRepository::get()`) хранят состояние in-memory.
- Каждый репозиторий защищён своим `userver::engine::Mutex`.
- `reserveSeat` дополнительно использует глобальный `reserveSeatMutex`, чтобы сериализовать «проверка → списание → бронь».
- `resetService` использует `resetServiceMutex`.

---
