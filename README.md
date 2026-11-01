# Cinema Booking Service

HTTP-сервис для бронирования мест в кинотеатре с управлением клиентами и банковскими счетами. C++20, Boost.Asio/Beast (async coroutines), Boost.JSON.

## Требования

- C++20 (GCC ≥ 11, Clang ≥ 14, MSVC ≥ 19.30)
- Boost ≥ 1.81: `beast`, `asio`, `json`, `url`

## Сборка и запуск

```bash
mkdir build && cd build && cmake .. && cmake --build .
./my_app <host> <port>
# Пример: ./my_app 127.0.0.1 8080
```

## Архитектура

```
HttpServer (server.h)  →  ServiceLogic (serviceLogic.h)
                            ├── CustomersRepository
                            ├── BankAccountsRepository
                            └── SeatsRepository
```

- **`settings.h`** — константы: зал 6×5, цены, скидка 500 каждому 5-му клиенту, лимиты HTTP
- **`repositories/*.h`** — in-memory синглтоны
- **`*.cpp`** — хендлеры `ServiceLogic` (по одному на эндпоинт)

Все данные в памяти — теряются при перезапуске.

## API

Тело `POST`/`PATCH` — `application/x-www-form-urlencoded`.

| Метод | Путь | Параметры | Успех |
|-------|------|-----------|-------|
| `POST` | `/customers` | body: `name` | `201` |
| `GET` | `/customers` | `?name=` | `200` + JSON |
| `PATCH` | `/customers` | `?name=`, body: `newName` | `204` |
| `DELETE` | `/customers` | `?name=` | `204` |
| `PATCH` | `/balance` | `?name=`, body: `amount` | `204` |
| `GET` | `/balance` | `?name=` | `200` + JSON |
| `GET` | `/seats` | — | `200` + JSON |
| `PATCH` | `/seats/reserve` | body: `name`, `row`, `column` | `200` |

**Примеры ответов:**

```json
// GET /customers?name=Ivan
{ "name": "Ivan", "hasDiscount": true }

// GET /balance?name=Ivan
{ "balance": 4500 }

// GET /seats
[ [ [0, 0], 1000 ], [ [0, 1], 1100 ] ]
```

**Выполнил: Мигачев В., Б9124-02.03.01мо**
