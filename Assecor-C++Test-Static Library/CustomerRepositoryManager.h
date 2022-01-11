#pragma once
#include "CustomerRepositoryBase.h"

#include <memory>
#include <string>

namespace MyAssecorLibrary
{
	class CustomerRepositoryManager
	{
	public:
		CustomerRepositoryManager() = default;
		~CustomerRepositoryManager() = default;

		CreateRepositoryResult createCustomerRepositoryInMemory();

		/*
		* more methodes for creating a repository for storing data e.g. in file
		CreateRepositoryResult createCustomerRepositoryInFile(const std::string& fileName);
		*/

		CustomerRepositoryBase* getCurrentCustomerRepository();
		CustomerRepositoryBase const* getCurrentCustomerRepository() const;

		AddResult addCustomer(const CUSTOMER& aCustomer) const;
		std::pair<GetResult, std::optional<std::reference_wrapper<CUSTOMER>>> getCustomerByID(const IDTYPE& id) const;
		std::pair<GetResult, std::optional<std::reference_wrapper<std::vector<CUSTOMER>>>> getAllCustomers();
		std::pair<GetResult, std::optional<std::reference_wrapper<const std::vector<CUSTOMER>>>> getAllCustomers() const;

		// method just for gTest (mocking)
		void setCustomerRepository(std::unique_ptr<CustomerRepositoryBase>&& customerRepository);

	private:
		std::unique_ptr<CustomerRepositoryBase> _CustomerRepository;
	};
}