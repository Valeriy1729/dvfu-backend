async def test_seat_can_be_reserverd_only_once(
        service_client, create_customer, top_customer_balance):

    # Creating customers
    await create_customer("Customer")
    await create_customer("Customer1")

    # Topping Customer's balance
    await top_customer_balance("Customer", 5000)

    # Reserving seat (row=0, column=0)
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "0"})
    assert response.status == 200

    # Reserving seat (row=0, column=0) again
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "0"})
    assert response.status == 409

    # Reserving seat (row=0, column=0) with second customer
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer1", "row": "0", "column": "0"})
    assert response.status == 409


async def test_strange_arguments_when_reserving_seat(
        service_client, create_customer, top_customer_balance):

    # Creating Customer
    await create_customer("Customer")

    # Topping Customer's balance
    await top_customer_balance("Customer", 5000)

    # Reserving seat with row and column out of range
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "100", "column": "0"})
    assert response.status == 400
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "100"})
    assert response.status == 400

    # Reserving seat with negative row and column
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "-1", "column": "0"})
    assert response.status == 400
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "-1"})
    assert response.status == 400

    # Reserving seat with empty row and column
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "", "column": "0"})
    assert response.status == 400
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": ""})
    assert response.status == 400

    # Reserving seat with float row and column
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0.5", "column": "0"})
    assert response.status == 400
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "9.3"})
    assert response.status == 400

    # Reserving seat with text row and column
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "abc", "column": "0"})
    assert response.status == 400
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "abc"})
    assert response.status == 400


async def test_reserving_seat_with_huge_name(service_client):
    # Reserving seat with too big customer name
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "a" * 10_000, "row": "0", "column": "0"})
    assert response.status == 414


async def test_reserving_seat_with_huge_row(
        service_client, create_customer, top_customer_balance):

    # Creating Customer
    await create_customer("Customer")

    # Topping Customer's balance
    await top_customer_balance("Customer", 5000)

    # Reserving seat with huge row
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "1" * 10_000, "column": "0"})
    assert response.status == 414


async def test_reserving_seat_with_huge_column(
        service_client, create_customer, top_customer_balance):

    # Creating Customer
    await create_customer("Customer")

    # Topping Customer's balance
    await top_customer_balance("Customer", 5000)

    # Reserving seat with huge column
    response = await service_client.patch("/cinema-service/reserve",
                params={"name": "Customer", "row": "0", "column": "1" * 10_000})
    assert response.status == 414

