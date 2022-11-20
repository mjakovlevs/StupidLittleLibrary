#pragma once

namespace StupidLittle
{
    enum class State : uint8_t
    {
        uninitialized = 0,
        stopping,
        stopped,
        starting,
        running,
        suspending,
        suspended,
        count
    };
}