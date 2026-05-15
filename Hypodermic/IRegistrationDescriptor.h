#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <functional>
#include <memory>
#endif

#include <boost/signals2.hpp>


namespace Hypodermic
{

    class IRegistrationDescriptor;
    class IRegistrationRegistry;

    struct TypeInfo;


    class IRegistrationDescriptor
    {
    public:
        typedef boost::signals2::signal< void(const std::shared_ptr< IRegistrationDescriptor >&) > Updated;

    public:
        virtual ~IRegistrationDescriptor() = default;

        virtual Updated& registrationDescriptorUpdated() const = 0;

        virtual std::function< void(IRegistrationRegistry&) > getDescriptionFactory() const = 0;

        virtual const TypeInfo& instanceType() const = 0;
    };

} // namespace Hypodermic