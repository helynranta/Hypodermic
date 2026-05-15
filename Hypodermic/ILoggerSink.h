#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <string>
#endif

#include "Hypodermic/LogLevel.h"


namespace Hypodermic
{

    class ILoggerSink
    {
    public:
        virtual ~ILoggerSink() = default;

        virtual void append(LogLevels::LogLevel level, const std::string& message) = 0;
    };

} // namespace Hypodermic