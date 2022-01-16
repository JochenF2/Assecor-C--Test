#pragma once

//#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Assecor-C++Test-Static Library/CustomerRepositoryInMemory.h"


class MockCustomerRepository : public MyAssecorLibrary::CustomerRepositoryInMemory
{
public:
	using GetCustomerByIDResult = std::pair<MyAssecorLibrary::GetResult, std::optional<std::reference_wrapper<CUSTOMER>>>;
	using GetAllResult =  std::pair<MyAssecorLibrary::GetResult, std::reference_wrapper<std::vector<CUSTOMER>>>;

	MOCK_METHOD(MyAssecorLibrary::AddResult, addCustomer, (const CUSTOMER& customer), (override));
	MOCK_METHOD(GetCustomerByIDResult, getCustomerByID, (const MyAssecorLibrary::IDTYPE& id), (override));
	MOCK_METHOD(GetAllResult, getAllCustomers, (), (override));
};

