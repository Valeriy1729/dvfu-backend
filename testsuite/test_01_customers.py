async def test_CRUD_for_success(service_client):
    # Creating Customer
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 201

    # Getting Customer
    response = await service_client.get("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 200

    # Updating Customer to NewCustomer
    response = await service_client.patch("/cinema-service/customers",
            params={"name": "Customer", "new_name": "NewCustomer"})
    assert response.status == 200

    # Getting NewCustomer
    response = await service_client.get("/cinema-service/customers", params={"name": "NewCustomer"})
    assert response.status == 200

    # Deleting NewCustomer
    response = await service_client.delete("/cinema-service/customers", params={"name": "NewCustomer"})
    assert response.status == 200


async def test_methods_for_nonexisting_customer(service_client):
    # Getting Non-existing-name
    response = await service_client.get("/cinema-service/customers", params={"name": "Non-existing-name"})
    assert response.status == 400

    # Updating Non-existing-name
    response = await service_client.patch("/cinema-service/customers",
            params={"name": "Non-existing-name", "new_name": "Name"})
    assert response.status == 400

    # Deleting Non-existing-name
    response = await service_client.delete("/cinema-service/customers", params={"name": "Non-existing-name"})
    assert response.status == 400


async def test_methods_omitting_arguments(service_client):
    # Creating customer without name
    response = await service_client.post("/cinema-service/customers", params={})
    assert response.status == 400

    # Updating customer without name
    response = await service_client.patch("/cinema-service/customers", params={"new_name": "NewCustomer"})
    assert response.status == 400

    # Updating customer without new_name
    response = await service_client.patch("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 400

    # Updating customer without arguments
    response = await service_client.patch("/cinema-service/customers", params={})
    assert response.status == 400

    # Deleting customer without name
    response = await service_client.delete("/cinema-service/customers", params={})
    assert response.status == 400


async def test_huge_name_when_creating(service_client):
    # Creating customer with too long name
    response = await service_client.post("/cinema-service/customers",
                params={"name": "a" * 10_000})
    assert response.status == 414


async def test_huge_new_name_when_updating(service_client):
    # Creating Customer
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 201

    # Updating customer with too long new_name
    response = await service_client.patch("/cinema-service/customers",
            params={"name": "Customer", "new_name": "a" * 10_000})
    assert response.status == 414

    # Deleting Customer
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 200


async def test_huge_new_name_when_updating(service_client):
    # Updating customer with too long new_name
    response = await service_client.patch("/cinema-service/customers",
            params={"name": "a" * 10_000, "new_name": "NewCustomer"})
    assert response.status == 414


async def test_huge_name_when_getting(service_client):
    # Getting customer with too long name
    response = await service_client.get("/cinema-service/customers",
            params={"name": "a" * 10_000})
    assert response.status == 414


async def test_huge_name_when_deleting(service_client):
    # Deleting customer with too long name
    response = await service_client.delete("/cinema-service/customers",
            params={"name": "a" * 10_000})
    assert response.status == 414


async def test_create_same_customer_twice(service_client):
    # Creating Customer
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 201

    # Creating Customer again
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 400

    # Deleting Customer
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer"})
    assert response.status == 200


async def test_updating_to_existing_customer(service_client):
    # Creating Customer1
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer1"})
    assert response.status == 201

    # Creating Customer2
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer2"})
    assert response.status == 201

    # Updating Customer1 to Customer2
    response = await service_client.patch("/cinema-service/customers",
            params={"name": "Customer1", "new_name": "Customer2"})
    assert response.status == 400

    # Deleting Customer1
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer1"})
    assert response.status == 200

    # Deleting Customer2
    response = await service_client.delete("/cinema-service/customers", params={"name": "Customer2"})
    assert response.status == 200

