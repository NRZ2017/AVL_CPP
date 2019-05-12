#include "AVL.h"


int main()
{
	AVL<int>* tree = new AVL<int>();
	while (true)
	{
		for (int i = 0; i < 100; i++)
		{
			tree->Insert(i);
		}
		for (int i = 0; i < 100; i++)
		{
			tree->Delete(i);
		}
	}
};
