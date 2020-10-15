#include "Sayi.hpp"
string Sayi::TabanDonustur(){
	int sayi=deger;
	string rakamlar = "0123456789ABCDEF";
	string yeniSayi="";
	Stack<int> *yigit = new Stack<int>();

	while(sayi > 0){
		int kalan = sayi % taban;
		yigit->push(kalan);
		sayi = sayi / taban;
	}
	
	while(!yigit->isEmpty()){
		yeniSayi = yeniSayi + rakamlar[yigit->top()];
		yigit->pop();
	}
	delete yigit;
	return yeniSayi;
}
Sayi::Sayi(){
	cin>>*this;
	donusturulen=TabanDonustur();
}
int Sayi::Taban10Deger()const{
	return deger;
}
ostream& operator<<(ostream& ekran,Sayi &sag){
	ekran<<"("<<sag.deger<<")10"<<"="<<"("<<sag.donusturulen<<")"<<sag.taban;
}	
istream& operator>>(istream& girdi,Sayi &sag){
	cout<<"Sayi:";
	girdi>>sag.deger;
	cout<<"Taban:";
	girdi>>sag.taban;
	return girdi;
}