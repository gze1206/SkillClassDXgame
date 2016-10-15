#include "Task.h"
#include "TaskIter.h"
#pragma once

class Task;
class TaskIter;

class TaskList
{
	friend Task;
	friend TaskIter;

public:
	char* Buffer;
	Task* ActiveTask;
	Task* FreeTask;
	size_t Task_Size;
	size_t Task_Count;

	Task* GetTask(size_t i);

	TaskList(size_t size, size_t count);
	~TaskList();
	void* New(size_t size);
	void Delete(void* p);
};

