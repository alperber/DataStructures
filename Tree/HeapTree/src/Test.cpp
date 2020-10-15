#include "HeapTree.hpp"
#inlude <cstdlib>
int main()
{
	HeapTree *heap = new HeapTree(30);
	int *dizi = new int [25];
	cout<<"Dizi Sırasız Hali..:"<<endl;
	for(int i=0;i<25;i++)
	{
		dizi[i] = rand()%100+1;
		heap->add(dizi[i]);
		cout<<dizi[i]<<" ";
	}
	int index = 0;
	while(!heap->isEmpty())
	{
		dizi[index] = heap->removeMaxItem();
		index++;
	}
	cout<<endl;
	cout<<"Dizi Sıralı Hali.."<<endl;
	for(int i=0;i<25;i++)
	{
		cout<<dizi[i]<<" ";
	}
	cout<<endl;
	delete [] dizi;
	delete heap;
	return 0;
}