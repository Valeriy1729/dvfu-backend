import asyncio


async def test_concurrency_when_many_customers_are_reserving_one_seat(
        service_client, create_customer, top_customer_balance, reserve_seat):

    N = 50

    # Creating Customers with names Customer{i}
    Tasks = [create_customer(f"Customer{i}") for i in range(N)]
    Responses = await asyncio.gather(*Tasks)
    for Response in Responses:
        assert Response.status == 201

    # Topping balance for Customer{i} by 3000
    Tasks = [top_customer_balance(f"Customer{i}", 3000) for i in range(N)]
    Responses = await asyncio.gather(*Tasks)
    for Response in Responses:
        assert Response.status == 200

    # task{i} execution leads to buying seat (row=1, column=1) by Customer{i}
    Tasks = [reserve_seat(f"Customer{i}", 1, 1) for i in range(N)]

    # Starting all N tasks concurrently
    Responses = await asyncio.gather(*Tasks)

    # There must be only one reservation in result
    reservations_count = sum(int(r.status == 200) for r in Responses)
    assert reservations_count == 1



async def test_concurrency_when_topping_balance(
        service_client, create_customer, top_customer_balance):

    N = 500

    # Creating Customer
    await create_customer("Customer")

    # Creating N tasks
    # Every task topping balance by 1
    Tasks = [top_customer_balance("Customer", 1) for _ in range(N)]

    # Starting all N tasks concurrently
    Responses = await asyncio.gather(*Tasks)

    for Response in Responses:
        assert Response.status == 200

    # Getting Customer's balance
    response = await service_client.get("/cinema-service/balance", params={"name": "Customer"})
    assert response.status == 200
    assert response.json()['balance'] == N


