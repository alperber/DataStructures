#include "HeapTree.hpp"			
			
		HeapTree::HeapTree(int capacity)
		{
			items = new int[capacity];
			this->capacity = capacity;
			lenght = 0;
		}
		bool HeapTree::isEmpty()const
		{
			return lenght == 0;
		}
		void HeapTree::add(int number)
		{
			if(lenght == capacity) throw "Dizi Tasması";
			items[lenght] = number;
			lenght++;
			HeapfyUp(lenght-1);
		}
		int HeapTree::removeMaxItem()
		{
			if(isEmpty()) throw "Agac Bos";
			int max = items[0];
			items[0] = items[lenght-1];
			lenght--;
			if(lenght>0) HeapfyDown(0);
			return max;
		}
		HeapTree::~HeapTree()
		{
			delete [] items;
		}
		int HeapTree::ParentIndex(int nodeIndex)
		{
			return (nodeIndex-1)/2;
		}
		int HeapTree::LeftIndex(int nodeIndex)
		{
			return (2*nodeIndex)+1;
		}
		int HeapTree::RightIndex(int nodeIndex)
		{
			return (2*nodeIndex) +2;
		}
		void HeapTree::HeapfyUp(int nodeIndex)
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
		
		void HeapTree::HeapfyDown(int nodeIndex)
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
		