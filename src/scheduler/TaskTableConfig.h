#pragma once

#include "TaskSchedulerConfig.h"
#include "TaskTable.h"

namespace StupidLittle
{
    // periodic task timebase count period definitions
    constexpr TimebaseCount TaskPeriodTimebaseTicksExample1{ 10 };
    constexpr TimebaseCount TaskPeriodTimebaseTicksExample2{ 8 };
    // etc..

    // make sure to synchronise with task table definition in SLTaskTableConfig.cpp
    enum class TaskTableHandle
    {
        init = 0,
        periodic,
        count
    };

    TaskTable* getTaskTableByHandle(TaskTableHandle);
} // namespace