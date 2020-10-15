// Þablon düðüm sýnýfý
#ifndef DUGUM_HPP
#define DUGUM_HPP

#include <iostream>
using namespace std;

template <typename Object>
class Dugum{
	public:	
		Object eleman;
		Dugum<Object> *ileri;
		Dugum(const Object& eleman=Object(),Dugum<Object> *ilr=NULL){
			this->eleman=eleman;
			ileri=ilr;
		}
};
#endif