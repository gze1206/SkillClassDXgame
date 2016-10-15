#include "DXUT.h"
#include "Task.h"


Task::Task(TaskList* list)
{
	prev = list->ActiveTask->prev;
	next = list->ActiveTask;
	prev->next = next->prev = this;
}


Task::~Task()
{
	prev->next = next;
	next->prev = prev;
}
