#pragma once
#include "CustomerRepositoryBase.h"

namespace MyAssecorLibrary
{
    class CustomerRepositoryInMemory : public CustomerRepositoryBase
    {
        friend class CustomerRepositoryManager;
    protected:
        CustomerRepositoryInMemory() = default;
    public:
        CustomerRepositoryInMemory(CustomerRepositoryInMemory& rhs) = delete;
        CustomerRepositoryInMemory(CustomerRepositoryInMemory&& rhs) = delete;
        ~CustomerRepositoryInMemory() override = default;

        AddResult addCustomer(const CUSTOMER& aCustomer) override;
        std::pair<GetResult, std::optional<std::reference_wrapper<CUSTOMER>>> getCustomerByID(const IDTYPE& id) override;
        std::pair<GetResult, std::reference_wrapper<std::vector<CUSTOMER>>> getAllCustomers() override;

    private:
        std::vector<CUSTOMER>::const_iterator findIteratorOfCustomerWithID(const IDTYPE& id) const;

    private:
        // or usage of std::map<IDTYPE, CUSTOMER>
        std::vector<CUSTOMER>       _Customers;
    };
}