#pragma once
#include "Task.h"
#include "TaskList.h"

class Task;
class TaskList;

class TaskIter
{
public:
	TaskList* list;
	Task* task;

	TaskIter(TaskList* _list);
	~TaskIter();

	bool HasNext();
	Task* Next();
	void Remove();
};

