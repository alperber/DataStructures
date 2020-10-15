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
		Dugum<Object> *geri;
		Dugum(const Object& eleman=Object(),Dugum<Object> *ilr=NULL,Dugum<Object> *gr=NULL){
			this->eleman=eleman;
			ileri=ilr;
			geri=gr;
		}
};
#endif