#pragma once

#include <stdint.h>

namespace StupidLittle
{
    // storage type of timebaseCount. only unsigned integral type may be used.
    using TimebaseCount = uint32_t;
    // constants related to timebaseCount storage type (max, one):
    constexpr TimebaseCount timebase_count_max{ UINT32_MAX };
    constexpr TimebaseCount timebase_count_one{ static_cast<TimebaseCount>(1) };
    // taskExecutionQueue count storage type:
    using TaskExecutionQueueCount = uint8_t;
    // capacity constant of taskExecutionQueue
    constexpr TaskExecutionQueueCount task_execution_queue_capacity{ static_cast<TaskExecutionQueueCount>(8)};
} // namespace