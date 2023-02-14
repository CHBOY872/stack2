#include <stdio.h>

class Queue;
class List {
	friend class Queue;
	struct item {
		int val;
		item *next;
	
		item(int _val) : val(_val) {}
	};

	item *first;

public:
	List();
	~List();

	void Push(int val);
	int Pop();	

private:
	bool HasElement() { return first; }
};

List::List() : first(0) {}
List::~List()
{
	while (first) {
		item *tmp = first->next;
		delete first;
		first = tmp;
	}
}

void List::Push(int val)
{
	item *tmp = new item(val);
	tmp->next = first;
	first = tmp;
}

int List::Pop()
{
	item *tmp = first->next;
	int res = first->val;
	delete first;
	first = tmp;
	return res;
}

class Queue {
	List *first;
	List *second;

public:
	Queue() : first(new List), second(new List) {}
	~Queue()
	{
		delete first;
		delete second;
	}

	void Put(int el);
	int Take();
};

void Queue::Put(int el)
{
	first->Push(el);
}

int Queue::Take()
{
	while (first->HasElement())
		second->Push(first->Pop());
	int res = second->Pop();
	while (second->HasElement())
		first->Push(second->Pop());
	return res;
}

int main()
{
	Queue q;
	q.Put(35);
	q.Put(363);
	q.Put(445);
	q.Put(33355);
	int res = q.Take();
	q.Put(6363);
	q.Put(110001);
	res = q.Take();
	return 0;
}
