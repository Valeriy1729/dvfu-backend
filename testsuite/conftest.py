import pytest

# Adding a plugin from userver/testsuite/pytests_plugins/

pytest_plugins = ['pytest_userver.plugins.core']


@pytest.fixture(autouse=True)
async def reset_service(service_client):
    response = await service_client.delete(
            "/cinema-service/reset")
    assert response.status == 200


@pytest.fixture
async def create_customer(service_client):

    async def _factory(customer_name: str):
         # Creating Customer
         response = await service_client.post(
                 "/cinema-service/customers",
                 params={"name": customer_name})
         return response

    yield _factory  # test...


@pytest.fixture
async def top_customer_balance(service_client):

    async def _factory(customer_name: str, amount: int):
        # Topping balance
        response = await service_client.patch(
                "/cinema-service/balance",
                params={"name": customer_name, "amount": amount})
        return response

    return _factory


@pytest.fixture
async def reserve_seat(service_client):

    async def _factory(customer_name: str, row: int, column: int):
        # Reserving seat
        response = await service_client.patch(
                "/cinema-service/reserve",
                params={"name": customer_name, "row": row, "column": column})
        return response

    return _factory

