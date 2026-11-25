import pytest_userver.client
import testsuite.utils.http

# [ -- Functional testing -- ]

# basic customer creating tests

async def test_customer_creates_successfully(service_client):
    response = await service_client.post("/cinema-service/customers", params={"name": "Customer1"})
    assert response.status == 201


async def test_customer_cannot_omit_name(service_client):
    response = await service_client.post("/cinema-service/customers", params={})
    assert response.status == 400


async def test_customer_cannot_enter_empty_name(service_client):
    response = await service_client.post("/cinema-service/customers", params={"name": ""})
    assert response.status == 400


async def test_customer_cannot_be_created_twice(service_client):
    response1 = await service_client.post("/cinema-service/customers", params={"name": "Customer2"})
    response2 = await service_client.post("/cinema-service/customers", params={"name": "Customer2"})
    assert response1.status == 201
    assert response2.status == 400

