#include "DXUT.h"
#include "TaskList.h"

Task * TaskList::GetTask(size_t i)
{
	return (Task*)(Buffer + Task_Size*i);
}

TaskList::TaskList(size_t size, size_t count) : Task_Size(size), Task_Count(count)
{
	Buffer = new char[Task_Size*(Task_Count + 2)];
	ActiveTask = GetTask(0);
	ActiveTask->prev = ActiveTask;
	ActiveTask->next = ActiveTask;
	FreeTask = GetTask(1);
	for (size_t i = 1; i < Task_Count + 2; i++)
	{
		GetTask(i)->prev = NULL;
		GetTask(i)->next = GetTask(i + 1);
	}
	GetTask(Task_Count + 1)->next = FreeTask;
}


TaskList::~TaskList()
{
	SAFE_DELETE(Buffer);
}

void * TaskList::New(size_t size)
{
	assert(size <= Task_Size);
	if (FreeTask->next == FreeTask) return NULL;
	Task* task = FreeTask->next;
	FreeTask->next = task->next;
	return task;
}

void TaskList::Delete(void * p)
{
	Task* task = (Task*)p;
	assert(task->prev != NULL);
	task->prev = NULL;
	task->next = FreeTask->next;
	FreeTask->next = task;
}
