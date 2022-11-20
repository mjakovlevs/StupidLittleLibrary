#pragma once

#include <iostream>

template <typename TData, typename TSize, TSize TCapacity>
class Container
{
public:
    Container() : capacity{ TCapacity }, data{}, count{ 0 }, overflow{ false }
    {
        std::cout << "Called Container()" << std::endl;
        static_assert(std::is_unsigned<TSize>::value, "Container<TData, TSize, TCapacity>: only unsigned integral types are allowed as TSize");
    }

    ~Container()
    {}

protected:
    const TSize capacity;
    TData data[TCapacity];
    TSize count;
    bool overflow;


};