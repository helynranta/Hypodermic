#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <memory>
#endif


namespace Hypodermic
{

    struct ActivationResult
    {
        ActivationResult()
            : activated(false)
        {
        }

        bool activated;
        std::shared_ptr< void > activatedInstance;
        std::shared_ptr< void > alignedInstance;
    };
    
} // namespace Hypodermic