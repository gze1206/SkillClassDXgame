#include "DXUT.h"
#include "Object.h"


Object::Object(TaskList* list) : mPosition(0.f, 0.f, 0.f), mWorldTM(), Task(list)
{
}


Object::~Object()
{
}

bool Object::IsHit(Object* obj)
{
	RECT a = GetRect(), b = obj->GetRect();
	return (a.left <= b.right && a.right >= b.left && a.top <= b.bottom && a.bottom >= b.top);
}

bool Object::IsHit(TaskList * list)
{
	for (TaskIter i(list); i.HasNext(); )
	{
		Object* obj = static_cast<Object*>(i.Next());
		if (IsHit(obj)) return true;
	}

	return false;
}
