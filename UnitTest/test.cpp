//#include "pch.h"

#include "MockCustomerRepository.h"

#include "../Assecor-C++Test-Static Library/CustomerRepositoryManager.h"
#include "../Assecor-C++Test-Static Library/Formatter.h"


TEST(AddTest, TestLibrary) {
  
	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.createCustomerRepositoryInMemory();

	auto addResult = customerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	EXPECT_EQ(addResult, MyAssecorLibrary::AddResult::eOk);

	addResult = customerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Test", .last_name = "Tester", .zip_code = "01119", .city = "Dresden", .favorite_color = 2 });

	EXPECT_EQ(addResult, MyAssecorLibrary::AddResult::eDuplicatedID);
}

TEST(GetTest, TestLibrary) {

	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.createCustomerRepositoryInMemory();

	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 1, .first_name = "Guido", .last_name = "Zahn", .zip_code = "12219", .city = "Berlin", .favorite_color = 1 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 2, .first_name = "Peter", .last_name = "Mahn", .zip_code = "01119", .city = "Dresden", .favorite_color = 2 });

	auto [getResult, customer] = customerRepositoryManager.getCustomerByID(2);
	EXPECT_EQ(getResult, MyAssecorLibrary::GetResult::eOk);

	auto [getResult2, customer2] = customerRepositoryManager.getCustomerByID(20);
	EXPECT_EQ(getResult2, MyAssecorLibrary::GetResult::eIDNotFound);
}

TEST(GetTestWithFormatter, TestLibrary) {

	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.createCustomerRepositoryInMemory();

	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 1, .first_name = "Guido", .last_name = "Zahn", .zip_code = "12219", .city = "Berlin", .favorite_color = 1 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 2, .first_name = "Peter", .last_name = "Mahn", .zip_code = "01119", .city = "Dresden", .favorite_color = 2 });

	MyAssecorLibrary::Formatter aFormatter(std::ref(customerRepositoryManager));
	auto [getResult, customer] = aFormatter.getCustomerByID(20);

	EXPECT_EQ(getResult, MyAssecorLibrary::GetResult::eIDNotFound);
	EXPECT_EQ(customer, std::string("(no customer)"));
}


TEST(GetAllCustomerTest, TestLibrary) {

	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.createCustomerRepositoryInMemory();

	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 1, .first_name = "Guido", .last_name = "Zahn", .zip_code = "12219", .city = "Berlin", .favorite_color = 1 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 2, .first_name = "Peter", .last_name = "Mahn", .zip_code = "01119", .city = "Dresden", .favorite_color = 2 });

	auto [getResult, customers] = customerRepositoryManager.getAllCustomers();
	EXPECT_EQ(getResult, MyAssecorLibrary::GetResult::eOk);
	
	EXPECT_EQ(customers.value().get()[2].id, 2);
}

TEST(GetAllCustomerTestWithFormatter, TestLibrary) {

	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.createCustomerRepositoryInMemory();

	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 1, .first_name = "Guido", .last_name = "Zahn", .zip_code = "12219", .city = "Berlin", .favorite_color = 1 });
	customerRepositoryManager.addCustomer(CUSTOMER{ .id = 2, .first_name = "Peter", .last_name = "Mahn", .zip_code = "01119", .city = "Dresden", .favorite_color = 2 });

	MyAssecorLibrary::Formatter aFormatter(std::ref(customerRepositoryManager));
	auto [getResult, customers]  = aFormatter.getAllCustomers();

	EXPECT_EQ(getResult, MyAssecorLibrary::GetResult::eOk);
	EXPECT_EQ(customers[2], std::string("Mahn, Peter, 01119, Dresden, favorite color: 2"));
}

TEST(MockTest_GetCustomerByID_OK, TestLibrary) 
{
	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.setCustomerRepository(std::make_unique<MockCustomerRepository>());

	CUSTOMER aCustomer({ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	customerRepositoryManager.addCustomer(aCustomer);
	
	auto currentCustomerRepo = dynamic_cast<MockCustomerRepository*>(customerRepositoryManager.getCurrentCustomerRepository());
	std::optional<std::reference_wrapper<CUSTOMER>> expectedCustomer(aCustomer);

	auto retValue = std::pair(MyAssecorLibrary::GetResult::eOk, expectedCustomer);
	auto myAction = testing::Return(retValue);
	EXPECT_CALL(*currentCustomerRepo, getCustomerByID).WillOnce(myAction);
	
	customerRepositoryManager.getCustomerByID(0);
}

TEST(MockTest_GetCustomerByID_Fail, TestLibrary)
{
	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.setCustomerRepository(std::make_unique<MockCustomerRepository>());

	CUSTOMER aCustomer({ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	customerRepositoryManager.addCustomer(aCustomer);

	auto currentCustomerRepo = dynamic_cast<MockCustomerRepository*>(customerRepositoryManager.getCurrentCustomerRepository());
	std::optional<std::reference_wrapper<CUSTOMER>> expectedCustomer(aCustomer);

	auto retValue = std::pair(MyAssecorLibrary::GetResult::eIDNotFound, std::nullopt);
	auto myAction = testing::Return(retValue);
	EXPECT_CALL(*currentCustomerRepo, getCustomerByID).WillOnce(myAction);

	customerRepositoryManager.getCustomerByID(1);
}

TEST(MockTest_GetAllCustomer, TestLibrary)
{
	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.setCustomerRepository(std::make_unique<MockCustomerRepository>());

	std::vector<CUSTOMER> theCustomers({ 
		{.id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 },
		{.id = 1, .first_name = "Hannes", .last_name = "Bla", .zip_code = "12209", .city = "Berlin", .favorite_color = 11 },
		{.id = 2, .first_name = "Test", .last_name = "Rainer", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 } });

	customerRepositoryManager.addCustomer(theCustomers[0]);
	customerRepositoryManager.addCustomer(theCustomers[1]);
	customerRepositoryManager.addCustomer(theCustomers[2]);

	auto currentCustomerRepo = dynamic_cast<MockCustomerRepository*>(customerRepositoryManager.getCurrentCustomerRepository());
	std::reference_wrapper<std::vector<CUSTOMER>> result1(theCustomers);

	auto retValue = std::pair(MyAssecorLibrary::GetResult::eOk, result1);
	auto myAction = testing::Return(retValue);
	EXPECT_CALL(*currentCustomerRepo, getAllCustomers).WillOnce(myAction);

	customerRepositoryManager.getAllCustomers();
}

TEST(MockTest_AddCustomer_OK, TestLibrary)
{
	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.setCustomerRepository(std::make_unique<MockCustomerRepository>());

	std::vector<CUSTOMER> theCustomers({
		{.id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 },
		{.id = 1, .first_name = "Hannes", .last_name = "Bla", .zip_code = "12209", .city = "Berlin", .favorite_color = 11 },
		{.id = 2, .first_name = "Test", .last_name = "Rainer", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 } });

	customerRepositoryManager.addCustomer(theCustomers[0]);
	customerRepositoryManager.addCustomer(theCustomers[1]);
	customerRepositoryManager.addCustomer(theCustomers[2]);

	auto currentCustomerRepo = dynamic_cast<MockCustomerRepository*>(customerRepositoryManager.getCurrentCustomerRepository());

	EXPECT_CALL(*currentCustomerRepo, addCustomer).WillOnce(testing::Return(MyAssecorLibrary::AddResult::eOk));

	customerRepositoryManager.addCustomer({ .id = 5, .first_name = "Jane", .last_name = "Doe", .zip_code = "12209", .city = "Berlin", .favorite_color = 99 });
}

TEST(MockTest_AddCustomer_Fail, TestLibrary)
{
	MyAssecorLibrary::CustomerRepositoryManager customerRepositoryManager;

	customerRepositoryManager.setCustomerRepository(std::make_unique<MockCustomerRepository>());

	std::vector<CUSTOMER> theCustomers({
		{.id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 },
		{.id = 1, .first_name = "Hannes", .last_name = "Bla", .zip_code = "12209", .city = "Berlin", .favorite_color = 11 },
		{.id = 2, .first_name = "Test", .last_name = "Rainer", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 } });

	customerRepositoryManager.addCustomer(theCustomers[0]);
	customerRepositoryManager.addCustomer(theCustomers[1]);
	customerRepositoryManager.addCustomer(theCustomers[2]);

	auto currentCustomerRepo = dynamic_cast<MockCustomerRepository*>(customerRepositoryManager.getCurrentCustomerRepository());

	EXPECT_CALL(*currentCustomerRepo, addCustomer).WillOnce(testing::Return(MyAssecorLibrary::AddResult::eDuplicatedID));

	customerRepositoryManager.addCustomer({ .id = 2, .first_name = "Jane", .last_name = "Doe", .zip_code = "12209", .city = "Berlin", .favorite_color = 99 });
}
