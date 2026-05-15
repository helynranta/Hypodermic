#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <iostream>
#endif

#include "Hypodermic/ILoggerSink.h"


namespace Hypodermic
{

    class ConsoleLoggerSink : public ILoggerSink
    {
    public:
        void append(LogLevels::LogLevel logLevel, const std::string& message) override
        {
            if (logLevel == LogLevels::Off)
                return;

            (logLevel == LogLevels::Error ? std::cerr : std::cout) << toString(logLevel) << " || " <<  message << std::endl;
        }
    };

} // namespace Hypodermic