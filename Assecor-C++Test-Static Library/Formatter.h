#pragma once

#include "CustomerRepositoryManager.h"


namespace MyAssecorLibrary
{
	class Formatter
	{
	public:
		explicit Formatter(std::reference_wrapper<const CustomerRepositoryManager>&& customerRepositoryManager);
		Formatter() = delete;
		Formatter(Formatter&& rhs) = delete;
		Formatter(const Formatter& rhs) = delete;
		~Formatter() = default;

		std::pair<GetResult, std::string> getCustomerByID(const IDTYPE& id) const;
		std::pair<GetResult, std::vector<std::string>> getAllCustomers() const;

	private:
		std::string formatOneCustomer(const CUSTOMER& aCustomer) const;

	private:
		std::reference_wrapper<const CustomerRepositoryManager> _CustomerRepositoryManager;
	};

}