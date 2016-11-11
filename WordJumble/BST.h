#pragma once



template<typename Type>
class BST
{
private:

	struct Node
	{
		Type data;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(const Type& v)
		{
			data = v;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* Root = nullptr;



public:
	//Default Constructor
	BST()
	{

	}

	//Destructor
	~BST()
	{

	}

	//Assignment
	BST& operator=(const BST& that)
	{
		if (this != &that)
		{
			clear();
			Root = preOrder(Root, that.Root);
		}
		return *this;
	}

	//Copy Constructor
	BST(const BST& that)
	{
		Root = nullptr;
		*this = that;
	}

	//Insert
	void insert(const Type& v)
	{

		if (Root == nullptr)
			Root = new Node(v);
		else
		{
			Node* current = Root;
			while (true)
			{
				if (v < current->data)
				{
					if (current->left != nullptr)
						current = current->left;
					else
					{
						current->left = new Node(v);
						return;
					}
				}
				else
				{
					if (current->right != nullptr)
						current = current->right;
					else
					{
						current->right = new Node(v);
						return;
					}
				}
			}
		}
	}

	//Find and Remove, if returns true, item was found and removed
	bool findAndRemove(const Type& v)
	{
		if (Root == nullptr)
			return false;

		Node* current = Root;
		Node* parent = nullptr;

		while (current != nullptr)
		{
			if (v < current->data)
			{
				if (current->left != nullptr)
				{
					parent = current;
					current = current->left;
				}
				else
					return false;
			}
			else if (v > current->data)
			{
				if (current->right != nullptr)
				{
					parent = current;
					current = current->right;
				}
				else
					return false;
			}
			else
			{
				//If Node is found and has no children
				if (current->left == nullptr && current->right == nullptr)
				{
					if (current != Root)
					{
						//parent pointer to current = nullptr, delete current
						//Possible answer
						if (parent->left == current)
							parent->left = nullptr;
						else
							parent->right = nullptr;
						delete current;
						return true;
					}
					else
					{
						delete current;
						Root = nullptr;
						return true;
					}
						
				}

				//If Node only has left child
				else if (current->left != nullptr && current->right == nullptr)
				{
					if (current == Root)
						Root = current->left;
					else
					{
						if (parent->left == current)
							parent->left = current->left;
						else
							parent->right = current->left;
					}
					delete current;
					return true;

				}
				//Node only has right child
				else if (current->left == nullptr && current->right != nullptr)
				{
					if (current == Root)
						Root = current->right;
					else
					{
						if (parent->left == current)
							parent->left = current->right;
						else
							parent->right = current->right;
					}


					delete current;
					return true;
				}
				//If Node has 2 children
				else
				{

					Node* min = current->right;
					Node* minPrev = current;
					while (min->left != nullptr)
					{
						minPrev = min;
						min = min->left;
					}
					if (min->right != nullptr)
						minPrev->left = min->right;
					else
						minPrev->left = nullptr;

					Type switchData = min->data;
					min->data = current->data;
					current->data = switchData;

					delete min;
					return true;
				}
			}
		}
		return false;
	}

	//Find
	bool find(const Type& v) const
	{
		Node* current = nullptr;

		current = Root;
		while (current != nullptr)
		{
			if (v < current->data)
			{
				if (current->left != nullptr)
					current = current->left;
				else
					return false;
			}
			else if (v > current->data)
			{
				if (current->right != nullptr)
					current = current->right;
				else
					return false;
			}
			else
				return true;
		}
		return false;
	}

	//Clear
	void clear()
	{
		if (Root != nullptr)
			deletePostOrder(Root);
		Root = nullptr;
	}

	//Print in Order
	void printInOrder() const
	{
		if (Root != nullptr)
		{
			print(Root);
			cout << '\n';
		}
	}

	Node* preOrder(Node* curr, Node* thatCurr)
	{
		if (thatCurr == nullptr)
			return nullptr;
		curr = new Node(thatCurr->data);
		curr->left = preOrder(curr->left, thatCurr->left);
		curr->right = preOrder(curr->right, thatCurr->right);
		return curr;
	}

	void deletePostOrder(const Node* curr)
	{
		if (curr != nullptr)
		{
			deletePostOrder(curr->left);
			deletePostOrder(curr->right);
			delete curr;
		}
	}

	void print(Node* curr) const
	{
		if (curr != nullptr)
		{
			print(curr->left);
			cout << curr->data << ' ';
			print(curr->right);
		}
	}

};