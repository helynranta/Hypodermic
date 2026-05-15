#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <memory>
#endif


namespace Hypodermic
{

    class IRegistration;

    
    class IRegistrationRegistry
    {
    public:
        virtual ~IRegistrationRegistry() = default;

        virtual void addRegistration(const std::shared_ptr< IRegistration >& registration) = 0;
        virtual void addRegistration(const TypeAliasKey& typeAliasKey, const std::shared_ptr< IRegistration >& registration) = 0;
    };

} // namespace Hypodermic