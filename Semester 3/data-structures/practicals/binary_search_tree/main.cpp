/*
    Written by Anshul Verma
*/

#include <iostream>
#include "stack_ll.h"
#include "queue.h"
using namespace std;

template <typename T>
class BST
{
	class node
	{
	  public:
		node *left, *right;
		T data;
		node(T n)
		{
			this->data = n;
			this->left = this->right = nullptr;
		}
	};

  public:
	node *root;
	int leafs, nonLeafs;
	BST()
	{
		root = nullptr;
		leafs = 0;
		nonLeafs = 0;
	}

	void insert(T n)
	{
		node *newNode = new node(n);
		node *temp, *ptr = root;
		if (root == nullptr)
			root = newNode;
		else
		{
			while (ptr != nullptr)
			{
				temp = ptr;
				if (n >= ptr->data)
					ptr = ptr->right;
				else
					ptr = ptr->left;
			}
			if (n >= temp->data)
				temp->right = newNode;
			else
				temp->left = newNode;
		}
		cout << "Node<" << n << "> Inserted!" << endl;
	}

	void search(T n)
	{
		node *temp, *ptr = root;
		if (root == nullptr)
			cout << "Tree Empty!";
		else
		{
			int count = 0;
			while (ptr != nullptr)
			{
				if (n == ptr->data)
				{
					cout << "\nNode found at level: " << count;
					return;
				}
				else if (n > ptr->data)
					ptr = ptr->right;
				else
					ptr = ptr->left;
				++count;
			}
			cout << "\nNode not found in tree!";
		}
	}

	void recursive_inorder(node *ptr)
	{
		if (ptr == nullptr)
			return;
		else
		{
			recursive_inorder(ptr->left);
			cout << ptr->data << " ";
			recursive_inorder(ptr->right);
		}
	}
	void recursive_preorder(node *ptr)
	{
		if (ptr == nullptr)
			return;
		else
		{
			cout << ptr->data << " ";
			recursive_preorder(ptr->left);
			recursive_preorder(ptr->right);
		}
	}
	void recursive_postorder(node *ptr)
	{
		if (ptr == nullptr)
			return;
		else
		{
			recursive_postorder(ptr->left);
			recursive_postorder(ptr->right);
			cout << ptr->data << " ";
		}
	}

	node *get_root()
	{
		return this->root;
	}

	void iterative_inorder()
	{
		Stack<node *> stack;
		node *ptr = root;
		while (ptr != nullptr || !stack.isempty())
		{
			if (ptr != nullptr)
			{
				stack.push(ptr);
				ptr = ptr->left;
			}
			else
			{
				ptr = stack.pop();
				cout << ptr->data << " ";
				ptr = ptr->right;
			}
		}
	}
	void iterative_preorder()
	{
		Stack<node *> stack;
		node *ptr = root;
		while (ptr != nullptr || !stack.isempty())
		{
			if (ptr != nullptr)
			{
				cout << ptr->data << " ";
				stack.push(ptr);
				ptr = ptr->left;
			}
			else
			{
				ptr = stack.pop();
				ptr = ptr->right;
			}
		}
	}
	void iterative_postorder()
	{
		Stack<node *> stack;
		node *ptr = root;
		node *temp = root;
		while (ptr != nullptr)
		{
			for (; ptr->left != nullptr; ptr = ptr->left)
				stack.push(ptr);
			while (ptr != nullptr && (ptr->right == nullptr || ptr->right == temp))
			{
				temp = ptr;
				cout << ptr->data << " ";
				if (stack.isempty())
					return;
				ptr = stack.pop();
			}
			stack.push(ptr);
			ptr = ptr->right;
		}
	}

	int height()
	{
		return height_helper(root);
	}
	int height_helper(node *temp)
	{
		int hleft = 0;
		int hright = 0;
		if (temp != nullptr)
		{
			hleft = height_helper(temp->left);
			hright = height_helper(temp->right);
			if (hleft > hright)
				return hleft + 1;
			else
				return hright + 1;
		}
		return -1;
	}

	void BFS()
	{
		Queue<node *> q;
		node *ptr = root;
		if (ptr != nullptr)
		{
			q.enqueue(ptr);
			while (!q.isempty())
			{
				ptr = q.dequeue();
				cout << ptr->data << " ";
				if (ptr->left != nullptr)
					q.enqueue(ptr->left);
				if (ptr->right != nullptr)
					q.enqueue(ptr->right);
			}
		}
	}

	void printMirrorImage()
	{
		Queue<node *> q;
		node *ptr = root;
		if (ptr != nullptr)
		{
			q.enqueue(ptr);
			while (!q.isempty())
			{
				ptr = q.dequeue();
				cout << ptr->data << " ";
				if (ptr->right != nullptr)
					q.enqueue(ptr->right);
				if (ptr->left != nullptr)
					q.enqueue(ptr->left);
			}
		}
	}

	void count(node *temp)
	{
		if (temp != nullptr)
		{
			if (temp->left != nullptr || temp->right != nullptr)
				nonLeafs++;
			if (temp->left == nullptr && temp->right == nullptr)
				leafs++;
			count(temp->left);
			count(temp->right);
		}
	}
	void printCount()
	{
		count(this->root);
		cout << "\nNo. of leaf nodes: " << this->leafs;
		cout << "\nNo. of non-leaf nodes: " << this->nonLeafs;
		cout << "\nTotal no. of nodes: " << this->leafs + this->nonLeafs;
	}

	void del_copy(T el)
	{
		node *prev;
		node *ptr = root;
		while (ptr != nullptr)
		{
			if (ptr->data == el)
				break;
			prev = ptr;
			if (ptr->data < el)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}
		if (ptr != nullptr && ptr->data == el)
		{
			if (ptr == root)
				delc(root);
			else if (prev->left == ptr)
				delc(prev->left);
			else
				delc(prev->right);
		}
		else if (root != 0)
			cout << "\n\tKey " << el << " is not in the tree!";
		else
			cout << "\n\tTree is Empty!";
	}
	void delc(node *&temp)
	{
		node *prev, *tmp = temp;
		if (temp->right == NULL)
			temp = temp->left;
		else if (temp->left == NULL)
			temp = temp->right;
		else
		{
			tmp = temp->left;
			prev = temp;
			while (tmp->right != NULL)
			{
				prev = tmp;
				tmp = tmp->right;
			}
			temp->data = tmp->data;
			if (prev == temp)
				prev->left = tmp->left;
			else
				prev->right = tmp->left;
		}
		delete tmp;
	}

	void del_merge(T el)
	{
		node *prev;
		node *ptr = root;
		while (ptr != nullptr)
		{
			if (ptr->data == el)
				break;
			prev = ptr;
			if (ptr->data < el)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}
		if (ptr != nullptr && ptr->data == el)
		{
			if (ptr == root)
				delm(root);
			else if (prev->left == ptr)
				delm(prev->left);
			else
				delm(prev->right);
		}
		else if (root != 0)
			cout << "\n\tKey " << el << " is not in the tree!";
		else
			cout << "\n\tTree is Empty!";
	}
	void delm(node *&temp)
	{
		node *tmp = temp;
		if (temp != NULL)
		{
			if (temp->right == NULL)
				temp = temp->left;
			else if (temp->left == NULL)
				temp = temp->right;
			else
			{
				tmp = temp->left;
				while (tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				tmp->right = temp->right;
				tmp = temp;
				temp = temp->left;
			}
			delete tmp;
		}
	}

	void search_change()
	{
		int key, newKey;
		cout << "\nEnter the key to be searched: ";
		cin >> key;
		cout << "Enter the new key: ";
		cin >> newKey;
		node *ptr = root;
		if (ptr == nullptr)
			cout << "Tree Empty!";
		else
		{
			int flag = 0;
			while (ptr != nullptr)
			{
				if (key == ptr->data)
				{
					flag = 1;
					break;
				}
				else if (key > ptr->data)
					ptr = ptr->right;
				else
					ptr = ptr->left;
			}
			if (flag == 0)
				cout << "\nNode not found in tree!";
			else
			{
				del_copy(key);
				insert(newKey);
			}
		}
	}
};

int main()
{
	BST<int> bst;
	bst.insert(30);
	bst.insert(18);
	bst.insert(43);
	bst.insert(10);
	bst.insert(25);
	bst.insert(48);
	bst.insert(32);
	cout << "Inorder: ";
	bst.iterative_inorder(); //10 18 25 30 32 43 48
	cout << endl
		 << "Preorder: ";
	bst.iterative_preorder(); //30 18 10 25 43 32 48
	cout << endl
		 << "Postorder: ";
	bst.iterative_postorder(); //10 25 18 32 48 43
	bst.search(32);
	cout << endl
		 << "Height: " << bst.height();
	cout << endl
		 << "BFS: ";
	bst.BFS();
	cout << endl
		 << "Mirror Image: ";
	bst.printMirrorImage();
	bst.printCount();
	bst.del_merge(30);
	bst.iterative_inorder();
	bst.search_change();
	bst.iterative_inorder();
	return 0;
}