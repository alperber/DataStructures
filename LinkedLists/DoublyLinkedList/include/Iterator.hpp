#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Hatalar.hpp"
#include "Dugum.hpp"

template <typename Object>
class Iterator{
	public:
		Dugum<Object> *current; // Listede o anki bulunan konumu ifade eder.
		Iterator(){  // Yap�c� metot
			current=NULL;
		}
		Iterator(Dugum<Object> *dugum){  // Yap�c� metot
			current=dugum;
		}
		bool canMove(){
			return current == NULL;
		}
		void next() throw(ListeSonu){
			if(canMove()) throw ListeSonu();
			current = current->ileri;
		}
		void prev()throw(ListeSonu){
			if(canMove()) throw ListeSonu();
			current = current->geri;
		}
		const Object& getCurrent()const{
			return current->eleman;
		}
};
#endif