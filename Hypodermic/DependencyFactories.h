#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <unordered_map>
#endif

#include "Hypodermic/DependencyFactory.h"
#include "Hypodermic/TypeInfo.h"


namespace Hypodermic
{

    typedef std::unordered_map< TypeInfo, DependencyFactory > DependencyFactories;

} // namespace Hypodermic