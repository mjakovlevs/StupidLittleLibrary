#pragma once

#include "TaskSchedulerConfig.h"

namespace StupidLittle
{
    struct Task
    {
        void(* const pPeriodicTask)() { nullptr };
        const TimebaseCount periodTimebaseCount{};
        TimebaseCount lastExecutionTimebaseCount{};
        const uint8_t priority{};
        bool overrun{ false };
    };

    struct TaskTable
    {
        Task* const pTaskList{ nullptr };
        const uint8_t taskCount{};
    };
} // namespace