#ifndef LinkedList_HPP
#define LinkedList_HPP

#include "Iterator.hpp"

template <typename Object>
class CircularLinkedList{
	private:
		Dugum<Object> *basDugum; // içinde eleman olmayan sadece listenin baþýný tutan düðüm.
		int size;
		
		Iterator<Object> OncekiniKonumuIleBul(int konum) const throw(Tasma){
			if(konum < 0 || konum > Count()) throw Tasma();
			int index=0;
			Iterator<Object> iterator(basDugum);
			
			while(!iterator.hasNext() && konum != index++)iterator.next();
			
			return iterator;
		}		
		/// Listenin ilk düðümünü döndürür
		Iterator<Object> FirstNode() const throw(ListeBos){
			if(isEmpty()) throw ListeBos();
			return Iterator<Object>(basDugum->ileri);
		}
		// Eðer listenin baþýna eleman ekleniyorsa veya ilk eleman silinirse liste sonunun ilerisi deðiþir.
		void updateLastNode(){
			Dugum<Object> *lastNode = OncekiniKonumuIleBul(size).current;
			lastNode->ileri = basDugum->ileri;
		}
	public:
		CircularLinkedList(){
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
			iterator.current->ileri = new Dugum<Object>(yeni,iterator.current->ileri);
			size++;
			
			if(konum == 0) updateLastNode();
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
				delete eskiDugum;
				size--;
				if(size == 0) onceki.current->ileri = NULL;
				if(konum == 0 && size != 0) updateLastNode();
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
		friend ostream& operator<<(ostream& screen, CircularLinkedList &left){
			if(left.isEmpty()) screen<<"Liste bos";
			else{
				int index=0;
				for(Iterator<Object> iterator = left.FirstNode();index<left.size;iterator.next(),index++)
					screen<<iterator.getCurrent()<<" ";
				screen<<endl;
			}
			return screen;
		}
		// Verilen konumdan itibaren bütün listeyi yazdýrýr
		void printAllFromPosition(int konum)throw(Tasma){
			if(konum < 0 || konum >= Count()) throw Tasma();
			if(isEmpty()) cout<<"Liste bos"<<endl;
			Iterator<Object> iterator = OncekiniKonumuIleBul(konum);
			int index=0;
			for(iterator.next();index<size;iterator.next(),index++)
					cout<<iterator.getCurrent()<<" ";
			cout<<endl;
		}
		/// Listedeki elemanlarý temizler
		void clear(){
			while(!isEmpty())
				removeAt(0);			
		}
		~CircularLinkedList(){
			clear();
			delete basDugum;
		}
};
#endif