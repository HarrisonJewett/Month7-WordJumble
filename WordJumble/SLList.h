#pragma once


template <typename Type> class SLLIter;

template <typename Type>
class SLList
{
	friend class SLLIter<Type>;
private:

	unsigned int Size;

	struct Node
	{
		Type data;
		Node* next;
	};

	Node* head;

	void copyHelper(Node* p)
	{
		if (p == nullptr)
			return;
		copyHelper(p->next);
		addHead(p->data);
	}

public:
	//Constructs an empty list
	SLList() { head = nullptr; Size = 0; }

	//Destroys the list
	~SLList() { clear(); }

	//Assignmet Operator
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		//if (that.head != nullptr)
		//{
		//	if (this != &that)
		//	{
		//		clear();
		//		Node* temp;
		//		Node* temp2;
		//		head = new Node;
		//		head->data = that.head->data;
		//		head->next = nullptr;
		//		temp = head;
		//		temp2 = that.head->next;
		//		while (temp2 != nullptr)
		//		{
		//			temp->next = new Node;
		//			temp->next->data = temp2->data;
		//			temp = temp->next;
		//			temp->next = nullptr;
		//			temp2 = temp2->next;
		//		}
		//	}
		//	//head = that.head;
		//	Size = that.Size;
		//}
		if (this != &that)
		{
			clear();
			copyHelper(that.head);
		}
		return *this;
	}

	//Copy Constructor
	SLList(const SLList<Type>& that)
	{
		/*Node* temp;
		Node* temp2;
		head = new Node;
		head->data = that.head->data;
		temp = head;
		temp2 = that.head->next;
		Size = 1;
		while (temp2 != nullptr)
		{
			temp->next = new Node;
			temp->next->data = temp2->data;
			temp = temp->next;
			temp->next = nullptr;
			temp2 = temp2->next;
			Size++;
		}*/
		head = nullptr;
		*this = that;
	}

	//Add a head(v)
	void addHead(const Type& v)
	{
		if (head == nullptr)
		{
			head = new Node;
			head->data = v;
			head->next = nullptr;
			Size++;
		}
		else
		{
			Node* temp = new Node;
			temp->data = v;
			temp->next = head;
			head = temp;
			Size++;
		}
	}

	//Clear the list, freeing of any dynamic memory
	void clear()
	{
		while (head != nullptr)
		{

			Node* temp = head;
			head = head->next;
			delete temp;

		}
		head = nullptr;
		Size = 0;
	}

	//Insert (v) into index (index)
	void insert(SLLIter<Type>& index, const Type& v)
	{
		if (index.iter != nullptr)
		{
			Node* insNode = new Node;
			insNode->data = v;

			if (index.iter == head)
			{
				insNode->next = head;
				head = insNode;
				index.iter = head;
			}
			else
			{
				index.prev->next = insNode;
				insNode->next = index.iter;
				index.iter = insNode;
			}
			Size++;
		}
	}

	//Remove index (index), do nothing on bad index
	void remove(SLLIter<Type>& index)
	{
		if (head == nullptr)
		{
		}
		else if (head == index.iter)
		{
			Node* removeNode;

			removeNode = head;
			head = head->next;
			delete removeNode;
			index.iter = head;
			Size--;
		}
		else
		{
			index.prev->next = index.iter->next;
			delete index.iter;
			//index.iter = nullptr;
			Size--;
			index.iter = index.prev->next;
		}
	}

	//Size, return the number of items stored
	inline unsigned int size() const { return Size; }
};

template <typename Type>
class SLLIter
{
	friend class SLList<Type>;
private:
	typename SLList<Type>::Node * iter;
	typename SLList<Type>::Node * prev;
	SLList<Type>* listToStore;
public:

	//Default constructor
	SLLIter(SLList<Type>& listToIterate) { listToStore = &listToIterate; }

	//move the iterator to the head
	void begin()
	{
		iter = listToStore->head;
		prev = nullptr;
	}

	//returns true if at end, else return false
	bool end() const
	{
		if (iter == nullptr)
			return true;
		else
			return false;
	}

	//Move iter forward one node
	SLLIter<Type>& operator++()
	{
		prev = iter;
		if (iter == nullptr)
		{
		}
		else if (iter->next == nullptr)
			iter = nullptr;
		else
			iter = iter->next;
		return *this;
	}

	//Return the item at the current iter location
	Type& current() const { return iter->data; }
};