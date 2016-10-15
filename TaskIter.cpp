#include "DXUT.h"
#include "TaskIter.h"


TaskIter::TaskIter(TaskList* _list)
{
	list = _list;
	task = list->ActiveTask;
}

TaskIter::~TaskIter()
{
}

bool TaskIter::HasNext()
{
	return task->next != list->ActiveTask;
}

Task * TaskIter::Next()
{
	return task = task->next;
}

void TaskIter::Remove()
{
	task = task->prev;
	delete task->next;
}
