#pragma once

#include <memory>
#include <math.h>

template <typename T>
class AVL_Node
{
public:
	T Data;
	std::unique_ptr<AVL_Node<T>> LeftChild;
	std::unique_ptr<AVL_Node<T>> RightChild;
	AVL_Node<T>* Parent;
	int Height;

	int ChildCount();
	std::unique_ptr<AVL_Node<T>>& FirstChild();
	int Balance();
	void UpdateHeight();

	AVL_Node(T data, std::unique_ptr<AVL_Node<T>> parent = nullptr)
	{
		Data = data;
		Parent = parent.get;
		Height = 1;
	}
private:

};

template <typename T>
int AVL_Node<T>::ChildCount()
{
	int childCount;
	if (LeftChild != nullptr)
	{
		childCount++;
	}
	if (RightChild != nullptr)
	{
		childCount++;
	}
	return childCount; 
}

template <typename T>
std::unique_ptr<AVL_Node<T>>& AVL_Node<T>::FirstChild()
{
	if (LeftChild != nullptr)
	{
		return LeftChild;
	}
	else
	{
		return RightChild;
	}
}

template <typename T>
int AVL_Node<T>::Balance()
{
	int right = 0;
	int left = 0;
	if (RightChild != nullptr)
	{
		right =  RightChild->Height;
	}
	else
	{
		right = 0;
	}
	if (RightChild != nullptr)
	{
		left = LeftChild->Height;
	}
	else
	{
		left = 0;
	}
	return right - left;
}

template <typename T>
void AVL_Node<T>::UpdateHeight()
{
	int right = 0;
	int left = 0;
	if (RightChild != nullptr)
	{
		right = RightChild->Height;
	}
	else
	{
		right = 0;
	}
	if (RightChild != nullptr)
	{
		left = LeftChild->Height;
	}
	else
	{
		left = 0;
	}
	Height = fmax(left, right) + 1;
}