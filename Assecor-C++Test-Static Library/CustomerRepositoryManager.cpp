#include "CustomerRepositoryManager.h"
#include "CustomerRepositoryInMemory.h"

namespace MyAssecorLibrary
{

	CreateRepositoryResult CustomerRepositoryManager::createCustomerRepositoryInMemory()
	{
		_CustomerRepository.reset(new CustomerRepositoryInMemory);
		return CreateRepositoryResult::eOk;

	}

	CustomerRepositoryBase* CustomerRepositoryManager::getCurrentCustomerRepository()
	{
		return _CustomerRepository.get();
	}

	CustomerRepositoryBase const* CustomerRepositoryManager::getCurrentCustomerRepository() const
	{
		return _CustomerRepository.get();
	}

	AddResult CustomerRepositoryManager::addCustomer(const CUSTOMER& aCustomer) const
	{
		if (_CustomerRepository)
			return _CustomerRepository->addCustomer(aCustomer);

		return AddResult::eNoRepositoryFound;
	}

	std::pair<GetResult, std::optional<std::reference_wrapper<CUSTOMER>>> CustomerRepositoryManager::getCustomerByID(const IDTYPE& id) const
	{
		if (_CustomerRepository)
			return _CustomerRepository->getCustomerByID(id);

		return std::make_pair(GetResult::eNoRepositoryFound,std::nullopt);
	}

	std::pair<GetResult, std::optional<std::reference_wrapper<std::vector<CUSTOMER>>>> CustomerRepositoryManager::getAllCustomers()
	{
		if (_CustomerRepository)
			return _CustomerRepository->getAllCustomers();

		return std::make_pair(GetResult::eNoRepositoryFound, std::nullopt);
	}

	std::pair<GetResult, std::optional<std::reference_wrapper<const std::vector<CUSTOMER>>>> CustomerRepositoryManager::getAllCustomers() const
	{
		if (_CustomerRepository)
			return _CustomerRepository->getAllCustomers();

		return std::make_pair(GetResult::eNoRepositoryFound, std::nullopt);
	}

	void CustomerRepositoryManager::setCustomerRepository(std::unique_ptr<CustomerRepositoryBase>&& customerRepository)
	{
		_CustomerRepository = std::move(customerRepository);
	}

}

