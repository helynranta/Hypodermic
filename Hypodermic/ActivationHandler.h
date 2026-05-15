#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <functional>
#include <memory>
#endif


namespace Hypodermic
{

    class ComponentContext;

    typedef std::function< void(ComponentContext&, const std::shared_ptr< void >&) > ActivationHandler;

} // namespace Hypodermic