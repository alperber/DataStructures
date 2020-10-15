#ifndef LinkedList_HPP
#define LinkedList_HPP

#include "Iterator.hpp"

template <typename Object>
class LinkedList{
	private:
		Dugum<Object> *basDugum; // i�inde eleman olmayan sadece listenin ba��n� tutan d���m.
		int size;
		
		Iterator<Object> OncekiniKonumuIleBul(int konum) const throw(Tasma){
			if(konum < 0 || konum > Count()) throw Tasma();
			int index=0;
			Iterator<Object> iterator(basDugum);
			
			while(!iterator.hasNext() && konum != index++) iterator.next();
			return iterator;
		}		
		/// Listenin ilk d���m�n� d�nd�r�r
		Iterator<Object> FirstNode() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return Iterator<Object>(basDugum->ileri);
		}
	public:
		LinkedList(){
			basDugum = new Dugum<Object>(); // Bo� bir d���m olu�turuluyor	
			size=0;
		}
		bool isEmpty() const{
			return basDugum->ileri == NULL;
		}
		int Count() const{
			return size;
		}
		/// Listenin ilk eleman�n� d�nd�r�r
		const Object& first() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return basDugum->ileri->eleman;
		}
		/// Listenin son eleman�n� d�nd�r�r
		const Object& last() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return OncekiniKonumuIleBul(size).getCurrent();
		}
		/// Listenin sonuna verilen eleman� ekler
		void add(const Object& yeni){
			insert(Count(),yeni);
		}
		/// Listenin istenen konumuna verilen eleman� ekler
		void insert(int konum,const Object& yeni) throw(Tasma){
			Iterator<Object> iterator;
			try{
				iterator = OncekiniKonumuIleBul(konum);
			}
			catch(Tasma ts){
				throw ts;
			}
			iterator.current->ileri = new Dugum<Object>(yeni,iterator.current->ileri);
			size++;
		}
		/// Verilen eleman� listede bulur ve siler.
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
				// silinen eleman� es ge�
				onceki.current->ileri = onceki.current->ileri->ileri;
				delete eskiDugum;
				size--;
			}
		}
		bool find(const Object& aranan) const{
			for(Iterator<Object> iterator(basDugum->ileri);!iterator.hasNext();iterator.next()){
				if(iterator.current->eleman == aranan) return true;
			}
			return false;
		}
		int indexOf(const Object& aranan) const throw(ElemanYok){
			int index=0;
			for(Iterator<Object> iterator(basDugum->ileri);!iterator.hasNext();iterator.next()){
				if(iterator.current->eleman == aranan) return index;
				index++;
			}
			throw ElemanYok();
		}
		friend ostream& operator<<(ostream& screen, LinkedList &left){
			if(left.isEmpty()) screen<<"Liste bos";
			else{
				for(Iterator<Object> iterator = left.FirstNode();!iterator.hasNext();iterator.next())
					screen<<iterator.getCurrent()<<" ";
				screen<<endl;
			}
			return screen;
		}
		/// Listedeki elemanlar� temizler
		void clear(){
			while(!isEmpty())
				remove(FirstNode().getCurrent());			
		}
		~LinkedList(){
			clear();
			delete basDugum;
		}
};
#endif