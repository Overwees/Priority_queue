#pragma once
#include <iostream>
#ifndef __queue_defined__
#define __queue_defined__
using namespace std;

constexpr auto START_LINE_PRIORITY = __LINE__;
enum class Priority {
	high = 1,
	medium,
	low
};
constexpr auto PRIORITY_COUNT = __LINE__ - START_LINE_PRIORITY - 3;
const string PRIORITY_NAMES[] = { "high", "medium", "low" };

typedef int InfoType;


class PQueue
{
private:
	struct QItem
	{
		InfoType info;
		Priority status;
		QItem* next;
		QItem(InfoType Ainfo,Priority astatus) : info(Ainfo),status(astatus), next(NULL) {}
	};
	QItem* front, * rear_high, * rear_medium, * rear_low;
	unsigned size;
	unsigned size_high;
	unsigned size_medium;
	unsigned size_low;

	void Erase();
	void Clone(const PQueue&);
	void move(QItem*&, QItem*&);
	void move(PQueue&& other);
public:

	PQueue() :front(NULL), rear_high(NULL), rear_medium(NULL), rear_low(NULL), size(0) {};
	PQueue(const PQueue&);
	PQueue(PQueue&&) noexcept; 

	~PQueue();

	PQueue& operator = (const PQueue&);
	PQueue& operator = (PQueue&&) noexcept;

	unsigned GetSize()const;
	unsigned GetHighSize()const;
	unsigned GetMediumSize()const;
	unsigned GetLowSize()const;
	bool IsEmpty() const;
	void Push(InfoType Ainfo,Priority astatus);
	bool pop();
	InfoType GetFirst()const;
	string GetFirstPriority()const;
	InfoType operator [](unsigned)const;	
};

#endif