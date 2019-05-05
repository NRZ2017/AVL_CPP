#pragma once
#include "AVL_Node.h"

template <typename T>
class AVL
{
public:
	int Count;
	void Insert(T value);
	bool Delete(T value);

private:
	const int& count = Count;
	AVL_Node<T>* Root;
	void removeNode(AVL_Node<T>* node);
};

template <typename T>
void AVL<T>::Insert(T value)
{
	Count++;
	if (Root == nullptr)
	{
		Root = new AVL_Node<T>(value);
	}
	else
	{
		AVL_Node<T>* tempNode = Root;

		while (tempNode != nullptr)
		{
			if (value < tempNode->Data)
			{
				if (tempNode->LeftChild != nullptr)
				{
					tempNode = tempNode->LeftChild.get();
				}
				else
				{
					tempNode->LeftChild = std::make_unique<AVL_Node<T>>(value, tempNode);
					break;
				}
			}
			else if (value >= tempNode->Data)
			{
				if (tempNode->RightChild != nullptr)
				{
					tempNode->RightChild = std::make_unique<AVL_Node<T>>(value, tempNode);
					break;
				}
			}
		}
		//make a function to balance the tree
	}
}

template <typename T>
bool AVL<T>::Delete(T value)
{
	AVL_Node<T>* tempNode = Root;
	while (tempNode != nullptr)
	{
		if (value < tempNode->Data)
		{
			tempNode = tempNode->LeftChild.get();
		}
		else if (value > tempNode->Data)
		{
			tempNode = tempNode->RightChild.get();
		}
		else
		{
			//make a function to remove nodes
			//and a function to balance the tree
			Count--;
			return true;
		}
	}

	return false;
}

template <typename T>
void AVL<T>::removeNode(AVL_Node<T>* node)
{
	if (node->ChildCount == 0)
	{
		if (node->Parent->LeftChild.get() == node)
		{
			node->Parent->LeftChild = nullptr;
		}
		else
		{
			node->Parent->LeftChild = nullptr;
		}
	}
	else if (node->ChildCount == 1)
	{
		auto child = node->FirstChild.get();
		child->Parent = node->Parent;

	}
}