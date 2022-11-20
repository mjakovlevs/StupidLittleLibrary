#include "TaskTableConfig.h"

#define NELEMS(a)	(sizeof(a) / sizeof(*a))

// ============================================================

static StupidLittle::Task initTaskList[]
{
    { nullptr, StupidLittle::TaskPeriodTimebaseTicksExample1, 0, 0, false },
    { nullptr, StupidLittle::TaskPeriodTimebaseTicksExample2, 0, 0, false }
};

static StupidLittle::Task periodicTaskList[]
{
    { nullptr, StupidLittle::TaskPeriodTimebaseTicksExample1, 0, 0, false },
    { nullptr, StupidLittle::TaskPeriodTimebaseTicksExample2, 0, 0, false }
};

// ============================================================

static StupidLittle::TaskTable taskTableList[]
{
    { initTaskList, NELEMS(initTaskList) },
    { periodicTaskList, NELEMS(periodicTaskList) }
};

// ============================================================

StupidLittle::TaskTable* StupidLittle::getTaskTableByHandle(StupidLittle::TaskTableHandle handle)
{
    return &taskTableList[static_cast<uint8_t>(handle)];
}