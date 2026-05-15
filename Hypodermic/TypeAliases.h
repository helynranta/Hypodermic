#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <functional>
#include <memory>
#include <unordered_map>
#endif

#include "Hypodermic/TypeAliasKey.h"


namespace Hypodermic
{

    typedef std::unordered_map< TypeAliasKey, std::function< std::shared_ptr< void >(const std::shared_ptr< void >&) > > TypeAliases;

} // namespace Hypodermic