async def test_balance_operations_for_success(service_client):
    # Creating Customer
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 201

    # Getting balance of Customer
    response = await service_client.get("/cinema-service/balance", params={"name": "Customer"})
    assert response.status == 200
    assert response.json()['balance'] == 0

    # Topping Customer's balance
    response = await service_client.patch("/cinema-service/balance", params={"name": "Customer", "amount": "1000"})
    assert response.status == 200

    # Getting balance of Customer
    response = await service_client.get("/cinema-service/balance", params={"name": "Customer"})
    assert response.status == 200
    assert response.json()['balance'] == 1000

    # Deleting Customer
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 200


async def test_user_cannot_get_balance_of_nonexisting_customer(service_client):
    # Getting balance of Non-existing-name
    response = await service_client.get("/cinema-service/balance", params={"name": "Non-existing-name"})
    assert response.status == 400


async def test_user_cannot_get_balance_without_name(service_client):
    # Getting balance without name
    response = await service_client.get("/cinema-service/balance", params={})
    assert response.status == 400


async def test_user_cannot_top_balance_of_nonexisting_customer(service_client):
    # Topping balance of Non-existing-name
    response = await service_client.patch("/cinema-service/balance",
                params={"name": "Non-existing-name", "amount": "1000"})
    assert response.status == 400


async def test_user_cannot_top_balance_without_arguments(service_client):
    # Creating Customer
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 201

    # Topping balance without name
    response = await service_client.patch("/cinema-service/balance", params={"amount": "1000"})
    assert response.status == 400

    # Topping balance without amount
    response = await service_client.patch("/cinema-service/balance", params={"name": "Customer"})
    assert response.status == 400

    # Deleting Customer
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 200


async def test_user_cannot_top_balance_with_strange_amount(service_client):
    # Creating Customer
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 201

    # Topping balance with zero amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": "0"})
    assert response.status == 400

    # Topping balance with negative amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": "-1000"})
    assert response.status == 400

    # Topping balance with float amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": "10.5"})
    assert response.status == 400

    # Topping balance with empty amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": ""})
    assert response.status == 400

    # Topping balance with text amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": "thousand"})
    assert response.status == 400

    # Deleting Customer
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 200


async def test_topping_balance_with_big_amount(service_client):
    # Topping balance with too big amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": str(10 ** 100)})
    assert response.status == 400

    # Topping balance with huge amount
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "Customer", "amount": "1" * 10_000})
    assert response.status == 414


async def test_topping_balance_with_huge_name(service_client):
    # Topping balance with huge name
    response = await service_client.patch("/cinema-service/balance",
                    params={"name": "a" * 10_000, "amount": "10"})
    assert response.status == 414


async def test_getting_balance_with_huge_name(service_client):
    # Getting balance with huge name argument
    response = await service_client.get("/cinema-service/balance", params={"name": "a" * 10_000})
    assert response.status == 414


