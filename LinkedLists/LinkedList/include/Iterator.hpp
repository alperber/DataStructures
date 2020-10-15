#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Hatalar.hpp"
#include "Dugum.hpp"

template <typename Object>
class Iterator{
	public:
		Dugum<Object> *current; // Listede o anki bulunan konumu ifade eder.
		Iterator(){  // Yapýcý metot
			current=NULL;
		}
		Iterator(Dugum<Object> *dugum){  // Yapýcý metot
			current=dugum;
		}
		bool hasNext(){
			return current == NULL;
		}
		void next() throw(ListeSonu){
			if(hasNext()) throw ListeSonu();
			current = current->ileri;
		}
		const Object& getCurrent()const{
			return current->eleman;
		}
};
#endif