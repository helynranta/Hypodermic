#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <functional>
#include <memory>
#endif


namespace Hypodermic
{

    class IRegistration;
    class IResolutionContext;

    typedef std::function< std::shared_ptr< void >(const IRegistration&, IResolutionContext&) > InstanceFactory;

} // namespace Hypodermic