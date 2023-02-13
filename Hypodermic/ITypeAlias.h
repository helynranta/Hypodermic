#pragma once

#include <cstdint>
#include <string>

#include "Hypodermic/HypodermicExport.h"

namespace Hypodermic
{

    struct TypeInfo;


    class HYPODERMIC_EXPORT ITypeAlias
    {
    public:
        virtual ~ITypeAlias() = default;

        virtual bool operator==(const ITypeAlias& rhs) const = 0;
        
        virtual std::size_t hashCode() const = 0;

        virtual const TypeInfo& typeInfo() const = 0;

        virtual std::string toString() const = 0;
    };

} // namespace Hypodermic