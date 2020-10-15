#ifndef CircularDoublyLinkedList_HPP
#define CircularDoublyLinkedList_HPP

#include "Iterator.hpp"

template <typename Object>
class CircularDoublyLinkedList{
	private:
		Dugum<Object> *basDugum; // içinde eleman olmayan sadece listenin baþýný tutan düðüm.
		int size;
		
		Iterator<Object> OncekiniKonumuIleBul(int konum) const throw(Tasma){
			if(konum < 0 || konum > Count()) throw Tasma();
			int index=0;
			Iterator<Object> iterator(basDugum);
			
			while(!iterator.canMove() && konum != index++) iterator.next();
			return iterator;
		}		
		/// Listenin ilk düðümünü döndürür
		Iterator<Object> FirstNode() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return Iterator<Object>(basDugum->ileri);
		}
	public:
		CircularDoublyLinkedList(){
			basDugum = new Dugum<Object>(); // Boþ bir düðüm oluþturuluyor	
			size=0;
		}
		bool isEmpty() const{
			return basDugum->ileri == NULL;
		}
		int Count() const{
			return size;
		}
		/// Listenin ilk elemanýný döndürür
		const Object& first() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return basDugum->ileri->eleman;
		}
		/// Listenin son elemanýný döndürür
		const Object& last() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return basDugum->ileri->geri->eleman;
		}
		/// Listenin sonuna verilen elemaný ekler
		void add(const Object& yeni){
			insert(Count(),yeni);
		}
		/// Listenin istenen konumuna verilen elemaný ekler
		void insert(int konum,const Object& yeni) throw(Tasma){
			Iterator<Object> iterator;
			try{
				iterator = OncekiniKonumuIleBul(konum);
			}
			catch(Tasma ts){
				throw ts;
			}
			Dugum<Object> *newNext = iterator.current->ileri;
			iterator.current->ileri = new Dugum<Object>(yeni,newNext,iterator.current);
			if(newNext != NULL){
				Dugum<Object> *last = newNext->geri;
				newNext->geri = iterator.current->ileri;
				if(konum == 0) basDugum->ileri->geri = last;
			}
			if(size == 0) basDugum->ileri->ileri = basDugum->ileri->geri = basDugum->ileri;
			size++;			
		}
		/// Verilen elemaný listede bulur ve siler.
		void remove(const Object& aranan) throw(ElemanYok){
			try{
				int konum = indexOf(aranan);
				removeAt(konum);
			}
			catch(ElemanYok ey){
				throw ey;
			}
		}
		void removeAt(int konum) throw(Tasma){
			Iterator<Object> onceki;
			try{
				onceki = OncekiniKonumuIleBul(konum);
			}			
			catch(Tasma ts){
				throw ts;
			}
			if(onceki.current->ileri != NULL){
				Dugum<Object> *eskiDugum = onceki.current->ileri;
				// silinen elemaný es geç
				onceki.current->ileri = onceki.current->ileri->ileri;
				eskiDugum->ileri->geri = eskiDugum->geri;
				delete eskiDugum;
				if(konum == 0) basDugum->ileri->geri->ileri = basDugum->ileri;
				size--;
				if(size == 0) onceki.current->ileri = NULL;
			}
		}
		bool find(const Object& aranan) const{
			int index=0;
			for(Iterator<Object> iterator(basDugum->ileri);index<size;iterator.next()){
				if(iterator.current->eleman == aranan) return true;
			}
			return false;
		}
		int indexOf(const Object& aranan) const throw(ElemanYok){
			int index=0;
			for(Iterator<Object> iterator(basDugum->ileri);index<size;iterator.next()){
				if(iterator.current->eleman == aranan) return index;
				index++;
			}
			throw ElemanYok();
		}
		friend ostream& operator<<(ostream& screen, CircularDoublyLinkedList &right){
			if(right.isEmpty()) screen<<"Liste bos";
			else{
				int index=0;
				for(Iterator<Object> iterator = right.FirstNode();index<right.size;iterator.next(),index++)
					screen<<iterator.getCurrent()<<" ";
				screen<<endl;
			}
			return screen;
		}
		void printNodesFromPositionReverseOrder(int konum){
			int index=0;
			for(Iterator<Object> iterator = OncekiniKonumuIleBul(konum+1);index<size;iterator.prev(),index++)
				cout<<iterator.getCurrent()<<" ";
			cout<<endl;
		}
		void printReverseOrder(){
			printNodesFromPositionReverseOrder(size-1);
		}
		/// Listedeki elemanlarý temizler
		void clear(){
			while(!isEmpty())
				removeAt(0);			
		}
		~CircularDoublyLinkedList(){
			clear();
			delete basDugum;
		}
};
#endif