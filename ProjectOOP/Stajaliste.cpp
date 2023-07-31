#include "Stajaliste.h"
#include "Linija.h"
#include <set>

Stajaliste::Stajaliste(int sifra, std::string naziv, bool vazno):sifra_stajalista(sifra), naziv_stajalista(naziv), vazno(vazno) {}


std::set<std::string, std::less<std::string>> Stajaliste::getOznakeLinija(){
	std::set<std::string, std::less<std::string>> out;
	for (Linija* linija : linije) {
		out.insert(linija->getOznakaLinije());
	}
	return out;
}

void Stajaliste::addLinija(Linija* l){
	this->linije.push_back(l);
}
