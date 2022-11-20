#include "TaskScheduler.h"

StupidLittle::TaskScheduler::TaskScheduler() :
    timebaseCount{ 0 },
    state{ State::stopped },
    pTaskTable{ nullptr }
{}

StupidLittle::TaskScheduler::~TaskScheduler()
{}

void StupidLittle::TaskScheduler::process()
{
    if (State::running == state)
    {
        // check if task list is selected AND task list has any tasks
        if (pTaskTable != nullptr && pTaskTable->taskCount > 0)
        {
            Task* pTask{ nullptr };
            TimebaseCount elapsedTimebaseCountSinceLastExecution{};

            taskExecutionQueue.clear();

            for (uint8_t i{ 0 }; i < pTaskTable->taskCount; i++)
            {
                pTask = &pTaskTable->pTaskList[i];
                elapsedTimebaseCountSinceLastExecution = getElapsedTimebaseCountSince(pTask->lastExecutionTimebaseCount);
                pTask->overrun = elapsedTimebaseCountSinceLastExecution > pTask->periodTimebaseCount;

                if (pTask->overrun || (elapsedTimebaseCountSinceLastExecution == pTask->periodTimebaseCount))
                {
                    // enqueue current task for execution:
                    taskExecutionQueue.enqueue(pTask);
                }
            }

            pTask = nullptr;

            while (!taskExecutionQueue.isEmpty())
            {
                pTask = taskExecutionQueue.dequeue();

                // execute the periodic task function and update its last execution timebase count:
                pTask->pPeriodicTask();
                pTask->lastExecutionTimebaseCount = timebaseCount;
            }
        }
        else
        {
            // TODO: there is no valid task list selected, handle this condition
        }
    }
}

void StupidLittle::TaskScheduler::incrementTimebaseCount()
{
    if (++timebaseCount == 0)
    {
        // TODO: implement overflow condition processing
    }
    // timebaseCount++;
}

StupidLittle::TimebaseCount StupidLittle::TaskScheduler::getTimebaseCount()
{
    return timebaseCount;
}

void StupidLittle::TaskScheduler::start()
{
    if (state != State::stopping) state = State::running;
}

void StupidLittle::TaskScheduler::stop()
{
    if (state != State::stopping) state = State::stopping;
}

StupidLittle::State StupidLittle::TaskScheduler::getState()
{
    return state;
}

void StupidLittle::TaskScheduler::setTaskTable(TaskTable* pTaskTable)
{
    this->pTaskTable = pTaskTable;
}

StupidLittle::TimebaseCount StupidLittle::TaskScheduler::getElapsedTimebaseCountSince(StupidLittle::TimebaseCount referenceTimebaseCount)
{
    TimebaseCount elapsedTimebaseCount{ 0 };

    if (timebaseCount >= referenceTimebaseCount)
    {
        // timebaseCount overflow did not occur since referenceTimebaseCount,
        // calculate elapsedTimebaseCount normally:
        elapsedTimebaseCount = timebaseCount - referenceTimebaseCount;
    }
    else
    {
        // this case is an attempt to compensate for a possible timebaseCount variable overflow which is inevitable 
        // when the system is left to run for a long enough period of time.
        // this scenario consists of the following conditions:
        // 1) referenceTimebaseCount is recorded by reading and storing current timebaseCount;
        // 2) timebaseCount continues to increment, and overflows;
        // 3) timebaseCount becomes < referenceTimebaseCount, which is a condition
        // from which we may assume that timebaseCount has overflowed since reading it previously.

        // it seems that timebaseCount overflow has occured since the referenceTimebaseCount value was recorded.
        // only one overflow occurrence is accounted for in this way.
        // elapsed = max - ref + 1 + current, where:
        // i.e. for uint8_t count: max = 255, ref = 230, current = 12 =>
        // 255 - ref + 1 + current = elapsed =>
        // 255 - 230 + 1 + 12 = 26 + 12 = 38, etc.
        // (we are adding 1 above because in a uint8_t there are 256 values, not 255 due to count starting from 0
        elapsedTimebaseCount = (timebase_count_max - referenceTimebaseCount + timebase_count_one) + timebaseCount;
    }

    return elapsedTimebaseCount;
}