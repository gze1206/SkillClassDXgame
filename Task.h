#pragma once
#include "TaskIter.h"
#include "TaskList.h"

class Task
{
	friend TaskList;
	friend TaskIter;

public:
	Task *prev, *next;

	void* operator new(size_t t) { }
	void operator delete(void* p) { }

	Task(TaskList* list);
	~Task();
};

