#include "PriorityQueue.h"
#include <exception>

void PQueue::Erase()
{
	while (Pop());
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
}

void PQueue::Clone(const PQueue& q)
{
	QItem* tmp = q.front;
	for(unsigned i=0;i<q.GetSize();i++)
	{
		Push(tmp->info,tmp->status);
		tmp = tmp->next;
	}
}

void PQueue::move(QItem*& a, QItem*& b)
{
	a = b;
	b = nullptr;
}

void PQueue::move(PQueue&& other)
{
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);

	for (int i = 0; i < 4; i++)
	{
		size[i] = other.size[i];
		other.size[i] = 0;
	}
}

PQueue::PQueue(const PQueue& other)
{
	for (int i = 0; i < 4; i++)
		size[i] = 0;
	Clone(other);
}

PQueue::PQueue(PQueue&& other) noexcept
{
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);

	for (int i = 0; i < 4; i++)
	{
		size[i] = other.size[i];
		other.size[i] = 0;
	}
}

PQueue& PQueue::operator=(const PQueue& other)
{
	if (&other != this)
	{
		Erase();
		Clone(other);
	}
	return (*this);
}

PQueue& PQueue::operator=(PQueue&& other) noexcept
{
	if (&other == this)
		return (*this);
	Erase();
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);
	for (int i = 0; i < 4; i++)
	{
		size[i] = other.size[i];
		other.size[i] = 0;
	}
	return *this;
}

PQueue::~PQueue()
{
	Erase();
}

unsigned PQueue::GetSize(Priority astatus) const
{
	switch(astatus)
	{
	case Priority(1):
		return size[0];

	case Priority(2):
		return size[1];

	case Priority(3):
		return size[2];
	}
}

unsigned PQueue::GetSize() const
{
	return size[3];
}

bool PQueue::IsEmpty() const
{
	return (size == 0);
}

void PQueue::Push(InfoType Ainfo,Priority astatus)
{
	if (int(astatus) < 1 || int(astatus) > PRIORITY_COUNT)
		throw exception("Error! Invalid priority input!");
	QItem* tmp1 = new QItem(Ainfo,astatus);
	if (astatus == Priority(1))// high
	{
		if (rear_medium != NULL || rear_low != NULL)//есть элементы с приоритетом ниже
		{
			if (rear_high != NULL)// есть high
			{
				QItem* tmp2 = rear_high->next;
				rear_high->next = tmp1;
				tmp1->next = tmp2;
			}
			else
			{
				QItem* tmp2 = front;
				front = tmp1;
				tmp1->next = tmp2;
			}

		}
		if(rear_medium == NULL && rear_low == NULL)// нет low и medium
		{
			if (size[3] > 0)
				rear_high->next = tmp1;
			else
				front = tmp1;
		}
		rear_high = tmp1;
		size[0]++;
	}
	if (astatus == Priority(2))// medium
	{
		if (rear_high != NULL && rear_low == NULL)// есть high нет low
			if(rear_medium != NULL)
				rear_medium->next = tmp1;
			else
				rear_high->next = tmp1;

		if (rear_high == NULL && rear_low == NULL)// нет high и low
			if (rear_medium != NULL)
				rear_medium->next = tmp1;
			else
					front = tmp1;

		if (rear_high == NULL && rear_low != NULL)// есть low нет high
		{
			if (rear_medium != NULL)
			{
				QItem* tmp2 = rear_medium->next;
				rear_medium->next = tmp1;
				tmp1->next = tmp2;
			}
			else
			{
				QItem* tmp2 = front;
				front = tmp1;
				tmp1->next = tmp2;
			}
		}
		if (rear_high != NULL && rear_low != NULL)//есть high и low
		{
			{
				if (rear_medium != NULL)
				{
					QItem* tmp2 = rear_medium->next;
					rear_medium->next = tmp1;
					tmp1->next = tmp2;
				}
				else
				{
					QItem* tmp2 = rear_high->next;
					rear_high->next = tmp1;
					tmp1->next = tmp2;
				}
			}
		}

		rear_medium = tmp1;
		size[1]++;
	}
	if (astatus == Priority(3))// low
	{
		if (rear_low != NULL)
			rear_low->next = tmp1;
		else
			if (size[3] == 0)
				front = tmp1;
			else
				if (rear_medium != NULL)
					rear_medium->next = tmp1;
				else
					rear_high->next = tmp1;
		rear_low = tmp1;
		size[2]++;
	}
	size[3]++;
}

bool PQueue::Pop()
{
	if (size[3] == 0)
		return false;
	QItem* tmp = front;
	Priority pr = front->status;
	front = front->next;

	delete tmp;
	size[3]--;
	switch (pr)
	{
	case Priority(1):
		size[0]--;
		if (size[0] == 0)
			rear_high = NULL;
		break;
	case Priority(2):
		size[1]--;
		if (size[1] == 0)
			rear_medium = NULL;
		break;
	case Priority(3):
		size[2]--;
		if (size[2] == 0)
			rear_low = NULL;
		break;
	}
	return true;
}

InfoType PQueue::GetFirstValue() const
{
	if (size[3] == 0)
		throw exception("Impossible to execute\GetFirstValue:queue is empty");
	return front->info;
}

Priority PQueue::GetFirstPriority() const
{
	if (size[3] == 0)
		throw exception("Impossible to execute\GetFirstPriority:queue is empty");
	return front->status;
}

InfoType PQueue::operator[](unsigned k) const
{

	if ((k < 0) || (k >= size[3]))
				throw exception("Impossible to execute\operator[]: invalid index");
			QItem* tmp = front;
			for (unsigned i = 0; i < k; i++)
			tmp = tmp->next;
			return tmp->info;
}

