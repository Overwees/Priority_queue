#include <iostream>
#include "PriorityQueue.h"
using namespace std;
void swap_move(PQueue& queue_a, PQueue& queue_b)
{
	PQueue tmp (move(queue_a));
	queue_a = move(queue_b);
	queue_b = move(tmp);
}
void swap_copy(PQueue& queue_a, PQueue& queue_b)
{
	PQueue tmp(queue_a);
	queue_a = queue_b;
	queue_b = tmp;
}
void queue_size(PQueue& queue)
{
	int tmp;
	cout << "1. High\n";
	cout << "2. Medium\n";
	cout << "3. Low\n";
	cout << "Choose priority:";
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		cout<<queue.GetSize(Priority(1))<<endl;
		break;
	case 2:
		cout << queue.GetSize(Priority(2)) << endl;
		break;
	case 3:
		cout << queue.GetSize(Priority(3)) << endl;
		break;
	default:
		cerr << "Error! Invalid priority!" << endl;
		break;
	}
}
void push_element(PQueue& queue)
{
	int value;
	int tmp;
	cout << "Enter number:";
	cin >> value;
	cout << "\n1. High\n";
	cout << "2. Medium\n";
	cout << "3. Low\n";
	cout << "Choose priority:";
	cin >> tmp;
	system("Cls");
	Priority prior = Priority(tmp);
	try
	{
		queue.Push(value, prior);
	}
	catch (exception ex)
	{
		cerr << ex.what() << endl;
	}
}
int main()
{
	PQueue q_one;
	q_one.Push(1, Priority(1));//fillig
	q_one.Push(4,Priority(3));
	q_one.Push(2, Priority(2));
	q_one.Push(15, Priority(2));
	q_one.Push(2, Priority(3));
	q_one.Push(16, Priority(1));
	q_one.Push(7, Priority(3));
	q_one.Push(199, Priority(2));
	q_one.Push(11, Priority(3));
	PQueue q_two;
	q_two.Push(11, Priority(2));
	q_two.Push(89, Priority(2));
	q_two.Push(7, Priority(3));
	q_two.Push(3, Priority(1));
	q_two.Push(5, Priority(1));
	q_two.Push(35, Priority(1));
	int op;
	while (true)
	{
		cout << "1. Swap queue with move\n";
		cout << "2. Swap queue without move(copy and assignment)\n";
		cout << "3. Get size\n";
		cout << "4. Get size(specific priority)\n";
		cout << "5. Empty check\n";
		cout << "6. Push\n";
		cout << "7. Pop\n";
		cout << "8. Get First info and priority\n";
		cout << "9. Cout\n\n";
		cout << "0. Exit\n\n";
		cout << "Choose option:";
		cin >> op;
		system("Cls");
		if (op == 0)
			break;
		switch (op)
		{
		case 1:
			swap(q_one,q_two);
			break;
		case 2:
			swap_copy(q_one, q_two);
			break;
		case 3:
			cout << "First queue size - " << q_one.GetSize() << endl;
			cout << "Second queue size - " << q_two.GetSize() << endl;
			break;
		case 4:
			queue_size(q_one);
			break;
		case 5:
			if (q_one.IsEmpty() == 1)
				cout << "First queue is empty!" << endl;
			else
				cout << "First queue isn't empty!" << endl;
			break;
		case 6:
			push_element(q_one);
			break;
		case 7:
			q_one.Pop();
			break;
		case 8:
			if (q_one.GetSize() > 0)
			cout << "First element value - "  << q_one.GetFirstValue() << endl;
			if(q_two.GetSize()>0)
			cout << "First element value - " << q_two.GetFirstValue() << endl;
			break;
		case 9:
			if (q_one.GetSize() > 0)
			{
				cout<<"First queue"<<endl;
				for (int i = 0; i < q_one.GetSize(); i++)
					cout << q_one[i] << " ";
				cout << endl;
			}
			if (q_two.GetSize() > 0)
			{
				cout << "Second queue" << endl;
				for (int i = 0; i < q_two.GetSize(); i++)
					cout << q_two[i] << " ";
				cout << endl;
			}
			break;
		default:
			cerr << "Error! Incorrect option!\nTry again!\n";
			break;
		}
		system("pause");
		system("Cls");
	}
	return 0;
}
