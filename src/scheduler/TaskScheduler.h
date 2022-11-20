#pragma once

#include <stdint.h>
#include "TaskSchedulerConfig.h"
#include "common/State.h"
#include "TaskTable.h"
#include "containers/Queue.hpp"

namespace StupidLittle
{
    class TaskScheduler
    {
    public:
        TaskScheduler();
        ~TaskScheduler();

        void process();
        void incrementTimebaseCount();
        TimebaseCount getTimebaseCount();

        void start();
        inline void stop();
        // void suspend();
        State getState();

        void setTaskTable(TaskTable* pTaskTable);

        TimebaseCount getElapsedTimebaseCountSince(TimebaseCount referenceTimebaseCount);

    private:
        TimebaseCount timebaseCount;
        State state;
        TaskTable* pTaskTable;
        Queue<Task*, TaskExecutionQueueCount, task_execution_queue_capacity> taskExecutionQueue;
    };
} // namespace