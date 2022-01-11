#pragma once
#include "customer.h"
#include "RepositoryResults.h"

#include <vector>
#include <stdint.h>
#include <optional> 

namespace MyAssecorLibrary
{
	typedef decltype(CUSTOMER::id) IDTYPE;

	// pure virtual class as Base for concrete implementation of the CustomerRepository (InMemory, InFile, InCloud,...)
	class CustomerRepositoryBase
	{
	public:
		CustomerRepositoryBase() = default;
		CustomerRepositoryBase(CustomerRepositoryBase& rhs) = delete;
		CustomerRepositoryBase(CustomerRepositoryBase&& rhs) = delete;
		virtual ~CustomerRepositoryBase() = default;

		virtual AddResult addCustomer(const CUSTOMER& aCustomer) = 0;
		virtual std::pair<GetResult, std::optional<std::reference_wrapper<CUSTOMER>>> getCustomerByID(const IDTYPE& id) = 0;
		virtual std::pair<GetResult, std::reference_wrapper<std::vector<CUSTOMER>>> getAllCustomers() = 0;
	};
}

