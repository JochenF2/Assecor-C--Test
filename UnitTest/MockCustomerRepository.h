#pragma once

//#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Assecor-C++Test-Static Library/CustomerRepositoryInMemory.h"


class MockCustomerRepository : public MyAssecorLibrary::CustomerRepositoryInMemory
{
public:
	MOCK_METHOD1(getCustomerByID, std::pair<MyAssecorLibrary::GetResult, std::optional<std::reference_wrapper<CUSTOMER>>>(const MyAssecorLibrary::IDTYPE& id));
	MOCK_METHOD1(addCustomer, MyAssecorLibrary::AddResult(const CUSTOMER& id));
	MOCK_METHOD0(getAllCustomers, std::pair<MyAssecorLibrary::GetResult, std::reference_wrapper<std::vector<CUSTOMER>>>());
};

