#include "CustomerRepositoryInMemory.h"

#include <algorithm>

namespace MyAssecorLibrary
{
    AddResult CustomerRepositoryInMemory::addCustomer(const CUSTOMER& aCustomer)
    {
        auto iter = findIteratorOfCustomerWithID(aCustomer.id);
        if (iter == _Customers.end())
        {
            _Customers.push_back(aCustomer);
            return AddResult::eOk;
        }
        else
            return AddResult::eDuplicatedID;
    }

    std::pair<GetResult, std::optional<std::reference_wrapper<CUSTOMER>>> CustomerRepositoryInMemory::getCustomerByID(const IDTYPE& id)
    {
        auto iterConst = findIteratorOfCustomerWithID(id);
        auto iter = _Customers.erase(iterConst, iterConst);
        if (iter != _Customers.end())
            return std::make_pair(GetResult::eOk, std::optional(std::ref(*iter) ));
        else
            return std::make_pair(GetResult::eIDNotFound, std::nullopt);
    }

    std::pair<GetResult, std::reference_wrapper<std::vector<CUSTOMER>>> CustomerRepositoryInMemory::getAllCustomers()
    {
        return std::make_pair<GetResult, std::reference_wrapper<std::vector<CUSTOMER>>>(GetResult::eOk, std::ref(_Customers));
    }

    std::vector<CUSTOMER>::const_iterator CustomerRepositoryInMemory::findIteratorOfCustomerWithID(const IDTYPE& id) const
    {
        auto iterFound = std::ranges::find_if(_Customers.begin(), _Customers.end(), [&id](const CUSTOMER& aCustomerTemp) {
            return id == aCustomerTemp.id;
            });

        return iterFound;
    }

}