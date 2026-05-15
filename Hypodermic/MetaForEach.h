#pragma once

#ifndef HYPODERMIC_USE_STD_MODULE
#include <utility>
#endif


namespace Hypodermic
{

    namespace Details
    {

        template <int N, class TSequence, class TCallable>
        struct ForEach;

        template <class TSequence, class TCallable>
        struct ForEach< 0, TSequence, TCallable >
        {
            explicit ForEach(TCallable&&)
            {
            }
        };

        template <int N, template <class...> class TSequence, class TValue, class... TValues, class TCallable>
        struct ForEach< N, TSequence< TValue, TValues... >, TCallable >
        {
            explicit ForEach(TCallable&& func)
            {
                func(TValue());

                ForEach< N - 1, TSequence< TValues... >, TCallable > invoke(std::forward< TCallable >(func));
            }
        };
        
    } // namespace Details


    template <class TSequence, class TCallable>
    void metaForEach(TCallable&& func)
    {
        Details::ForEach< TSequence::count, TSequence, TCallable > invoke(std::forward< TCallable >(func));
    }
    
} // namespace Hypodermic