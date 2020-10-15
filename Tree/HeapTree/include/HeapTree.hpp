#ifndef HEAPTREE_HPP
#define HEAPTREE_HPP

#include <iostream>
using namespace std;

class HeapTree
{
	private:
		int *items;
		int lenght;
		int capacity;
		int ParentIndex(int nodeIndex)
		{
			return (nodeIndex-1)/2;
		}
		int LeftIndex(int nodeIndex)
		{
			return (2*nodeIndex)+1;
		}
		int RightIndex(int nodeIndex)
		{
			return (2*nodeIndex) +2;
		}
		void HeapfyUp(int nodeIndex)
		{
			int parentIndex,tmp;
			if(nodeIndex != 0)
			{
				parentIndex = ParentIndex(nodeIndex);
				if(items[parentIndex] < items[nodeIndex])
				{
					tmp = items[parentIndex];
					items[parentIndex] = items[nodeIndex];
					items[nodeIndex] = tmp;
					HeapfyUp(parentIndex);
				}
			}
		}
		
		void HeapfyDown(int nodeIndex)
		{
			int leftNodeIndex,rightNodeIndex,maxIndex,tmp;
			leftNodeIndex = LeftIndex(nodeIndex);
			rightNodeIndex = RightIndex(nodeIndex);
			if(rightNodeIndex >= lenght)
			{
				if(leftNodeIndex >= lenght) return;
				else 
					maxIndex = leftNodeIndex;
			}
			else 
			{
				if(items[rightNodeIndex] >= items[leftNodeIndex]) maxIndex = rightNodeIndex;
				else
					maxIndex = leftNodeIndex;
			}
			if(items[nodeIndex] < items[maxIndex]){
				tmp = items[maxIndex];
				items[maxIndex] = items[nodeIndex];
				items[nodeIndex] = tmp;
				HeapfyDown(maxIndex);
			}
		}
	public:
		HeapTree(int capacity)
		{
			items = new int[capacity];
			this->capacity = capacity;
			lenght = 0;
		}
		bool isEmpty()const
		{
			return lenght == 0;
		}
		void add(int number)
		{
			if(lenght == capacity) throw "Dizi Tasması";
			items[lenght] = number;
			lenght++;
			HeapfyUp(lenght-1);
		}
		int removeMaxItem()
		{
			if(isEmpty()) throw "Agac Bos";
			int max = items[0];
			items[0] = items[lenght-1];
			lenght--;
			if(lenght>0) HeapfyDown(0);
			return max;
		}
		~HeapTree()
		{
			delete [] items;
		}
};

#endif