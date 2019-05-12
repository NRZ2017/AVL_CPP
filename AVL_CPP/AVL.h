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
	//AVL_Node<T>* Root;
	std::unique_ptr<AVL_Node<T>> Root;
	void removeNode(AVL_Node<T>* node);
	void Balance(AVL_Node<T>* node);
	void RotateLeft(AVL_Node<T>* node);
	void RotateRight(AVL_Node<T>* node);
};

template <typename T>
void AVL<T>::Insert(T value)
{
	Count++;
	if (Root == nullptr)
	{
		Root = std::make_unique<AVL_Node<T>>(value);//new AVL_Node<T>(value);
	}
	else
	{
		AVL_Node<T>* tempNode = Root.get();

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
					tempNode->LeftChild = std::make_unique<AVL_Node<T>>(value);
					break;
				}
			}
			else if (value >= tempNode->Data)
			{
				if (tempNode->RightChild != nullptr)
				{
					tempNode->RightChild = std::make_unique<AVL_Node<T>>(value);
					break;
				}
			}
		}
		Balance(tempNode);
	}
}

template <typename T>
bool AVL<T>::Delete(T value)
{
	AVL_Node<T>* tempNode = Root.get();
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
			removeNode(tempNode);
			Balance(tempNode->Parent);
			Count--;
			return true;
		}
	}

	return false;
}

template <typename T>
void AVL<T>::removeNode(AVL_Node<T>* node)
{
	if (node->ChildCount() == 0)
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
	else if (node->ChildCount() == 1)
	{
		AVL_Node<T>* child = node->FirstChild.get();
		node->Parent = child->Parent;
		if (node->Parent->LeftChild.get() == node)
		{
			node->Parent->LeftChild->Data = std::move(child)->Data;
		}
		else
		{
			node->Parent->RightChild->Data = std::move(child)->Data;
		}
	}
	else if(node->ChildCount() == 2)
	{
		auto primeNode = node->LeftChild.get();
		while (primeNode->RightChild != nullptr)
		{
			primeNode = primeNode->RightChild.get();
		}
		node->Data = primeNode->Data;
		removeNode(primeNode);
	}
}

template <typename T>
void AVL<T>::Balance(AVL_Node<T>* node)
{
	if (node == nullptr)
	{
		node->UpdateHeight();
	}
	if (node->Balance() > 1)
	{
		RotateLeft(std::make_unique<AVL_Node<T>>(node));
		if (node->Balance() > 2)
		{
			RotateRight(node);
		}
	}
	if (node->Balance() < -1)
	{
		RotateRight(node);
		if (node->Balance() < -2)
		{
			RotateLeft(std::make_unique<AVL_Node<T>>(node));
		}
	}
	if (node->Parent != nullptr)
	{
		Balance(node->Parent);
	}
}



template <typename T>
void AVL<T>::RotateLeft(std::unique_ptr<AVL_Node<T>> node)
{
	auto parent = node->Parent;
	auto child = node->LeftChild.get();
	auto last = node->RightChild.get();

	child->LeftChild = std::move(node);
	child->Parent = parent;
	
	node->Parent = child;
	node->RightChild.get() == last;

	if (last != nullptr)
	{
		last->Parent = node.get();
	}
	if (parent != nullptr)
	{
		if (parent->LeftChild.get() == node.get())
		{
			parent->LeftChild.get() == child;
		}
		else if (parent->RightChild.get() == node.get())
		{
			parent->RightChild.get() == child;
		}
	}
	node->UpdateHeight();
	child->UpdateHeight();
}

template <typename T>
void AVL<T>::RotateRight(AVL_Node<T>* node)
{
	auto parent = node->Parent;
	auto child = node->RightChild.get();
	auto last = node->LeftChild.get();

	child->RightChild.get() == node;
	child->Parent = last;

	node->Parent = child;
	node->LeftChild.get() == last;

	if (last != nullptr)
	{
		last->Parent = node;
	}
	if (parent != nullptr)
	{
		if (parent->RightChild.get() == node)
		{
			parent->RightChild.get() == child;
		}
		if (parent->LeftChild.get() == node)
		{
			parent->LeftChild.get() == child;
		}
	}
	node->UpdateHeight();
	child->UpdateHeight();
}

