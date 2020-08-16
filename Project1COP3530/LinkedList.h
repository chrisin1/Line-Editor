#pragma once
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::runtime_error;
using std::vector;

template <typename T>
class LinkedList
{
private:


public:
	struct Node
	{
		//a node has a data variable and a pointer to the next node and previous node
		T data;
		Node* next;
		Node* prev;
	};



	//behaviors
	void PrintForward() const;

	//accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	//insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	//removal
	unsigned int Remove(const T& data);
	bool RemoveHead();
	bool RemoveTail();
	bool RemoveAt(int index);
	void Clear();

	//operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs); //copy assignment

	//Constructors
	LinkedList();
	LinkedList(const LinkedList<T>& list); //copy constructor
	void setFromOther(const LinkedList<T>& other);

	//Destructor
	~LinkedList();


private:
	Node* head;
	Node* tail;
	unsigned int node_count;


};

//constructors

template <typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	node_count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	node_count = 0;
	setFromOther(list);
}


//operators

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	if (index >= node_count)
		throw runtime_error("Invalid Index");
	Node* ptr = this->head;
	for (unsigned int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return ptr->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	if (index >= node_count)
		throw runtime_error("Invalid Index");
	Node* ptr = this->head;
	for (unsigned int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return ptr->data;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	setFromOther(rhs);
	return *this;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	if (node_count != rhs.NodeCount()) //first check to see if lists are the same size
	{
		return false;
	}

	Node* thisPtr = head;
	Node const* otherPtr = rhs.Head();

	while (thisPtr != nullptr)
	{
		if (thisPtr->data != otherPtr->data)
		{
			return false;
		}
		else
		{
			thisPtr = thisPtr->next;
			otherPtr = otherPtr->next;
		}
	}

	return true;
}

template <typename T>
void LinkedList<T>::setFromOther(const LinkedList<T>& other)
{

	for (unsigned int i = 0; i < other.NodeCount(); i++)
	{
		AddTail(other.GetNode(i)->data);
	}

}

//accessors

template <typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return this->node_count;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	Node* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->data == value)
		{
			outData.push_back(ptr);
		}
		ptr = ptr->next;
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const  //const version
{

	Node* ptr = head;
	for (unsigned int i = 0; i < NodeCount(); i++)
	{
		if (ptr->data == data)
			return ptr;
		ptr = ptr->next;
	}

	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	Node* ptr = head;
	for (unsigned int i = 0; i < NodeCount(); i++)
	{
		if (ptr->data == data)
			return ptr;
		ptr = ptr->next;
	}

	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const  //const version
{
	if (index >= NodeCount())
		throw runtime_error("Invalid Index");

	Node* ptr = head;
	for (unsigned int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}

	return ptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	if (index >= NodeCount())
		throw runtime_error("Invalid Index");

	Node* ptr = head;
	for (unsigned int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}

	return ptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const //const version
{
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const  //const version
{
	return tail;
}

//insertion

template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
	if (node_count == 0) //if list is empty
	{
		//1. allocate space for new node and set head to it
		Node* newHead = new Node;
		this->head = newHead;
		this->tail = newHead;   //head and tail are same since list only has 1 element

		//set head's data to function input
		this->head->data = data;
		this->tail->data = data;

		//update next and prev
		this->head->next = nullptr;
		this->tail->prev = nullptr;
	}
	else if (node_count == 1)
	{
		Node* newHead = new Node;
		this->tail->prev = newHead; //give tail->prev a value (list now has 2 items, head and tail)
		Node* oldHead = this->head; //saves value of old head (before new head is added)
		this->head = newHead; // add mew jead
		this->head->next = oldHead;
		this->head->data = data;
	}
	else if (node_count > 1)
	{
		Node* newHead = new Node;
		Node* oldHead = this->head; //saves value of old head (before new head is added)
		oldHead->prev = newHead;
		this->head = newHead;
		this->head->next = oldHead;
		this->head->data = data;
	}

	this->head->prev = nullptr;
	this->tail->next = nullptr;
	this->node_count++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data)
{
	if (node_count == 0) //if list is empty
	{
		//1. allocate space for new node and set tail to it
		Node* newTail = new Node;
		this->head = newTail;
		this->tail = newTail;   //head and tail are same since list only has 1 element

		//set head's data to function input
		this->head->data = data;
		this->tail->data = data;

		//update next and prev
		this->head->next = nullptr;
		this->tail->prev = nullptr;
	}
	else if (node_count == 1)
	{
		Node* newTail = new Node;
		this->head->next = newTail; //give head->next a value (list now has 2 items, head and tail)
		Node* oldTail = this->tail; //saves value of old tail (before new tail is added)
		this->tail = newTail; // add new Tail
		this->tail->prev = oldTail;
		this->tail->data = data;
	}
	else if (node_count > 1)
	{
		Node* newTail = new Node;
		Node* oldTail = this->tail; //saves value of old tail (before new tail is added)
		oldTail->next = newTail;
		this->tail = newTail;
		this->tail->prev = oldTail;
		this->tail->data = data;
	}

	this->head->prev = nullptr;
	this->tail->next = nullptr;
	this->node_count++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) //given array of data, add all to beginning of linkedlist
{
	for (unsigned int i = count; i > 0; i--)
	{
		AddHead(data[i - 1]);
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) //given array of data, add all to end of linkedlist
{
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	Node* newNode = new Node;
	newNode->data = data;
	Node* ptr = head;

	while (ptr != node && ptr != nullptr)//iterate until it reaches node
	{
		ptr = ptr->next;
	}

	Node* next = ptr->next; //record old next
	ptr->next = newNode; //introduce new node into list
	next->prev = newNode;

	newNode->prev = ptr;  //settings for new node
	newNode->next = next;
	node_count++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	Node* newNode = new Node;
	newNode->data = data;

	Node* ptr = head;
	while (ptr != node && ptr != nullptr)//iterate until it reaches node
	{
		ptr = ptr->next;
	}

	Node* prev = ptr->prev; //record old prev
	ptr->prev = newNode; //introduce new node into list
	prev->next = newNode;

	newNode->next = ptr;
	newNode->prev = prev;
	node_count++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	if ((unsigned int)index > NodeCount())  //checks if index is out of bounds
		throw runtime_error("Invalid Index");

	if (index == NodeCount()) //check to see if index is at end of list
	{
		AddTail(data);
		return;
	}

	Node* ptr = this->head;

	for (unsigned int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	if (ptr == head) // if the current is the head 
	{
		AddHead(data);
	}
	else //if node is inserted into the middle of the linked list
	{
		Node* newNode = new Node;
		newNode->data = data;

		Node* prev = ptr->prev; //record previous

		newNode->next = ptr; //displace pointer    (newNode will be placed between the ptr and its previous)
		newNode->prev = prev;

		prev->next = newNode; //resets next of previous to newNode
		ptr->prev = newNode;  //resets prev of pointer to newNode
		this->node_count++; //update count
	}
}

//deletion

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int removeCount = 0;
	Node* ptr = this->head; //sets current to beginning of list

	while (ptr != nullptr)
	{
		Node* next = ptr->next;
		Node* prev = ptr->prev;
		if (ptr->data != data) //if it doesn't match the current node
		{
			//do nothing
		}
		else if (ptr == head) // if it matches the node and the current is the head 
		{
			RemoveHead();
			removeCount++;
		}
		else if (ptr == tail) //if it matches the node and the current is the tail
		{
			RemoveTail();
			removeCount++;
		}
		else //if matched node is in the middle of the linked list
		{

			next->prev = prev; //resets previous of next to the previous of the deleted
			prev->next = next; //resets the next of the previous of the deleted to the next of the deleted
			delete ptr;
			removeCount++;
			this->node_count--;
		}
		ptr = next;
	}

	if (this->node_count == 0)
	{
		head = nullptr;
		tail = nullptr;
	}

	return removeCount;
}

template <typename T>
bool LinkedList<T>::RemoveHead()
{
	if (!head)
		return false;
	Node* ptr = head->next;
	delete head;
	head = ptr;
	this->node_count--;
	if (this->node_count == 0)
	{
		tail = head;
	}
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail()
{
	if (!tail)
		return false;
	Node* ptr = tail->prev;
	delete tail;
	tail = ptr;
	if (tail)
		tail->next = nullptr;
	this->node_count--;
	if (this->node_count == 0)
	{
		head = tail;
	}
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveAt(int index)
{
	if ((unsigned int)index >= NodeCount())  //checks if index is out of bounds
		return false;
	Node* ptr = this->head;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}

	Node* next = ptr->next; //records next and previous
	Node* prev = ptr->prev;

	if (ptr == head) // if it matches the node and the current is the head 
	{
		RemoveHead();
	}
	else if (ptr == tail) //if it matches the node and the current is the tail
	{
		RemoveTail();
	}
	else //if matched node is in the middle of the linked list
	{
		next->prev = prev; //resets previous of next to the previous of the deleted
		prev->next = next; //resets the next of the previous of the deleted to the next of the deleted
		delete ptr;
		this->node_count--;
	}

	if (this->node_count == 0)
	{
		head = nullptr;
		tail = nullptr;
	}

	return true;
}

template <typename T>
void LinkedList<T>::Clear()
{
	Node* ptr = this->head; //sets current to beginning of list
	while (ptr != nullptr)
	{
		Node* next = ptr->next;   //saves address of next in list
		delete ptr; //delete current
		ptr = next; //next becomes new current

	}
	head = nullptr;
	tail = nullptr;
	this->node_count = 0;
}

//printing

template <typename T>
void LinkedList<T>::PrintForward() const
{
	Node* ptr = this->head;
	int count = 1;
	while (ptr != nullptr)
	{
		cout << count << " " << ptr->data << endl;
		ptr = ptr->next;
		count++;
	}
}

//destructor

template <typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}