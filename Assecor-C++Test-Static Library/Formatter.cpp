#include "Formatter.h"


namespace MyAssecorLibrary
{
	Formatter::Formatter(std::reference_wrapper<const CustomerRepositoryManager>&& customerRepositoryManager)
		:_CustomerRepositoryManager(std::move(customerRepositoryManager))
	{
	}


	std::pair<GetResult, std::string> Formatter::getCustomerByID(const IDTYPE& id) const
	{
		std::pair<GetResult, std::string> result;

		auto [requestResult, optCustomer] = _CustomerRepositoryManager.get().getCustomerByID(id);
		result.first = requestResult;

		if (requestResult == GetResult::eOk && optCustomer.has_value())
		{
			const auto& customer = optCustomer.value();
			result.second = formatOneCustomer(customer.get());
		}
		else
			result.second = std::string("(no customer)");

		return result;

	}

	std::pair<GetResult, std::vector<std::string>> Formatter::getAllCustomers() const
	{
		std::pair<GetResult, std::vector<std::string>> result;

		auto [requestResult, customers] = _CustomerRepositoryManager.get().getAllCustomers();
		result.first = requestResult;

		if (requestResult == GetResult::eOk && customers.has_value())
		{
			result.first = GetResult::eOk;
			for (const auto& costumer : customers.value().get())
				result.second.push_back( formatOneCustomer(costumer) );
		}

		return result;
	}

	std::string Formatter::formatOneCustomer(const CUSTOMER& aCustomer) const
	{
		std::string result;
		result = std::string(aCustomer.last_name) + ", ";
		result += std::string(aCustomer.first_name) + ", ";
		result += std::string(aCustomer.zip_code) + ", ";
		result += std::string(aCustomer.city) + ", ";
		result += "favorite color: ";
		result +=  std::to_string(aCustomer.favorite_color).c_str();

		return result;
	}

}