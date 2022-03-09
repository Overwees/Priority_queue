#include "PriorityQueue.h"
#include <exception>

void PQueue::Erase()
{
	while (pop());
	size = 0;
	size_high = 0;
	size_medium = 0;
	size_low = 0;
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

	size = other.size;
	size_high = other.size_high;
	size_medium = other.size_medium;
	size_low = other.size_low;

	other.size_high = 0;
	other.size_medium = 0;
	other.size_low = 0;
	other.size = 0;
}

PQueue::PQueue(const PQueue& Q)
{
	size = 0;
	Clone(Q);
}

PQueue::PQueue(PQueue&& other) noexcept
{
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);

	size = other.size;
	size_high = other.size_high;
	size_medium = other.size_medium;
	size_low = other.size_low;

	other.size_high = 0;
	other.size_medium = 0;
	other.size_low = 0;
	other.size = 0;
}

PQueue& PQueue::operator=(const PQueue& Q)
{
	if (this != &Q)
	{
		Erase();
		Clone(Q);
	}
	return *this;
}

PQueue& PQueue::operator=(PQueue&& other) noexcept
{
	if (&other == this)
		return *this;
	Erase();
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);
	size = other.size;
	size_high = other.size_high;
	size_medium = other.size_medium;
	size_low = other.size_low;

	other.size_high = 0;
	other.size_medium = 0;
	other.size_low = 0;
	other.size = 0;
	return *this;
}

PQueue::~PQueue()
{
	Erase();
}

unsigned PQueue::GetSize() const
{
	return size;
}

unsigned PQueue::GetHighSize() const
{
	return size_high;
}

unsigned PQueue::GetMediumSize() const
{
	return size_medium;
}

unsigned PQueue::GetLowSize() const
{
	return size_low;
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
		if (rear_medium != NULL || rear_low != NULL)//åñòü ýëåìåíòû ñ ïðèîðèòåòîì íèæå
		{
			if (rear_high != NULL)// åñòü high
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
		if(rear_medium == NULL && rear_low == NULL)// íåò low è medium
		{
			if (size > 0)
				rear_high->next = tmp1;
			else
				front = tmp1;
		}
		rear_high = tmp1;
		size_high++;
	}
	if (astatus == Priority(2))// medium
	{
		if (rear_high != NULL && rear_low == NULL)// åñòü high íåò low
			if(rear_medium != NULL)
				rear_medium->next = tmp1;
			else
				rear_high->next = tmp1;

		if (rear_high == NULL && rear_low == NULL)// íåò high è low
			if (rear_medium != NULL)
				rear_medium->next = tmp1;
			else
					front = tmp1;

		if (rear_high == NULL && rear_low != NULL)// åñòü low íåò high
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
		if (rear_high != NULL && rear_low != NULL)//åñòü high è low
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
		size_medium++;
	}
	if (astatus == Priority(3))// low
	{
		if (rear_low != NULL)
			rear_low->next = tmp1;
		else
			if (size == 0)
				front = tmp1;
			else
				if (rear_medium != NULL)
					rear_medium->next = tmp1;
				else
					rear_high->next = tmp1;
		rear_low = tmp1;
		size_low++;
	}
	size++;
}

bool PQueue::pop()
{
		if (size == 0)
		return false;
	QItem* tmp = front;
	Priority pr = front->status;
	front = front->next;

	delete tmp;
	size--;
	switch (pr)
	{
	case Priority(1):
		size_high--;
		break;
	case Priority(2):
		size_medium--;
		break;
	case Priority(3):
		size_low--;
		break;
	}
	if (size_high == 0)
		rear_high = NULL;
	if (size_medium == 0)
		rear_medium = NULL;
	if (size_low == 0)
		rear_low = NULL;
	return true;
}

InfoType PQueue::GetFirst() const//åñëè óäàëèòü const è äîáàâèòü ñïåðåäè & ìîæíî èçìåíÿòü ïåðâûé ýëåìåíò
{
	if (size == 0)
		throw exception("Impossible to execute\GetFirst:queue is empty");
	return front->info;
}

string PQueue::GetFirstPriority() const
{
	return PRIORITY_NAMES[(int)front->status - 1];
}

InfoType PQueue::operator[](unsigned k) const
{

	if ((k < 0) || (k >= size))
				throw exception("Impossible to execute\operator[]: invalid index");
			QItem* tmp = front;
			for (unsigned i = 0; i < k; i++)
			tmp = tmp->next;
			return tmp->info;
}

