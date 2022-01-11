#pragma once

#include "CustomerRepositoryManager.h"

namespace MyAssecorLibrary
{
	class Formatter
	{
	public:
		Formatter() = default;
		~Formatter() = default;

		std::pair<GetResult, std::string> getCustomerByID(const CustomerRepositoryManager& customerRepositoryManager, const IDTYPE& id) const;
		std::pair<GetResult, std::vector<std::string>> getAllCustomers(const CustomerRepositoryManager& customerRepositoryManager) const;

	private:
		std::string formatOneCustomer(const CUSTOMER& aCustomer) const;
	};

}