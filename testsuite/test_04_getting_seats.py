async def test_getting_avaliable_seats_is_successful(service_client):
    # Getting avaliable seats
    response = await service_client.get("/cinema-service/seats")
    expected_string: str = (
         "[[[0,0],1000],[[0,1],1100],"
         "[[0,2],1200],[[0,3],1100],[[0,4],1000],[[1,0],1100],"
         "[[1,1],1200],[[1,2],1300],[[1,3],1200],[[1,4],1100],"
         "[[2,0],1200],[[2,1],1300],[[2,2],1500],[[2,3],1300],"
         "[[2,4],1200],[[3,0],1100],[[3,1],1200],[[3,2],1300],"
         "[[3,3],1200],[[3,4],1100],[[4,0],1000],[[4,1],1100],"
         "[[4,2],1200],[[4,3],1100],[[4,4],1000],[[5,0],900],"
         "[[5,1],1000],[[5,2],1100],[[5,3],1000],[[5,4],900]]"
    )
    assert response.status == 200
    assert response.text == expected_string


async def test_only_avaliable_seats_are_taken(
        service_client, create_customer, top_customer_balance, reserve_seat):

    # Creating Customer
    await create_customer("Customer")

    # Topping Customer's balance
    await top_customer_balance("Customer", 5000)

    # Reserving seat (row=0, column=0)
    await reserve_seat("Customer", 0, 0)

    # Getting avaliable seats
    # [[0,0],1000] was just reserved
    response = await service_client.get("/cinema-service/seats")
    expected_string: str = (
         "[[[0,1],1100],[[0,2],1200],[[0,3],1100],[[0,4],1000],[[1,0],1100],"
         "[[1,1],1200],[[1,2],1300],[[1,3],1200],[[1,4],1100],"
         "[[2,0],1200],[[2,1],1300],[[2,2],1500],[[2,3],1300],"
         "[[2,4],1200],[[3,0],1100],[[3,1],1200],[[3,2],1300],"
         "[[3,3],1200],[[3,4],1100],[[4,0],1000],[[4,1],1100],"
         "[[4,2],1200],[[4,3],1100],[[4,4],1000],[[5,0],900],"
         "[[5,1],1000],[[5,2],1100],[[5,3],1000],[[5,4],900]]"
    )
    assert response.status == 200
    assert response.text == expected_string

