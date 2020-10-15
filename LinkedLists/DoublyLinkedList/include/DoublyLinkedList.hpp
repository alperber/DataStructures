#ifndef DoublyLinkedList_HPP
#define DoublyLinkedList_HPP

#include "Iterator.hpp"

template <typename Object>
class DoublyLinkedList{
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
		DoublyLinkedList(){
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
			return OncekiniKonumuIleBul(size).getCurrent();
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
			if(newNext != NULL) newNext->geri = iterator.current->ileri;			
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
				if(eskiDugum->ileri != NULL) eskiDugum->ileri->geri = eskiDugum->geri;
				delete eskiDugum;
				size--;
			}
			else throw ElemanYok();
		}
		bool find(const Object& aranan) const{
			for(Iterator<Object> iterator(basDugum->ileri);!iterator.canMove();iterator.next()){
				if(iterator.current->eleman == aranan) return true;
			}
			return false;
		}
		int indexOf(const Object& aranan) const throw(ElemanYok){
			int index=0;
			for(Iterator<Object> iterator(basDugum->ileri);!iterator.canMove();iterator.next()){
				if(iterator.current->eleman == aranan) return index;
				index++;
			}
			throw ElemanYok();
		}
		friend ostream& operator<<(ostream& screen, DoublyLinkedList &right){
			if(right.isEmpty()) screen<<"Liste bos";
			else{
				for(Iterator<Object> iterator = right.FirstNode();!iterator.canMove();iterator.next())
					screen<<iterator.getCurrent()<<" ";
				screen<<endl;
			}
			return screen;
		}
		void printNodesFromPositionReverseOrder(int konum){
			for(Iterator<Object> iterator = OncekiniKonumuIleBul(konum+1);iterator.current != basDugum;iterator.prev())
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
		~DoublyLinkedList(){
			clear();
			delete basDugum;
		}
};
#endif